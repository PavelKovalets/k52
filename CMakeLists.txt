cmake_minimum_required(VERSION 2.8)
project(k52)

# Install platform specific git pre-commit hooks
#if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
#  message("Linux system has been detected. Installing linux specific pre-commit git hook")
#  file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/source-control/linux-pre-commit-hook"
#       DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/.git/hooks")
#  file(RENAME "${CMAKE_CURRENT_SOURCE_DIR}/.git/hooks/linux-pre-commit-hook"
#              "${CMAKE_CURRENT_SOURCE_DIR}/.git/hooks/pre-commit")
#endif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")

enable_testing()
set(K52_MESSAGE_PREFIX "\n->-> K52 MESSAGE <-<- :")
set(K52_MESSAGE_POSTFIX "\n")
include(k52.config)
include(configuration/common-config.cmake)
include(configuration/alglib-config.cmake)
include(configuration/boost-config.cmake)
include(configuration/mpi-config.cmake)

set(CMAKE_INSTALL_PREFIX ${k52_SOURCE_DIR})
set(k52_LIB_DESTINATION /lib)

### Libraries
# parallel library
add_subdirectory(src/parallel)

# optimization algoritms library
add_subdirectory(src/optimization)

# sound signal processing library
add_subdirectory(src/processing)

## Test applications
# optimization algorithms library tests
add_subdirectory(src/tests)
