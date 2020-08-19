function(SPATH_ADD_TEST name args outputs)

  # job launcher
  if(NOT(${VELOC_RESOURCE_MANAGER}))
    set(test_param mpirun -np 1)
  elseif(${VELOC_RESOURCE_MANAGER} STREQUAL "NONE")
    set(test_param mpirun -np 1)
  elseif(${VELOC_RESOURCE_MANAGER} STREQUAL "LSF")
    set(test_param jsrun -r 1)
  elseif(${VELOC_RESOURCE_MANAGER} STREQUAL "SLURM")
    set(test_param srun -N 3 -n 3)
  endif()

  # Tests
  add_test(NAME ${name} COMMAND ${test_param} ./${name} ${args} )

endfunction(SPATH_ADD_TEST)
