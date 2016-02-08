cmake_minimum_required(VERSION 2.8)
project(k52_common)

set(COMMON_INCLUDE ${k52_SOURCE_DIR}/include/k52/common)

set(COMMON_HEADERS
    ${COMMON_INCLUDE}/disallow_copy_and_assign.h
    ${COMMON_INCLUDE}/i_cloneable.h
    ${COMMON_INCLUDE}/random.h
    ${COMMON_INCLUDE}/settings_manager.h
    ${COMMON_INCLUDE}/constants.h
    ${COMMON_INCLUDE}/helpers.h
)

set(COMMON_SOURCE
    random.cpp
    constants.cpp
    helpers.cpp
)

include_directories(${k52_SOURCE_DIR}/include ${K52_BOOST_INCLUDE_DIRS})
link_directories(${K52_BOOST_LIBRARY_DIRS})

set(k52_COMMON_LIB k52_common)
add_library(${k52_COMMON_LIB} ${K52_LIBS_TYPE} ${COMMON_SOURCE} ${COMMON_HEADERS})

IF(K52_LIBS_TYPE_DYNAMIC)
    target_link_libraries(${k52_COMMON_LIB}
                          ${K52_BOOST_LIBRARIES}
                          )
ENDIF()

install(TARGETS ${k52_COMMON_LIB} DESTINATION ${k52_LIB_DESTINATION})