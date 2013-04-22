cmake_minimum_required(VERSION 2.6)
project(k52-parallel)

# parallel library
set(PARALLEL_SOURCE
    statistics_aggregator.cpp
    sequential_worker_pool.cpp
    worker_pool_factory.cpp
    worker_statistics.cpp
    mpi/identifyable_objects_manager.cpp
    mpi/mpi_worker_pool.cpp
    mpi/delay_supplier.cpp
    thread/thread_worker_pool.cpp
    thread/thread_worker_pool_task.cpp
    )

include_directories(${k52_SOURCE_DIR}/src ${k52_SOURCE_DIR}/include ${K52_BOOST_INCLUDE_DIRS})
link_directories(${K52_BOOST_LIBRARY_DIRS})

message("k52 boost libraries : ${K52_BOOST_LIBRARIES}")
message("k52 boost library dirs : ${K52_BOOST_LIBRARY_DIRS}")
message("k52 boost include dirs : ${K52_BOOST_INCLUDE_DIRS}")

add_library(k52-parallel-static STATIC ${PARALLEL_SOURCE})
INSTALL_TARGETS(${k52_LIB_DESTINATION} k52-parallel-static)

add_library(k52-parallel SHARED ${PARALLEL_SOURCE})
target_link_libraries(k52-parallel ${K52_BOOST_LIBRARIES})
INSTALL_TARGETS(${k52_LIB_DESTINATION} k52-parallel)
