cmake_minimum_required(VERSION 3.0)
set(PROJECT_NAME genetic_algorithm_example)
project(${PROJECT_NAME})

set(BOOST_ROOT "")
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

find_package(k52 REQUIRED HINTS "${CMAKE_CURRENT_LIST_DIR}/../../install")

include_directories(${k52_INCLUDE_DIRS})
link_directories(${k52_LIBRARY_DIRS})

add_executable(${PROJECT_NAME} genetic_algorithm.cpp)

target_link_libraries(${PROJECT_NAME} ${k52_LIBRARIES})