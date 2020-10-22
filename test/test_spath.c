#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "spath.h"
#include "spath_mpi.h"

#define TEST_PASS (0)
#define TEST_FAIL (1)

int main(int argc, char** argv){
  int rc;
  spath *sp, *spath_cpy, *sp1, *sp_rel;
  char buff[100], init_path[100], final_buff[100], *bf;

  sp = NULL;
  //now allocate, sp should no longer be NULL
  sp = spath_new();
  if(sp == NULL){
    printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
    printf("test_spath failed, spath_new() failed to allocate\n");
    return TEST_FAIL;
  }

  spath_delete(&sp);
  sp = spath_from_str("SPATH");
  spath_strcpy(buff,100, sp);
  if(sp == NULL || strcmp(buff, "SPATH") != 0 ){
    printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
    printf("test_spath failed, spath_from_str() failed \n");
    return TEST_FAIL;
  }

  if(spath_strlen(sp) != 5 ){
    printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
    printf("test_spath failed, spath_strlen() returns wrong length of string \n");
    return TEST_FAIL;
  }

  spath_cpy = spath_dup(sp);
  spath_strcpy(buff,100, spath_cpy);
  if(spath_cpy == NULL || strcmp(buff, "SPATH") != 0 ){
    printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
    printf("test_spath failed, spath_dup() or spath_strcpy() failed\n");
    return TEST_FAIL;
  }

  if(spath_is_null(spath_cpy) == 1){
    printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
    printf("test_spath failed, spath_is_null() returning true for not-null spath \n");
    return TEST_FAIL;
  }

  spath_delete(&sp);
  spath_cpy = spath_dup(sp);
  if(spath_cpy != NULL){
    printf("test_spath failed, spath_dup() returned NOT NULL with NULL argument\n");
    return TEST_FAIL;
  }

  sp = spath_from_str("SPATH");
  bf = spath_strdup(sp);
  if(bf == NULL || strcmp(bf, "SPATH") != 0 ){
    printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
    printf("test_spath failed, spath_strdup() failed\n");
    return TEST_FAIL;
  }

  spath_delete(&sp);
  free(bf);
  bf = spath_strdup(sp);
  if(bf != NULL){
    printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
    printf("test_spath failed, spath_strdup() returned NOT NULL when copying NULL spath\n");
    return TEST_FAIL;
  }

  spath_delete(&spath_cpy);
  if(spath_is_null(spath_cpy) == 0){
    printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
    printf("test_spath failed, spath_is_null() returning false following deletion of spath \n");
    return TEST_FAIL;
  }

  spath_delete(&sp);
  sp = spath_from_str("Directory");
  sp1 = spath_from_str("File");
  spath_insert(sp, 1, sp1);
  spath_strcpy(buff,100, sp);
  if(strcmp(buff, "Directory/File") != 0 ){
    printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
    printf("test_spath failed, spath_insert failed \n");
    return TEST_FAIL;
  }
  
  spath_delete(&sp);
  spath_delete(&sp1);
  sp1 = spath_from_str("File");
  rc = spath_insert(sp, 1, sp1);
  if(rc != SPATH_FAILURE){
    printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
    printf("test_spath failed, spath_insert() attempt to insert into NULL spath didn't return failure\n");
    return TEST_FAIL;
  }

  spath_delete(&sp);
  sp = spath_from_str("Directory/File");
  if(spath_components(sp) != 2 ){
    printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
    printf("test_spath failed, spath_components()  wrong number of components\n");
    return TEST_FAIL;
  }

  spath_delete(&sp);
  spath_delete(&sp1);
  sp = spath_from_str("Directory");
  sp1 = spath_from_str("File");
  spath_append(sp,sp1);
  spath_strcpy(buff,100, sp);
  if(strcmp(buff, "Directory/File") != 0 ){
    printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
    printf("test_spath failed, spath_append() failed \n");
    return TEST_FAIL;
  }

  spath_delete(&sp);
  spath_delete(&sp1);
  sp1 = spath_from_str("File");
  rc = spath_append(sp,sp1);
  if(rc != SPATH_FAILURE){
    printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
    printf("test_spath failed, spath_append() attempt to append to NULL spath didn't return failure\n");
    return TEST_FAIL;
  }

  spath_delete(&sp);
  spath_delete(&sp1);
  sp1 = spath_from_str("Directory");
  sp = spath_from_str("File");
  spath_prepend(sp,sp1);
  spath_strcpy(buff,100, sp);
  if(strcmp(buff, "Directory/File") != 0 ){
    printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
    printf("test_spath failed, spath_prepand() failed \n");
    return TEST_FAIL;
  }

  spath_delete(&sp);
  spath_delete(&sp1);
  sp1 = spath_from_str("Directory");
  rc = spath_prepend(sp,sp1);
  if(rc != SPATH_FAILURE){
    printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
    printf("test_spath failed, spath_prepand() attempt to prepend to NULL spath didn't return failure\n");
    return TEST_FAIL;
  }

  spath_delete(&sp);
  sp = spath_from_str("Directory");
  spath_insert_str(sp, 1, "File");
  spath_strcpy(buff,100, sp);
  if(strcmp(buff, "Directory/File") != 0 ){
    printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
    printf("test_spath failed, spath_insert_str() failed \n");
    return TEST_FAIL;
  }

  spath_delete(&sp);
  rc = spath_insert_str(sp, 1, "File");
  if(rc != SPATH_FAILURE){
    printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
    printf("test_spath failed, spath_insert_str() attempt to insert into NULL spath didn't return failure\n");
    return TEST_FAIL;
  }

  spath_delete(&sp);
  sp = spath_from_str("Directory");
  spath_append_str(sp, "File");
  spath_strcpy(buff,100, sp);
  if(strcmp(buff, "Directory/File") != 0 ){
    printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
    printf("test_spath failed, spath_append_str() failed \n");
    return TEST_FAIL;
  }

  spath_delete(&sp);
  rc = spath_append_str(sp,"File");
  if(rc != SPATH_FAILURE){
    printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
    printf("test_spath failed, spath_append_str() attempt to append to NULL spath didn't return failure\n");
    return TEST_FAIL;
  }

  spath_delete(&sp);
  sp = spath_from_str("File");
  spath_prepend_str(sp, "Directory");
  spath_strcpy(buff,100, sp);
  if(strcmp(buff, "Directory/File") != 0 ){
    printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
    printf("test_spath failed, spath_prepend_str() failed \n");
    return TEST_FAIL;
  }

  spath_delete(&sp);
  rc = spath_prepend_str(sp,"Directory");
  if(rc != SPATH_FAILURE){
    printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
    printf("test_spath failed, spath_prepand_str() attempt to prepend to NULL spath didn't return failure\n");
    return TEST_FAIL;
  }

  spath_delete(&sp);
  sp = spath_from_str("Directory/File/1/2/3/4");
  rc = spath_slice(sp, 2,4);
//  spath_slice(sp, -6,-17);
  spath_strcpy(buff,100, sp);
  printf("slice result is %s\n",buff);
  if(rc != SPATH_SUCCESS || strcmp(buff, "1/2/3/4") != 0 ){
    printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
    printf("test_spath failed, spath_slice() failed \n");
    return TEST_FAIL;
  }

  spath_delete(&sp);
  sp = spath_from_str("Directory/File/1/2/3/4");
  rc = spath_slice(sp,2,5);
  spath_strcpy(buff,100, sp);
  if(rc != SPATH_SUCCESS || strcmp(buff, "1/2/3/4") != 0 ){
    printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
    printf("test_spath failed, spath_slice() with last argument out of range failed \n");
//  if(rc == SPATH_SUCCESS){
//    printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
//    printf("test_spath failed, spath_slice() returned SPATH_SUCCESS when (offset + length) > components \n");
    return TEST_FAIL;
  }

  spath_delete(&sp);
  sp = spath_from_str("Directory/File/1/2/3/4");
  rc = spath_slice(sp,6,1);
  spath_strcpy(buff,100, sp);
  if(rc != SPATH_SUCCESS || strcmp(buff, "Directory") != 0 ){
    printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
    printf("test_spath failed, spath_slice() with next to last argument out of range failed \n");
//  if(rc == SPATH_SUCCESS){
//    printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
//    printf("test_spath failed, spath_slice() returned SPATH_SUCCESS when starting index not in range \n");
    return TEST_FAIL;
  }

  spath_delete(&sp);
  sp = spath_from_str("Dir1/Dir2/Dir3/File");
  spath_dirname(sp);
  spath_strcpy(buff,100, sp);
  if(strcmp(buff, "Dir1/Dir2/Dir3") != 0 ){
    printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
    printf("test_spath failed, spath_dirname() failed \n");
    return TEST_FAIL;
  }

  spath_delete(&sp);
  sp = spath_from_str("Dir1/Dir2/Dir3/File");
  spath_basename(sp);
  spath_strcpy(buff,100, sp);
  if(strcmp(buff, "File") != 0 ){
    printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
    printf("test_spath failed, spath_basename() failed \n");
    return TEST_FAIL;
  }

  spath_delete(&sp);
  spath_delete(&sp1);
  sp = spath_from_str("Directory/File/1/2/3/4");
  sp1 = spath_sub(sp,2,4);
//  sp1 = spath_sub(sp, -6,-17);
  spath_strcpy(buff,100, sp1);
  printf("sub result is %s\n",buff);
  if(strcmp(buff, "1/2/3/4") != 0 ){
    printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
    printf("test_spath failed, spath_sub() returned wrong path \n");
    return TEST_FAIL;
  }

  spath_delete(&sp);
  spath_delete(&sp1);
  sp = spath_from_str("Directory/File/1/2/3/4");
  sp1 = spath_sub(sp,2,5);
  spath_strcpy(buff,100, sp1);
    printf ("SPATH_SUB= %s\n",buff);
  if(rc != SPATH_SUCCESS || strcmp(buff, "1/2/3/4") != 0 ){
    printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
    printf("test_spath failed, spath_sub() with last argument out of range failed \n");
//  if(sp1 != NULL){
//    printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
//    printf("test_spath failed, spath_sub() returned NOT NULL when (offset + length) > components \n");
    return TEST_FAIL;
  }

  spath_delete(&sp);
  spath_delete(&sp1);
  sp = spath_from_str("Directory/File/1/2/3/4");
  sp1 = spath_sub(sp,6,1);
  spath_strcpy(buff,100, sp1);
    printf ("SPATH_SUB2= %s\n",buff);
  if(rc != SPATH_SUCCESS || strcmp(buff, "Directory") != 0 ){
    printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
    printf("test_spath failed, spath_sub() with next to last argument out of range failed \n");
//  if(sp1 != NULL){
//    printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
//    printf("test_spath failed, spath_sub() returned NOT NULL when starting index not in range \n");
    return TEST_FAIL;
  }

  spath_delete(&sp);
  spath_delete(&sp1);
  sp = spath_from_str("Directory/File/1/2/3/4");
  sp1 = spath_cut(sp,1);
  spath_strcpy(buff,100, sp1);
  if(strcmp(buff, "File/1/2/3/4") != 0 ){
    printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
    printf("test_spath failed, spath_basename() failed \n");
    return TEST_FAIL;
  }

  spath_delete(&sp);
  sp = spath_from_str("//./1/2/3//4/");
  spath_reduce(sp);
  spath_strcpy(buff,100, sp);
  if(strcmp(buff, "/1/2/3/4") != 0 ){
    printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
    printf("test_spath failed, spath_reduce() failed \n");
    return TEST_FAIL;
  }

  bf = spath_strdup_reduce_str("//./1/2/3//4/");
  if(strcmp(bf, "/1/2/3/4") != 0 ){
    printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
    printf("test_spath failed, spath_strdup_reduce_str() failed \n");
    return TEST_FAIL;
  }

  spath_delete(&sp);
  spath_delete(&sp1);
  sp = spath_from_str("/Absolute");
  sp1 = spath_from_str("Relative");
  if(spath_is_absolute(sp) != 1 || spath_is_absolute(sp1) != 0){
    printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
    printf("test_spath failed, spath_is_absolute() failed \n");
    return TEST_FAIL;
  }

  spath_delete(&sp);
  spath_delete(&sp1);
  sp = spath_from_str("1/2/3");
  sp1 = spath_from_str("1/2/3/4");
  if(spath_is_child(sp,sp1) != 1){
    printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
    printf("test_spath failed, spath_is_child() failed \n");
    return TEST_FAIL;
  }

  spath_delete(&sp);
  spath_delete(&sp1);
  sp = spath_from_str("1/2/3");
  sp1 = spath_from_str("1/2/./3/4");
  spath_reduce(sp1);
  sp_rel = spath_relative(sp,sp1);
  spath_strcpy(buff,100, sp_rel);
  if(strcmp(buff, "4") != 0 ){
    printf ("Error in line %d, file %s, function %s.\n", __LINE__, __FILE__, __func__);
    printf("test_spath failed, spath_is_child() failed \n");
    return TEST_FAIL;
  }

  return TEST_PASS;
}
