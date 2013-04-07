cmake_minimum_required(VERSION 2.6)
project(k52)

# It has to be defined before every step that requeries compiler invokation

include(k52.config)
#include(configuration/mpi-config.cmake)
include(configuration/boost-config.cmake)

if(MPI_FOUND AND Boost_MPI_FOUND AND Boost_SERIALIZATION_FOUND)
  add_definitions(-DBUILD_WITH_MPI)
endif(MPI_FOUND AND Boost_MPI_FOUND AND Boost_SERIALIZATION_FOUND)

if(ALGLIB_ROOT)
  message("Using custom alglib root path : ${ALGLIB_ROOT}")
endif(ALGLIB_ROOT)

set(CMAKE_INSTALL_PREFIX ${k52_SOURCE_DIR})
set(k52_LIB_DESTINATION /lib)

# parallel library
add_subdirectory(src/parallel)

# optimization algoritms library
add_subdirectory(src/optimization)

# sound signal processing library
add_subdirectory(src/processing)

