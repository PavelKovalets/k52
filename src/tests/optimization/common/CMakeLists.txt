cmake_minimum_required(VERSION 2.8)
project(k52_optimization_test_common)

set(K52_OPTIMIZATION_TEST_COMMON_HEADERS
    consts.h
    optimizer_tester.h
    test_objective_functions.h
    test_function.h
    )

set(K52_OPTIMIZATION_TEST_COMMON_SOURCE
    optimizer_tester.cpp
    test_function.cpp
    )

include_directories(${k52_SOURCE_DIR}/include ${K52_BOOST_INCLUDE_DIRS})
add_library(k52_optimization_test_common ${K52_OPTIMIZATION_TEST_COMMON_SOURCE} ${K52_OPTIMIZATION_TEST_COMMON_HEADERS})

