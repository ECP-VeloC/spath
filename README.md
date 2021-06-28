# spath

[![Build Status](https://api.travis-ci.org/ECP-VeloC/spath.png?branch=main)](https://travis-ci.org/ECP-VeloC/spath)

## Overview

The spath libary defines a data structure and a number of functions to manipulate paths,
including combining, slicing, simplification,
computing relative paths, and converting to/from character strings.

For a quick intro, see [doc/rst/spath.rst](doc/rst/spath.rst).

For full documentation, refer to [src/spath.h](src/spath.h) and the [User API docs](https://ecp-veloc.github.io/component-user-docs/group__spath.html).

## Quickstart

spath uses the CMake build system and we recommend out-of-source builds.

```shell
git clone git@github.com:ECP-VeloC/spath.git
mkdir build
mkdir install

cd build
cmake -DCMAKE_INSTALL_PREFIX=../install ../spath
make
make install
make check
```

Some useful CMake command line options:

- `-DCMAKE_INSTALL_PREFIX=[path]`: Place to install the spath library
- `-DCMAKE_BUILD_TYPE=[Debug/Release]`: Build with debugging or optimizations
- `-DMPI=ON`: Build with support for MPI movement of spath objects

### Dependencies

  - C
  - MPI (optional)
  - CMake, Version 2.8+

## Release

Copyright (c) 2018, Lawrence Livermore National Security, LLC.
Produced at the Lawrence Livermore National Laboratory.
<br>
Copyright (c) 2018, UChicago Argonne LLC, operator of Argonne National Laboratory.


For release details and restrictions, please read the [LICENSE](LICENSE) and [NOTICE](NOTICE) files.

`LLNL-CODE-751725` `OCEC-18-060`
