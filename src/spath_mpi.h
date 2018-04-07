/*
 * Copyright (c) 2009, Lawrence Livermore National Security, LLC.
 * Produced at the Lawrence Livermore National Laboratory.
 * Written by Adam Moody <moody20@llnl.gov>.
 * LLNL-CODE-411039.
 * All rights reserved.
 * This file is part of The Scalable Checkpoint / Restart (SCR) library.
 * For details, see https://sourceforge.net/projects/scalablecr/
 * Please also read this file: LICENSE.TXT.
*/

#ifndef SPATH_MPI_H
#define SPATH_MPI_H

#include "mpi.h"

#include "spath.h"

#if 0
/* send/recv path, recv_path should be from spath_new() */
int spath_sendrecv(
  const spath* send_path,
  int send_rank,
  spath* recv_path,
  int recv_rank,
  MPI_Comm comm
);
#endif

/* broadcast path, path should be from spath_new() on non-roots */
int spath_bcast(spath* path, int root, MPI_Comm comm);

#endif /* SPATH_MPI_H */
