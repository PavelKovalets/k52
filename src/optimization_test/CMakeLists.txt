cmake_minimum_required(VERSION 2.6)
project(k52_optimization_test)

# optimization algoritms tests executable
set(OPTIMIZATION_TEST_SOURCE
    optimization_test.cpp
    )

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
endif(Boost_FOUND)

include_directories(${k52_SOURCE_DIR}/include)
set(TARGET_EXE k52_optimization_test)
add_executable (${TARGET_EXE} ${OPTIMIZATION_TEST_SOURCE})

#TODO fix whith understanding of how CMake works!!!
#optimization
set(OPTIMIZATION_LIB_PATH ${k52_SOURCE_DIR}/build/src/optimization)
find_library(K52_OPTIMIZATION_LIBRARY k52-optimization-static ${OPTIMIZATION_LIB_PATH})
if(NOT K52_OPTIMIZATION_LIBRARY)
    message(SEND_ERROR "Failed to find K52_OPTIMIZATION_LIBRARY in ${OPTIMIZATION_LIB_PATH}")
    return()
endif(NOT K52_OPTIMIZATION_LIBRARY)
target_link_libraries(${TARGET_EXE} ${K52_OPTIMIZATION_LIBRARY})

#parallel
set(PARALLEL_LIB_PATH ${k52_SOURCE_DIR}/build/src/parallel)
find_library(K52_PARALLEL_LIBRARY k52-parallel-static ${PARALLEL_LIB_PATH})
if(NOT K52_PARALLEL_LIBRARY)
    message(SEND_ERROR "Failed to find K52_PARALLEL_LIBRARY in ${PARALLEL_LIB_PATH}")
    return()
endif(NOT K52_PARALLEL_LIBRARY)
target_link_libraries(${TARGET_EXE} ${K52_PARALLEL_LIBRARY})

#boost magic
#TODO remove all this trash!!!
find_package(Boost COMPONENTS mpi serialization thread system)
if(NOT Boost_THREAD_FOUND OR NOT Boost_SYSTEM_FOUND OR NOT Boost_MPI_FOUND OR NOT Boost_SERIALIZATION_FOUND)
    message("boost components [thread,system,mpi,serialization] have not been found : ${Boost_ERROR_REASON}")
    message(SEND_ERROR "Failed to find Boost COMPONENTS")
    return()
endif(NOT Boost_THREAD_FOUND OR NOT Boost_SYSTEM_FOUND OR NOT Boost_MPI_FOUND OR NOT Boost_SERIALIZATION_FOUND)
add_definitions(-DBUILD_WITH_MPI)
add_definitions(-DBUILD_WITH_BOOST_THREAD)
target_link_libraries(${TARGET_EXE} ${Boost_LIBRARIES})

#TODO remove MPI detection
find_package(MPI)
if(NOT MPI_FOUND)
    message("Mpi has been found")
endif(NOT MPI_FOUND)

if(MPI_FOUND)
    find_package(Boost COMPONENTS mpi serialization)
    if(NOT Boost_MPI_FOUND OR NOT Boost_SERIALIZATION_FOUND)
        message("boost components [mpi,serialization] have not been found : ${Boost_ERROR_REASON}")
    endif(NOT Boost_MPI_FOUND OR NOT Boost_SERIALIZATION_FOUND)

    if(Boost_MPI_FOUND AND Boost_SERIALIZATION_FOUND)
      set(CMAKE_C_COMPILER mpic)
      set(CMAKE_CXX_COMPILER mpicxx)
      add_definitions(-DBUILD_WITH_MPI)
    endif(Boost_MPI_FOUND AND Boost_SERIALIZATION_FOUND)
endif(MPI_FOUND)

