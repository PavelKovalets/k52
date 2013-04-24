cmake_minimum_required(VERSION 2.6)
project(k52_memory_consumption_test)

# memory tests executable
set(K52_MEMORY_CONSUMPTION_TEST_SOURCE
    memory_consumption_test.cpp
    )

include_directories(${k52_SOURCE_DIR}/include ${K52_BOOST_INCLUDE_DIRS})
link_directories(${K52_BOOST_LIBRARY_DIRS})
add_executable(k52_memory_consumption_test ${K52_MEMORY_CONSUMPTION_TEST_SOURCE})

target_link_libraries(k52_memory_consumption_test
                      k52_optimization_test_common 
                      k52_optimization_static 
                      k52_parallel_static 
                      ${K52_BOOST_LIBRARIES})

add_test(NAME "Memory-test" COMMAND k52_memory_consumption_test)
