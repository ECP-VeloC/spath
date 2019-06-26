#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "spath.h"
#include "spath_mpi.h"

#define TEST_PASS (0)
#define TEST_FAIL (1)

int main(int argc, char** argv){
  int rc = TEST_PASS;
  int rank, ranks, kvtree_rc;
  spath *sp, *sp_bcast;
  char buff[100], init_path[100], final_buff[100];
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &ranks);
  if( ranks != 3){
    printf("tests require 3 processes; actual # is %d\n", ranks);
    return 1;
  }
  sprintf(init_path,"initial spath for rank %d", rank);
sp = spath_from_str(init_path);
spath_strcpy(buff,100, sp);
printf("spath from rank %d :%s\n", rank, buff);
  if(rank == 1){
    sp_bcast = sp;
  }
  else{
    sp_bcast = spath_new();
  }
  rc = spath_bcast(sp_bcast, 1, MPI_COMM_WORLD);
  spath_strcpy(final_buff,100, sp_bcast);
  printf(" final spath from rank %d :%s\n", rank, final_buff);
  if(strcmp(final_buff, "initial spath for rank 1") != 0){
    printf("spath_bcast failed for rank: %d\n", rank);
    rc = TEST_FAIL;
  }


  MPI_Finalize();
  return rc;
}
