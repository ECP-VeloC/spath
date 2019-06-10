#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include "spath.h"
#include "spath_mpi.h"

#define TEST_PASS (0)
#define TEST_FAIL (1)

int main(int argc, char** argv){
  int rc = TEST_PASS;
  int rank, ranks, kvtree_rc;
  spath* sp;
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
  rc = spath_bcast(sp, 1, MPI_COMM_WORLD);
  spath_strcpy(final_buff,100, sp);
  printf(" final spath from rank %d :%s\n", rank, final_buff);


  MPI_Finalize();
  return rc;
}
