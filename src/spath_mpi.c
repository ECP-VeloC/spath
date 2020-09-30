#include "mpi.h"

#include "spath.h"
#include "spath_util.h"
#include "spath_mpi.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#include <stdint.h>

/*
=========================================
Functions to send/recv paths with MPI
=========================================
*/

spath_assert_mode_t spath_assert_mode = SPATH_ASSERT_ABORT; /* determines how spath_assert behaves on errors */

/* Check that given condition is true.
 * Returns 0 if assert passes, and 1 if assert fails.
 * if in production mode:
 *   - if condition is false, print msg and call MPI_Abort
 * if in testing mode:
 *   - execute allreduce on comm to verify condition is true on *all* procs,
 *     if false on *any* proc, print msg and return error on all procs
 * if in debugging mode:
 *   - if condition is false, print msg and call while(1) to hang,
 *     which allows someone to attach debugger */
static int spath_assert(int condition, MPI_Comm comm, const char* format, ...)
{
  /* If in production mode and condition is false,
   * then print error message and call abort. */
  if (spath_assert_mode == SPATH_ASSERT_ABORT) {
    if (! condition) {
      /* print error message */
      va_list ap;
      va_start(ap, format);
      vfprintf(stderr, format, ap);
      va_end(ap);
      fflush(stderr);

      /* abort */
      MPI_Abort(comm, -1);
    }
  }

  /* If in debugging mode and condition is false,
   * then print error message and hang so one can attach a debugger. */
  if (spath_assert_mode == SPATH_ASSERT_HANG) {
    if (! condition) {
      /* print error message */
      va_list ap;
      va_start(ap, format);
      vfprintf(stderr, format, ap);
      va_end(ap);

      /* hang, so user can attach a debugger */
      fprintf(stderr, "Hanging in while(1) ...\n");
      fflush(stderr);
      while(1);
    }
  }

  /* If in testing mode, check that condition is true on all procs in comm.
   * If true everywhere, return SUCCESS.  Otherwise, print error message
   * from one rank and return an error on all ranks. */
  if (spath_assert_mode == SPATH_ASSERT_RETURN) {
    /* verify that condition is true on all procs in comm */
    int alltrue;
    MPI_Allreduce(&condition, &alltrue, 1, MPI_INT, MPI_LAND, comm);
    if (! alltrue) {
      /* condition is false on at least one rank in comm,
       * print the error message, but just from rank 0 */
      int rank;
      MPI_Comm_rank(comm, &rank);
      if (rank == 0) {
        va_list ap;
        va_start(ap, format);
        vfprintf(stderr, format, ap);
        va_end(ap);
        fflush(stderr);
      }

      /* everyone return an error from all ranks */
      return 1;
    }
  }

  /* condition is true */
  return 0;
}

/* broacast path from root to all ranks in comm,
 * receivers must pass in a newly allocated path from spath_new() */
int spath_bcast(spath* path, int root, MPI_Comm comm)
{
  /* if pointer is NULL, throw an error */
  int assert_rc = spath_assert(path != NULL, comm,
    "NULL pointer passed for path @ %s:%d\n",
    __FILE__, __LINE__);
  if (assert_rc) {
    return SPATH_FAILURE;
  }

  /* lookup our rank in comm */
  int rank;
  MPI_Comm_rank(comm, &rank);

  /* as a receiver, verify that we were given an empty path */
  int components = spath_components(path);
  assert_rc = spath_assert(rank == root || components == 0, comm,
    "Non-null path passed as input in receiver to bcast path @ %s:%d\n",
    __FILE__, __LINE__);
  if (assert_rc) {
    return SPATH_FAILURE;
  }

  /* determine number of bytes to send */
  int bytes;
  if (rank == root) {
    if (components > 0) {
      /* figure out string length of path (including terminating NULL) */
      bytes = spath_strlen(path) + 1;
    } else {
      /* we use 0 bytes to denote a NULL path,
       * since even an empty string contains at least one byte */
      bytes = 0;
    }
  }

  /* broadcast number of bytes in path */
  MPI_Bcast(&bytes, 1, MPI_INT, root, comm);

  /* if path is NULL, we're done */
  if (bytes == 0) {
    return SPATH_SUCCESS;
  }

  /* otherwise, allocate bytes to receive str */
  char* str;
  if (rank == root) {
    /* the root converts the path to a string */
    str = spath_strdup(path);
  } else {
    /* non-root processes need to allocate an array */
    str = (char*) SPATH_MALLOC((size_t)bytes);
  }
  assert_rc = spath_assert(str != NULL, comm,
    "Failed to allocate memory to bcast path @ %s:%d\n",
    __FILE__, __LINE__);
  if (assert_rc) {
    return SPATH_FAILURE;
  }

  /* broadcast the string */
  MPI_Bcast(str, bytes, MPI_CHAR, root, comm);

  /* if we're not the rank, append the string to our path */
  if (rank != root) {
    spath_append_str(path, str);
  }

  /* free string */
  spath_free(&str);

  return SPATH_SUCCESS;
}
