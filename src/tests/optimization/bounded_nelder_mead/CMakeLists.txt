cmake_minimum_required(VERSION 2.6)
project(k52_bounded_nelder_mead_test)

# optimization algoritms tests executable
set(K52_BOUNDED_NELDER_MEAD_TEST_HEADERS
    optimization_test.cpp
    )

include_directories(${k52_SOURCE_DIR}/include ${K52_BOOST_INCLUDE_DIRS})

link_directories(${K52_BOOST_LIBRARY_DIRS})
add_executable(k52_bounded_nelder_mead_test ${K52_BOUNDED_NELDER_MEAD_TEST_HEADERS})
target_link_libraries(k52_bounded_nelder_mead_test 
                      k52_optimization_test_common 
                      k52-optimization-static 
                      k52-parallel-static 
                      ${K52_BOOST_LIBRARIES})

add_test(NAME "Nelder-Mead-method-test" COMMAND k52_bounded_nelder_mead_test)
