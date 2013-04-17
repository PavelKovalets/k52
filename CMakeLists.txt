cmake_minimum_required(VERSION 2.6)
project(k52)

# It has to be defined before every step that requeries compiler invokation
include(k52.config)
include(configuration/alglib-config.cmake)
include(configuration/boost-config.cmake)
include(configuration/mpi-config.cmake)

if(ALGLIB_ROOT)
endif(ALGLIB_ROOT)

set(CMAKE_INSTALL_PREFIX ${k52_SOURCE_DIR})
set(k52_LIB_DESTINATION /lib)

# parallel library
add_subdirectory(src/parallel)

# optimization algoritms library
add_subdirectory(src/optimization)

# sound signal processing library
add_subdirectory(src/processing)

