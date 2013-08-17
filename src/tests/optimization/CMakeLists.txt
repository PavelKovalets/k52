cmake_minimum_required(VERSION 2.6)
project(k52_optimization_tests)

# static library with common code
add_subdirectory(common)

# Please add all optimization tests to this file
add_subdirectory(conjugate_gradient)
add_subdirectory(random_search)
add_subdirectory(bounded_nelder_mead)
add_subdirectory(hleborodov_rosenbrock_method)
add_subdirectory(genetic_algorithm)
