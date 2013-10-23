# This cmake script detects available boost libraries
# and check mandatory boost header files
#
# If both boost_thread and related boost_system are found
# the BUILD_WITH_BOOST_THREAD will be defined
#
# If both boost_mpi and related boost_serialization are found
# the BUILD_WITH_MPI will be defined
#
# The variables below play role:
#   K52_BOOST_INCLUDE_DIRS contains path to the boost headers
#   K52_BOOST_LIBRARY_DIRS contains path to the boost libraries
#   K52_BOOST_LIBRARIES contains the list of available boost libraries

message("Resolving available parallel libraries")
if(BOOST_ROOT)
  message("Using custom boost root path : ${BOOST_ROOT}")
endif(BOOST_ROOT)

find_package(Boost)
if(NOT Boost_FOUND)
  message(FATAL_ERROR "Couldn't continue - boost library has not been found" ${Boost_ERROR_REASON})
endif(NOT Boost_FOUND)

message("Checking mandatory boost headers")
include(CheckIncludeFileCXX)
check_include_file_cxx(boost/shared_ptr.hpp     BOOST_SHARED_PTR_FOUND    -I${Boost_INCLUDE_DIRS})
check_include_file_cxx(boost/unordered_map.hpp  BOOST_UNORDERED_MAP_FOUND -I${Boost_INCLUDE_DIRS})
if(NOT BOOST_SHARED_PTR_FOUND OR NOT BOOST_UNORDERED_MAP_FOUND)
  message(FATAL_ERROR "Couldn't continue - not all boost headers are available")
endif(NOT BOOST_SHARED_PTR_FOUND OR NOT BOOST_UNORDERED_MAP_FOUND)

set(K52_BOOST_INCLUDE_DIRS ${Boost_INCLUDE_DIRS})
set(K52_BOOST_LIBRARY_DIRS ${Boost_LIBRARY_DIRS})
set(K52_BOOST_LIBRARIES)

find_package(Boost COMPONENTS thread system)
if(NOT Boost_THREAD_FOUND OR NOT Boost_SYSTEM_FOUND)
  message("boost components [thread,system] have not been found : ${Boost_ERROR_REASON}")
endif(NOT Boost_THREAD_FOUND OR NOT Boost_SYSTEM_FOUND)

if(Boost_THREAD_FOUND AND Boost_SYSTEM_FOUND)
  add_definitions(-DBUILD_WITH_BOOST_THREAD)
  set(Boost_USE_STATIC_LIBS ON)
  set(K52_BOOST_LIBRARIES ${K52_BOOST_LIBRARIES} boost_thread boost_system)
endif(Boost_THREAD_FOUND AND Boost_SYSTEM_FOUND)

find_package(Boost COMPONENTS mpi serialization)
if(NOT Boost_MPI_FOUND OR NOT Boost_SERIALIZATION_FOUND)
  message("boost components [mpi,serialization] have not been found : ${Boost_ERROR_REASON}")
endif(NOT Boost_MPI_FOUND OR NOT Boost_SERIALIZATION_FOUND)

if(Boost_MPI_FOUND AND Boost_SERIALIZATION_FOUND)
  set(K52_BOOST_LIBRARIES ${K52_BOOST_LIBRARIES} boost_mpi boost_serialization)
endif(Boost_MPI_FOUND AND Boost_SERIALIZATION_FOUND)

# Detecting Boost.Test library - unit test framework
find_package(Boost COMPONENTS unit_test_framework)
if(NOT Boost_UNIT_TEST_FRAMEWORK_FOUND)
  message("boost component [unit test framework] has not been found : ${Boost_ERROR_REASON}")
endif(NOT Boost_UNIT_TEST_FRAMEWORK_FOUND)

if(Boost_UNIT_TEST_FRAMEWORK_FOUND)
  add_definitions(-DBUILD_WITH_BOOST_UNIT_TESTS)
  set(BUILD_WITH_BOOST_UNIT_TESTS)
  set(K52_BOOST_LIBRARIES ${K52_BOOST_LIBRARIES} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARIES})
endif(Boost_UNIT_TEST_FRAMEWORK_FOUND)
