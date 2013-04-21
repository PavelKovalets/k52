cmake_minimum_required(VERSION 2.6)
project(k52)

include(k52.config)
if(BOOST_ROOT)
  message("Using custom boost root path : ${BOOST_ROOT}")
endif(BOOST_ROOT)

if(ALGLIB_ROOT)
  message("Using custom alglib root path : ${ALGLIB_ROOT}")
endif(ALGLIB_ROOT)

set(CMAKE_INSTALL_PREFIX ${k52_SOURCE_DIR})
set(k52_LIB_DESTINATION /lib)

set(AUTO_RESOLVE_PARALLEL_LIBS "ON")

# parallel library
add_subdirectory(src/parallel)

# optimization algoritms library
add_subdirectory(src/optimization)

# optimization algoritms library tests
add_subdirectory(src/optimization_test)

# sound signal processing library
add_subdirectory(src/processing)

