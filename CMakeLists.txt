CMAKE_MINIMUM_REQUIRED(VERSION 3.14)
PROJECT(SPATH VERSION 0.4.0)

# Mac rpath Policy
IF(POLICY CMP0042)
          CMAKE_POLICY(SET CMP0042 NEW)
ENDIF(POLICY CMP0042)
SET(CMAKE_MACOSX_RPATH ON)

# Linux rpath settings
SET(CMAKE_SKIP_BUILD_RPATH FALSE)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

SET(CMAKE_POSITION_INDEPENDENT_CODE ON)

#SET(CMAKE_C_FLAGS "-Wall")

# Configuration Options
OPTION(MPI "Enable MPI operations for spath" ON)
MESSAGE(STATUS "MPI: ${MPI}")

OPTION(BUILD_SHARED_LIBS "Whether to build shared libraries" ON)
MESSAGE(STATUS "BUILD_SHARED_LIBS: ${BUILD_SHARED_LIBS}")

if (BUILD_SHARED_LIBS)
   OPTION(SPATH_LINK_STATIC "Default to static linking? (Needed for Cray)" OFF)
else()
   OPTION(SPATH_LINK_STATIC "Default to static linking? (Needed for Cray)" ON)
endif()
MESSAGE(STATUS "SPATH_LINK_STATIC: ${SPATH_LINK_STATIC}")

OPTION(ENABLE_TESTS "Whether to build tests" ON)
MESSAGE(STATUS "ENABLE_TESTS: ${ENABLE_TESTS}")

OPTION(TVDISPLAY "Whether to compile tv_data_display.c for debugging with TotalView C++View" OFF)
MESSAGE(STATUS "TVDISPLAY: ${TVDISPLAY}")

# Find Packages & Files

LIST(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

## MPI
IF(MPI)
    INCLUDE(SetupMPI)
    IF(NOT MPI_C_FOUND)
        MESSAGE(FATAL_ERROR
            "Could not find MPI! "
            "Either add an MPI compiler to your path "
            "or force CMake to build using the correct compiler (`export CC=mpicc`). "
            "To disable MPI, set -DMPI=OFF")
    ENDIF(NOT MPI_C_FOUND)
ENDIF(MPI)

## HEADERS
INCLUDE(CheckIncludeFile)
INCLUDE(GNUInstallDirs)

# Subdirectories
ADD_SUBDIRECTORY(src)

IF(ENABLE_TESTS)
   INCLUDE(CTest)
   INCLUDE(SPATH_ADD_TEST)
   ADD_SUBDIRECTORY(test)
ENDIF(ENABLE_TESTS)
#ADD_DEFINITION(-DHIDE_TV=1)

# Generate config.h with all our build #defs
CONFIGURE_FILE(${PROJECT_SOURCE_DIR}/cmake/config.h.in ${PROJECT_BINARY_DIR}/config.h)
SET_SOURCE_FILES_PROPERTIES(${PROJECT_BINARY_DIR}/config.h PROPERTIES GENERATED TRUE)

# CMake configs

# Install the exports file
INSTALL(EXPORT spathTargets FILE spathTargets.cmake NAMESPACE spath:: DESTINATION share/spath/cmake)

# Export so we can use in-tree
EXPORT(EXPORT spathTargets NAMESPACE spath:: FILE spathTargets.cmake)

# Setup the package config
INCLUDE(CMakePackageConfigHelpers)
CONFIGURE_PACKAGE_CONFIG_FILE(cmake/spathConfig.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/spathConfig.cmake INSTALL_DESTINATION share/spath/cmake)
WRITE_BASIC_PACKAGE_VERSION_FILE(${CMAKE_CURRENT_BINARY_DIR}/spathConfigVersion.cmake COMPATIBILITY SameMajorVersion)

# Install package config
INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/spathConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/spathConfigVersion.cmake DESTINATION share/spath/cmake)

# Package
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "SPATH Path manipulation functions")
SET(CPACK_PACKAGE_VENDOR "Lawrence Livermore National Laboratory")
# SET(CPACK_PACKAGE_DESCRIPTION_FILE "${PROJECT_SOURCE_DIR}/README.md")
# SET(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE.TXT")
