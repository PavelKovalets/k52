cmake_minimum_required(VERSION 2.6)
project(k52_optimization_test_common)

set(K52_OPTIMIZATION_TEST_COMMON_HEADERS
    test_objective_functions.h
    test_function.h
    )

set(K52_OPTIMIZATION_TEST_COMMON_SOURCE
    test_function.cpp
    )

include_directories(${k52_SOURCE_DIR}/include ${K52_BOOST_INCLUDE_DIRS})
add_library(k52_optimization_test_common ${K52_OPTIMIZATION_TEST_COMMON_SOURCE})

