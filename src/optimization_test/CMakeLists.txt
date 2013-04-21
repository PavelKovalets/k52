cmake_minimum_required(VERSION 2.6)
project(k52_optimization_test)

# optimization algoritms tests executable
set(OPTIMIZATION_TEST_SOURCE
    optimization_test.cpp
    )

if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  link_directories(${Boost_LIBRARY_DIRS})
endif(Boost_FOUND)

include_directories(${k52_SOURCE_DIR}/include)
add_executable (k52_optimization_test ${OPTIMIZATION_TEST_SOURCE})


