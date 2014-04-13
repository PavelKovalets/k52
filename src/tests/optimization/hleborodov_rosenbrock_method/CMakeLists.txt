cmake_minimum_required(VERSION 2.8)
project(k52_hleborodov_rosenbrock_test)

# hleborodov rosenbrock tests executable
set(K52_HLEBORODOV_ROSENBROCK_SOURCE
    hleborodov_rosenbrock_method_test.cpp
    )

include_directories(${k52_SOURCE_DIR}/include ${K52_BOOST_INCLUDE_DIRS})
link_directories(${K52_BOOST_LIBRARY_DIRS})
add_executable(k52_hleborodov_rosenbrock_test ${K52_HLEBORODOV_ROSENBROCK_SOURCE})

target_link_libraries(k52_hleborodov_rosenbrock_test
                      k52_optimization_test_common
                      k52_optimization
                      k52_parallel
                      k52_common
                      ${K52_MPI_LIBRARIES}
                      ${K52_BOOST_LIBRARIES}
                      )

add_test(NAME "Hleborodov-Rosenbrock-test" COMMAND k52_hleborodov_rosenbrock_test)
