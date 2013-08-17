cmake_minimum_required(VERSION 2.6)
project(k52_conjugate_gradient_test)

# conjugate gradient tests executable
set(K52_CONJUGATE_GRADIENT_TEST_SOURCE
    conjugate_gradient_test.cpp
    )

include_directories(${k52_SOURCE_DIR}/include ${K52_BOOST_INCLUDE_DIRS})
link_directories(${K52_BOOST_LIBRARY_DIRS})
add_executable(k52_conjugate_gradient_test ${K52_CONJUGATE_GRADIENT_TEST_SOURCE})

target_link_libraries(k52_conjugate_gradient_test
                      k52_optimization_test_common 
                      k52_optimization_static 
                      k52_parallel_static 
                      ${K52_MPI_LIBRARIES}
                      ${K52_BOOST_LIBRARIES})

add_test(NAME "Conjugate-Gradient-test" COMMAND k52_conjugate_gradient_test)
