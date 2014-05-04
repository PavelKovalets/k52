cmake_minimum_required(VERSION 2.8)
project(k52_optimization)

set(OPTIMIZATION_COMMON_INCLUDE ${k52_SOURCE_DIR}/include/k52/optimization)

# optimization algoritms library
set(OPTIMIZATION_HEADERS
    ${OPTIMIZATION_COMMON_INCLUDE}/bounded_nelder_mead.h
    ${OPTIMIZATION_COMMON_INCLUDE}/chromosome.h
    ${OPTIMIZATION_COMMON_INCLUDE}/conjugate_gradient_method.h
    ${OPTIMIZATION_COMMON_INCLUDE}/continuous_objective_function.h
    ${OPTIMIZATION_COMMON_INCLUDE}/continuous_optimizer.h
    ${OPTIMIZATION_COMMON_INCLUDE}/discrete_objective_function.h
    ${OPTIMIZATION_COMMON_INCLUDE}/discrete_optimizer.h
    ${OPTIMIZATION_COMMON_INCLUDE}/generation_statistics.h
    ${OPTIMIZATION_COMMON_INCLUDE}/genetic_algorithm.h
    ${OPTIMIZATION_COMMON_INCLUDE}/grid_search.h
    ${OPTIMIZATION_COMMON_INCLUDE}/hleborodov_rosenbrock_method.h
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

    cache.h
    count_objective_function_task.h
    i_parameters_processor.h
    objective_function_counter.h
    objective_function_task_result.h
    optimization_parameters_processor.h
    optimization_task.h
    optimization_task_result.h
    simple_parameters_processor.h
    stored_value.h

    genetic_algorithm/mutator.h

    )

set(OPTIMIZE_SOURCE
    bounded_nelder_mead.cpp
    cache.cpp
    conjugate_gradient_method.cpp
    continuous_objective_function.cpp
    continuous_optimizer.cpp
    count_objective_function_task.cpp
    discrete_objective_function.cpp
    discrete_optimizer.cpp
    grid_search.cpp
    hleborodov_rosenbrock_method.cpp
    initialization_checker.cpp
    objective_function_counter.cpp
    objective_function_task_result.cpp
    optimization_parameters_processor.cpp
    optimization_task.cpp
    optimization_task_result.cpp
    random_search.cpp
    simple_parameters_processor.cpp

    genetic_algorithm/generation_statistics.cpp
    genetic_algorithm/genetic_algorithm.cpp
    genetic_algorithm/individual.cpp
    genetic_algorithm/mutator.cpp

    params/composite_discrete_parameters.cpp
    params/const_chromosome_size_paremeters.cpp
    params/continuous_parameters_array.cpp
    params/discrete_parameters.cpp
    params/double_parameter.cpp
    params/double_parameters_array.cpp
    params/int_parameter.cpp
    )

add_source_groups(genetic_algorithm params)

include_directories(${k52_SOURCE_DIR}/include ${K52_BOOST_INCLUDE_DIRS})
link_directories(${K52_BOOST_LIBRARY_DIRS})

set(k52_OPTIMIZE_LIB k52_optimization)
add_library(${k52_OPTIMIZE_LIB} ${K52_LIBS_TYPE} ${OPTIMIZE_SOURCE} ${OPTIMIZATION_HEADERS})

IF(K52_LIBS_TYPE_DYNAMIC)
    target_link_libraries(${k52_OPTIMIZE_LIB}
                          ${k52_COMMON_LIB}
                          ${k52_PARALLEL_LIB}
                          ${K52_MPI_LIBRARIES}
                          ${K52_BOOST_LIBRARIES}
                          )
ENDIF()

INSTALL_TARGETS(${k52_LIB_DESTINATION} ${k52_OPTIMIZE_LIB})