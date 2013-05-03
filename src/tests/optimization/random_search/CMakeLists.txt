cmake_minimum_required(VERSION 2.6)
project(k52_random_search_test)

# random search tests executable
set(K52_RANDOM_SEARCH_TEST_SOURCE
    random_search_test.cpp
    )

include_directories(${k52_SOURCE_DIR}/include ${K52_BOOST_INCLUDE_DIRS})
link_directories(${K52_BOOST_LIBRARY_DIRS})
add_executable(k52_random_search_test ${K52_RANDOM_SEARCH_TEST_SOURCE})

target_link_libraries(k52_random_search_test
                      k52_optimization_test_common 
                      k52_optimization_static 
                      k52_parallel_static 
                      ${K52_MPI_LIBRARIES}
                      ${K52_BOOST_LIBRARIES})

add_test(NAME "Random-Search-test" COMMAND k52_random_search_test)
