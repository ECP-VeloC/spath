###############
# Build tests
###############

################
# Add tests to ctest
################

ADD_EXECUTABLE(spath_bcast_test test_spath_bcast.c)
TARGET_LINK_LIBRARIES(spath_bcast_test ${SPATH_EXTERNAL_LIBS} spath)
SPATH_ADD_TEST(spath_bcast_test 256 "")
#ADD_TEST(NAME spath_bcast_test COMMAND ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} 3 ./spath_bcast_test)

ADD_EXECUTABLE(spath_test test_spath.c)
TARGET_LINK_LIBRARIES(spath_test ${SPATH_EXTERNAL_LIBS} spath)
SPATH_ADD_TEST(spath_test 256 "")
#ADD_TEST(NAME spath_test COMMAND ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} 3 ./spath_test)

####################
# make a verbose "test" target named "check"
####################

ADD_CUSTOM_TARGET(check COMMAND ${CMAKE_CTEST_COMMAND} --verbose)
