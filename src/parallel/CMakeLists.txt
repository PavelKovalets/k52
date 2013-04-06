cmake_minimum_required(VERSION 2.6)
project(k52-parallel)

if(AUTO_RESOLVE_PARALLEL_LIBS)
  message("Resolving available parallel libraries")

  find_package(Boost COMPONENTS thread system)
  if(NOT Boost_THREAD_FOUND OR NOT Boost_SYSTEM_FOUND)
    message("boost components [thread,system] have not been found : ${Boost_ERROR_REASON}")
  endif(NOT Boost_THREAD_FOUND OR NOT Boost_SYSTEM_FOUND)
  
  if(Boost_THREAD_FOUND AND Boost_SYSTEM_FOUND)
    add_definitions(-DBUILD_WITH_BOOST_THREAD)
  endif(Boost_THREAD_FOUND AND Boost_SYSTEM_FOUND)
  
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
endif(AUTO_RESOLVE_PARALLEL_LIBS)

# parallel library
set(PARALLEL_SOURCE
    statistics_aggregator.cpp
    sequential_worker_pool.cpp
    worker_pool_factory.cpp
    worker_statistics.cpp
    mpi/identifyable_objects_manager.cpp
    mpi/mpi_worker_pool.cpp
    thread/thread_worker_pool.cpp
    thread/thread_worker_pool_task.cpp
    )

if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  link_directories(${Boost_LIBRARY_DIRS})
endif(Boost_FOUND)

include_directories(${k52_SOURCE_DIR}/src ${k52_SOURCE_DIR}/include)
add_library (k52-parallel-static STATIC ${PARALLEL_SOURCE})
add_library (k52-parallel SHARED ${PARALLEL_SOURCE})

if(Boost_MPI_FOUND AND Boost_SERIALIZATION_FOUND)
  target_link_libraries(k52-parallel boost_mpi boost_serialization)
endif(Boost_MPI_FOUND AND Boost_SERIALIZATION_FOUND)

if(Boost_THREAD_FOUND AND Boost_SYSTEM_FOUND)
  target_link_libraries(k52-parallel boost_thread boost_system)
endif(Boost_THREAD_FOUND AND Boost_SYSTEM_FOUND)

INSTALL_TARGETS(${k52_LIB_DESTINATION} k52-parallel-static)
INSTALL_TARGETS(${k52_LIB_DESTINATION} k52-parallel)
