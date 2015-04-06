cmake_minimum_required(VERSION 2.8)
project(k52)

# TODO: add versioning
set(k52_VERSION "0.0.0")

set(CMAKE_INSTALL_PREFIX ${k52_SOURCE_DIR})
set(k52_LIB_DESTINATION /lib)

enable_testing()
set(K52_MESSAGE_PREFIX "->-> K52 MESSAGE <-<- :")
set(K52_MESSAGE_POSTFIX "\n")
include(k52.config)
include(configuration/common-config.cmake)
include(configuration/alglib-config.cmake)
include(configuration/boost-config.cmake)
include(configuration/mpi-config.cmake)

### Libraries
add_subdirectory(src/common)

# parallel library
add_subdirectory(src/parallel)

# optimization algorithms library
add_subdirectory(src/optimization)

# sound signal dsp library
add_subdirectory(src/dsp)

## Test applications
# optimization algorithms library tests
add_subdirectory(src/tests)

# Generate configuration file for all subprojects
# subproject order matters
set(k52_LIBRARY_DIRS "../lib")
set(k52_SUBPROJECTS k52_optimization k52_dsp k52_parallel k52_common)
foreach(k52_SUBPROJECT ${k52_SUBPROJECTS})
  get_target_property(TARGET_BUILD_SPECIFIC_LOCATION ${k52_SUBPROJECT} LOCATION)
  get_filename_component(TARGET_PLATFORM_SPECIFIC_FILENAME ${TARGET_BUILD_SPECIFIC_LOCATION} NAME)
  set(k52_LIBS ${k52_LIBS} "\${k52_DIR}/${k52_LIBRARY_DIRS}/${TARGET_PLATFORM_SPECIFIC_FILENAME}")
endforeach()

# TODO: improve install to properly install headers, libraries and config file(s)
set(k52_INCLUDE_DIRS "../include")
configure_file(k52-config.cmake.in "${PROJECT_BINARY_DIR}/k52-config.cmake" @ONLY)
install(FILES "${PROJECT_BINARY_DIR}/k52-config.cmake" DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
