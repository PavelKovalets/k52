cmake_minimum_required(VERSION 2.6)
project(k52_parallel)

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

include_directories(${k52_SOURCE_DIR}/include ${K52_BOOST_INCLUDE_DIRS})
link_directories(${K52_BOOST_LIBRARY_DIRS})

message("k52 boost libraries : ${K52_BOOST_LIBRARIES}")
message("k52 boost library dirs : ${K52_BOOST_LIBRARY_DIRS}")
message("k52 boost include dirs : ${K52_BOOST_INCLUDE_DIRS}")

add_library(k52_parallel_static STATIC ${PARALLEL_SOURCE})
INSTALL_TARGETS(${k52_LIB_DESTINATION} k52_parallel_static)

add_library(k52_parallel SHARED ${PARALLEL_SOURCE})
target_link_libraries(k52_parallel
                      ${K52_BOOST_LIBRARIES}
                      ${K52_MPI_LIBRARIES})
INSTALL_TARGETS(${k52_LIB_DESTINATION} k52_parallel)
