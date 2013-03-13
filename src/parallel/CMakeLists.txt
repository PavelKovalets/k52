cmake_minimum_required(VERSION 2.6)
project(k52-parallel)

# parallel library
set(PARALLEL_SOURCE
    SequentialWorkerPool.cpp
    WorkerPoolFactory.cpp
    mpi/IdentifyableObjectsManager.cpp
    mpi/MpiWorkerPool.cpp
    thread/ThreadWorkerPool.cpp
    thread/ThreadWorkerPoolTask.cpp
    )

include_directories(${k52_SOURCE_DIR}/src ${k52_SOURCE_DIR}/include)
add_library (k52-parallel ${PARALLEL_SOURCE})

