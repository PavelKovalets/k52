cmake_minimum_required(VERSION 2.6)
project(k52-optimize)

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

# optimization algoritms library
set(OPTIMIZE_SOURCE
    bounded_nelder_mead.cpp
    count_objective_function_task.cpp
    generation_statistics.cpp
    genetic_algorithm.cpp
    grid_search.cpp
    individual.cpp
    initialization_checker.cpp
    mutator.cpp
    objective_function_counter.cpp
    objective_function_task_result.cpp
    random.cpp
    params/composite_discrete_parameters.cpp
    params/const_chromosome_size_paremeters.cpp
    params/continuous_parameters_array.cpp
    params/discrete_parameters.cpp
    params/double_parameter.cpp
    params/double_parameters_array.cpp
    params/int_parameter.cpp
    )

if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  link_directories(${Boost_LIBRARY_DIRS})
endif(Boost_FOUND)

include_directories(${k52_SOURCE_DIR}/src ${k52_SOURCE_DIR}/include)
add_library (k52-optimization-static STATIC ${OPTIMIZE_SOURCE})
add_library (k52-optimization SHARED ${OPTIMIZE_SOURCE})
INSTALL_TARGETS(${k52_LIB_DESTINATION} k52-optimization-static)
INSTALL_TARGETS(${k52_LIB_DESTINATION} k52-optimization)
