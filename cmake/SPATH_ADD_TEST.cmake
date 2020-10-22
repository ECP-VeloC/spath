function(SPATH_ADD_TEST name args outputs)

  # job launcher
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
  message(STATUS "VELOC_RESOURCE_MANAGER=${VELOC_RESOURCE_MANAGER}")
  if(NOT DEFINED VELOC_RESOURCE_MANAGER)
    message(STATUS "in VELOC_RESOURCE_MANAGER not set")
    set(test_param mpirun -np 3)
  elseif(${VELOC_RESOURCE_MANAGER} STREQUAL "NONE")
    message(STATUS "in VELOC_RESOURCE_MANAGER NONE")
    set(test_param mpirun -np 3)
  elseif(${VELOC_RESOURCE_MANAGER} STREQUAL "LSF")
    message(STATUS "in VELOC_RESOURCE_MANAGER LSF")
    set(test_param jsrun -r 1)
  elseif(${VELOC_RESOURCE_MANAGER} STREQUAL "SLURM")
    message(STATUS "in VELOC_RESOURCE_MANAGER SLURM")
    set(test_param srun -N 3 -n 3)
  endif()

  # Tests
  add_test(NAME ${name} COMMAND ${test_param} ./${name} ${args} )

endfunction(SPATH_ADD_TEST)
