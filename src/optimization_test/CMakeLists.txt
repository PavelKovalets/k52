cmake_minimum_required(VERSION 2.6)
project(k52_optimization_test)

# optimization algoritms tests executable
set(OPTIMIZATION_TEST_HEADERS
    test_objective_functions.h
    test_function.h
    )

set(OPTIMIZATION_TEST_SOURCE
    test_function.cpp
    optimization_test.cpp
    )

include_directories(${k52_SOURCE_DIR}/include ${K52_BOOST_INCLUDE_DIRS})
link_directories(${K52_BOOST_LIBRARY_DIRS})
add_executable(k52_optimization_test ${OPTIMIZATION_TEST_SOURCE})
target_link_libraries(k52_optimization_test k52-optimization k52-parallel ${K52_BOOST_LIBRARIES})

add_test("Optimization test" k52_optimization_test)
