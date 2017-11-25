cmake_minimum_required(VERSION 3.1)
project(k52)

# TODO: add versioning
set(k52_VERSION "0.0.0")

set(CMAKE_INSTALL_PREFIX ${k52_SOURCE_DIR}/install)
set(k52_LIB_DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

enable_testing()
set(K52_MESSAGE_PREFIX "->-> K52 MESSAGE <-<- :")
set(K52_MESSAGE_POSTFIX "\n")

#add external modules from "cmake" folder
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

include(k52.config)
include(configuration/common-config.cmake)
include(configuration/fftw3-config.cmake)
include(configuration/boost-config.cmake)
#include(configuration/mpi-config.cmake)

### Libraries
add_subdirectory(src/common)

# parallel library
add_subdirectory(src/parallel)

# optimization algorithms library
add_subdirectory(src/optimization)

# sound signal dsp library
add_subdirectory(src/dsp)

## Unit tests
add_subdirectory(src/unit_tests)

## Create config-file package on install
# Generate configuration file for all subprojects
# subproject order matters
set(k52_LIBRARY_DIRS "lib")
set(k52_SUBPROJECTS k52_optimization k52_dsp k52_parallel k52_common)
foreach(k52_SUBPROJECT ${k52_SUBPROJECTS})
  set(k52_LIBS ${k52_LIBS} "${k52_SUBPROJECT}")
endforeach()

if(FFTW3_FOUND)
    set(k52_LIBS ${k52_LIBS} ${FFTW3_LIBRARIES})
endif()

set(k52_LIBS ${k52_LIBS} ${K52_BOOST_LIBRARIES} ${K52_MPI_LIBRARIES})

#TODO this is a temporary fix, remove it when ifdefs will be removed from headers
if(MPI_CXX_FOUND AND Boost_MPI_FOUND AND Boost_SERIALIZATION_FOUND)
  set(k52_DEFINES  "${k52_DEFINES} \nadd_definitions(-DBUILD_WITH_MPI)  ")
endif()

if(Boost_THREAD_FOUND AND Boost_SYSTEM_FOUND AND Boost_DATE_TIME_FOUND)
  set(k52_DEFINES  "${k52_DEFINES} \nadd_definitions(-DBUILD_WITH_BOOST_THREAD)  ")
endif()
#End TODO

set(k52_INCLUDE_DIRS "include")
configure_file(k52-config.cmake.in "${PROJECT_BINARY_DIR}/k52-config.cmake" @ONLY)
install(FILES "${PROJECT_BINARY_DIR}/k52-config.cmake" DESTINATION ${CMAKE_INSTALL_PREFIX})

install(DIRECTORY ${k52_SOURCE_DIR}/include/ DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
