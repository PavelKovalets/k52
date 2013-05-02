cmake_minimum_required(VERSION 2.6)
project(k52_optimization)

set(OPTIMIZATION_COMMON_INCLUDE ${k52_SOURCE_DIR}/include/k52/optimization)

# optimization algoritms library
set(OPTIMIZATION_HEADERS
    ${OPTIMIZATION_COMMON_INCLUDE}/bounded_nelder_mead.h
    ${OPTIMIZATION_COMMON_INCLUDE}/generation_statistics.h
    ${OPTIMIZATION_COMMON_INCLUDE}/genetic_algorithm.h
    ${OPTIMIZATION_COMMON_INCLUDE}/grid_search.h
    ${OPTIMIZATION_COMMON_INCLUDE}/i_convertable_to_chromosome.h
    ${OPTIMIZATION_COMMON_INCLUDE}/i_objective_function.h
    ${OPTIMIZATION_COMMON_INCLUDE}/i_optimizer.h
    ${OPTIMIZATION_COMMON_INCLUDE}/individual_statistics.h
    ${OPTIMIZATION_COMMON_INCLUDE}/individual.h
    ${OPTIMIZATION_COMMON_INCLUDE}/initialization_checker.h
    ${OPTIMIZATION_COMMON_INCLUDE}/random_search.h
    ${OPTIMIZATION_COMMON_INCLUDE}/params/composite_discrete_parameters.h
    ${OPTIMIZATION_COMMON_INCLUDE}/params/const_chromosome_size_paremeters.h
    ${OPTIMIZATION_COMMON_INCLUDE}/params/continuous_parameters_array.h
    ${OPTIMIZATION_COMMON_INCLUDE}/params/discrete_parameters.h
    ${OPTIMIZATION_COMMON_INCLUDE}/params/double_parameter.h
    ${OPTIMIZATION_COMMON_INCLUDE}/params/double_parameters_array.h
    ${OPTIMIZATION_COMMON_INCLUDE}/params/i_continuous_parameters.h
    ${OPTIMIZATION_COMMON_INCLUDE}/params/i_discrete_parameters.h
    ${OPTIMIZATION_COMMON_INCLUDE}/params/i_parameters.h
    ${OPTIMIZATION_COMMON_INCLUDE}/params/int_parameter.h
    count_objective_function_task.h
    i_parameters_processor.h
    mutator.h
    objective_function_counter.h
    objective_function_task_result.h
    random.h
    simple_parameters_processor.h
    stored_value.h
    )

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
    random_search.cpp
    random.cpp
    simple_parameters_processor.cpp
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

add_library(k52_optimization_static STATIC ${OPTIMIZE_SOURCE} ${OPTIMIZATION_HEADERS})
INSTALL_TARGETS(${k52_LIB_DESTINATION} k52_optimization_static)

add_library (k52_optimization SHARED ${OPTIMIZE_SOURCE} ${OPTIMIZATION_HEADERS})
target_link_libraries(k52_optimization
                      k52_parallel_static
                      ${K52_MPI_LIBRARIES}
                      ${K52_BOOST_LIBRARIES}
                      )
INSTALL_TARGETS(${k52_LIB_DESTINATION} k52_optimization)
