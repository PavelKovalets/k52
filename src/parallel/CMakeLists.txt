cmake_minimum_required(VERSION 2.6)
project(k52_parallel)

set(PARALLEL_COMMON_INCLUDE ${k52_SOURCE_DIR}/include/k52/parallel)

# parallel library
set(PARALLEL_HEADERS
    ${PARALLEL_COMMON_INCLUDE}/i_task_result.h
    ${PARALLEL_COMMON_INCLUDE}/i_task.h
    ${PARALLEL_COMMON_INCLUDE}/i_worker_pool.h
    ${PARALLEL_COMMON_INCLUDE}/worker_pool_factory.h
    ${PARALLEL_COMMON_INCLUDE}/worker_statistics.h
    ${PARALLEL_COMMON_INCLUDE}/mpi/async_call_chain.h
    ${PARALLEL_COMMON_INCLUDE}/mpi/boost_mpi_declaration.h
    ${PARALLEL_COMMON_INCLUDE}/mpi/constants.h
    ${PARALLEL_COMMON_INCLUDE}/mpi/i_mpi_task_result.h
    ${PARALLEL_COMMON_INCLUDE}/mpi/i_mpi_task.h
    ${PARALLEL_COMMON_INCLUDE}/mpi/i_transferable.h
    ${PARALLEL_COMMON_INCLUDE}/mpi/identifyable_objects_manager.h
    statistics_aggregator.h
    sequential_worker_pool.h
    mpi/delay_supplier.h
    mpi/mpi_worker_pool.h
    thread/thread_safe_queue.h
    thread/thread_worker_pool_task.h
    thread/thread_worker_pool_templated.h
    thread/thread_worker_pool.h
    thread/worker.h
    )

set(PARALLEL_SOURCE
    statistics_aggregator.cpp
    sequential_worker_pool.cpp
    worker_pool_factory.cpp
    worker_statistics.cpp
    mpi/async_call_chain.cpp
    mpi/identifyable_objects_manager.cpp
    mpi/mpi_worker_pool.cpp
    mpi/delay_supplier.cpp
    thread/thread_worker_pool.cpp
    thread/thread_worker_pool_task.cpp
    )

include_directories(${k52_SOURCE_DIR}/include ${K52_BOOST_INCLUDE_DIRS})
link_directories(${K52_BOOST_LIBRARY_DIRS})

IF(BUILD_K52_STATIC)
    add_library(k52_parallel_static STATIC ${PARALLEL_SOURCE} ${PARALLEL_HEADERS})
    INSTALL_TARGETS(${k52_LIB_DESTINATION} k52_parallel_static)
ENDIF()

IF(BUILD_K52_DYNAMIC)
    add_library(k52_parallel_dynamic SHARED ${PARALLEL_SOURCE} ${PARALLEL_HEADERS})
    target_link_libraries(k52_parallel_dynamic
                          ${K52_BOOST_LIBRARIES}
                          ${K52_MPI_LIBRARIES})
    INSTALL_TARGETS(${k52_LIB_DESTINATION} k52_parallel_dynamic)
ENDIF()
