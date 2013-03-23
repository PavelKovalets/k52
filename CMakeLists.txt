cmake_minimum_required(VERSION 2.6)
project(k52)

set(CMAKE_INSTALL_PREFIX ${k52_SOURCE_DIR})
set(k52_LIB_DESTINATION /lib)

set(AUTO_RESOLVE_PARALLEL_LIBS "ON")

# parallel library
add_subdirectory(src/parallel)

# optimization algoritms library
add_subdirectory(src/optimize)

# sound signal processing library
add_subdirectory(src/processing)

