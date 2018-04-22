#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "spath.h"
#include "spath_mpi.h"

#define TEST_PASS (0)
#define TEST_FAIL (1)

int main(int argc, char** argv){
  int rank, ranks;
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
  int bcast_rc = spath_bcast(sp_bcast, 1, MPI_COMM_WORLD);
  if(bcast_rc != SPATH_SUCCESS){
    printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
    printf("test_spath_bcast failed, spath_bcast call failed for rank: %d\n", rank);
    return TEST_FAIL;
  }

  spath_strcpy(final_buff,100, sp_bcast);
  printf(" final spath from rank %d :%s\n", rank, final_buff);
  if(strcmp(final_buff, "initial spath for rank 1") != 0){
    printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
    printf("spath_bcast_test failed, wrong spath value for rank: %d\n", rank);
    return TEST_FAIL;
  }
// perform a bad argument test
  bcast_rc = spath_bcast(NULL, 1, MPI_COMM_WORLD);
  if(bcast_rc == SPATH_SUCCESS){
    printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
    printf("test_spath_bcast failed, spath_bcast call succeded with NULL argument for rank: %d\n", rank);
    return TEST_FAIL;
  }

  MPI_Finalize();
  return TEST_PASS;
}
