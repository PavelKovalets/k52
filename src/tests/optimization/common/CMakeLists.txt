cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME k52_optimization_test_common)
project(${PROJECT_NAME})

set(K52_OPTIMIZATION_TEST_COMMON_HEADERS
    consts.h
    optimizer_tester.h
    test_objective_functions.h
    test_function.h
    test_functions_provider.h
    )

set(K52_OPTIMIZATION_TEST_COMMON_SOURCE
    optimizer_tester.cpp
    test_function.cpp
    test_functions_provider.cpp
    )

include_directories(${k52_SOURCE_DIR}/include ${K52_BOOST_INCLUDE_DIRS})
add_library(${PROJECT_NAME} ${K52_OPTIMIZATION_TEST_COMMON_SOURCE} ${K52_OPTIMIZATION_TEST_COMMON_HEADERS})

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER ${TESTS_SOLUTION_FOLDER_NAME})

