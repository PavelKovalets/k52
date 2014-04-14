cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME k52_bounded_nelder_mead_test)
project(${PROJECT_NAME})

# nelder mead tests executable
set(K52_BOUNDED_NELDER_MEAD_TEST_SOURCE
    bounded_nelder_mead_test.cpp
    )

include_directories(${k52_SOURCE_DIR}/include ${K52_BOOST_INCLUDE_DIRS})
link_directories(${K52_BOOST_LIBRARY_DIRS})
add_executable(${PROJECT_NAME} ${K52_BOUNDED_NELDER_MEAD_TEST_SOURCE})

target_link_libraries(${PROJECT_NAME} 
                      k52_optimization_test_common 
                      k52_optimization
                      k52_parallel
                      k52_common
                      ${K52_MPI_LIBRARIES}
                      ${K52_BOOST_LIBRARIES}
                      )

add_test(NAME "Nelder-Mead-method-test" COMMAND ${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER ${TESTS_SOLUTION_FOLDER_NAME})
