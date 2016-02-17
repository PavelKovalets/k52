cmake_minimum_required(VERSION 2.8)
set(PROJECT_NAME continuous_optimization_example)
project(${PROJECT_NAME})

add_definitions(-D_USE_MATH_DEFINES)

set(CONTINUOUS_OPTIMIZATION_HEADERS
    consts.h
    optimizer_tester.h
    test_objective_functions.h
    test_function.h
    test_functions_provider.h
    optimizers_provider.h
    optimizer_test_result.h
)

set(CONTINUOUS_OPTIMIZATION_SOURCE
    main.cpp
    optimizer_tester.cpp
    test_function.cpp
    test_functions_provider.cpp
    optimizers_provider.cpp
    optimizer_test_result.cpp
)

set(BOOST_ROOT "")
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

find_package(k52 REQUIRED HINTS "${CMAKE_CURRENT_LIST_DIR}/../../install")

include_directories(${k52_INCLUDE_DIRS})
link_directories(${k52_LIBRARY_DIRS})

add_executable(${PROJECT_NAME} ${CONTINUOUS_OPTIMIZATION_SOURCE} ${CONTINUOUS_OPTIMIZATION_HEADERS})

target_link_libraries(${PROJECT_NAME} ${k52_LIBRARIES})

