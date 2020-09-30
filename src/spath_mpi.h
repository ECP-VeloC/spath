#ifndef SPATH_MPI_H
#define SPATH_MPI_H

#include "mpi.h"

#include "spath.h"

/** \file spath.h
 *  \ingroup spath
 *  \brief functions to send/recv an spath object */

/* enable C++ codes to include this header directly */
#ifdef __cplusplus
extern "C" {
#endif

/* how to behave if an spath_assert condition is found to be false */
typedef enum {
  SPATH_ASSERT_ABORT = 1, /* print error message and call abort */
  SPATH_ASSERT_HANG,      /* print error message and hang with while(1) */
  SPATH_ASSERT_RETURN,    /* execute allreduce to check on all ranks,
                           * print error message and return failure on all */
} spath_assert_mode_t;

extern spath_assert_mode_t spath_assert_mode; /* determines how spath_assert behaves on errors */

#if 0
/** send/recv path, recv_path should be from spath_new() */
int spath_sendrecv(
  const spath* send_path,
  int send_rank,
  spath* recv_path,
  int recv_rank,
  MPI_Comm comm
);
#endif

/** broadcast path, path should be from spath_new() on non-roots */
int spath_bcast(spath* path, int root, MPI_Comm comm);

/* enable C++ codes to include this header directly */
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* SPATH_MPI_H */
