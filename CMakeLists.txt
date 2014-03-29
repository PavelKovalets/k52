cmake_minimum_required(VERSION 2.8)
project(k52)

enable_testing()
set(K52_MESSAGE_PREFIX "->-> K52 MESSAGE <-<- :")
set(K52_MESSAGE_POSTFIX "\n")
include(k52.config)
include(configuration/common-config.cmake)
include(configuration/alglib-config.cmake)
include(configuration/boost-config.cmake)
include(configuration/mpi-config.cmake)

set(CMAKE_INSTALL_PREFIX ${k52_SOURCE_DIR})
set(k52_LIB_DESTINATION /lib)

### Libraries
# parallel library
add_subdirectory(src/parallel)

# optimization algoritms library
add_subdirectory(src/optimization)

# sound signal processing library
add_subdirectory(src/processing)

## Test applications
# optimization algorithms library tests
add_subdirectory(src/tests)
