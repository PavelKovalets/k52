cmake_minimum_required(VERSION 2.6)
project(k52_optimize)

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

include_directories(${k52_SOURCE_DIR}/include ${K52_BOOST_INCLUDE_DIRS})
link_directories(${K52_BOOST_LIBRARY_DIRS})

add_library(k52_optimization_static STATIC ${OPTIMIZE_SOURCE})
INSTALL_TARGETS(${k52_LIB_DESTINATION} k52_optimization_static)

add_library (k52_optimization SHARED ${OPTIMIZE_SOURCE})
target_link_libraries(k52_optimization
                      k52_parallel_static
                      ${K52_MPI_LIBRARIES}
                      ${K52_BOOST_LIBRARIES}
                      )
INSTALL_TARGETS(${k52_LIB_DESTINATION} k52_optimization)
