###############
# Build tests
###############

################
# Add tests to ctest
################

ADD_EXECUTABLE(spath_test test_spath_bcast.c)
TARGET_LINK_LIBRARIES(spath_test ${SPATH_EXTERNAL_LIBS} spath)
#ADD_TEST(NAME spath_test COMMAND ${MPIEXEC} -n3 -m block ./spath_test)
ADD_TEST(NAME spath_test COMMAND ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} 3 ./spath_test)


####################
# make a verbose "test" target named "check"
####################

ADD_CUSTOM_TARGET(check COMMAND ${CMAKE_CTEST_COMMAND} --verbose)
