cmake_minimum_required(VERSION 2.8)
project(k52_processing)

set(PROCESSING_COMMON_INCLUDE ${k52_SOURCE_DIR}/include/k52/processing)

# processing library
set(PROCESSING_HEADERS
    ${PROCESSING_COMMON_INCLUDE}/akima_wavelet_function.h
    ${PROCESSING_COMMON_INCLUDE}/bspline_wavelet_function.h
    ${PROCESSING_COMMON_INCLUDE}/cwt.h
    ${PROCESSING_COMMON_INCLUDE}/mhat_wavelet_function.h
    ${PROCESSING_COMMON_INCLUDE}/haar_wavelet_function.h
    ${PROCESSING_COMMON_INCLUDE}/morlet_wavelet_function.h
    ${PROCESSING_COMMON_INCLUDE}/pseudo_wavelet_function.h
    ${PROCESSING_COMMON_INCLUDE}/signal_based_wavelet_function.h
    ${PROCESSING_COMMON_INCLUDE}/spline.h
    ${PROCESSING_COMMON_INCLUDE}/spline_based_wavelet_function.h
    ${PROCESSING_COMMON_INCLUDE}/wavelet.h
    )

# processing source
set(PROCESSING_SOURCE
    akima_wavelet_function.cpp
    bspline_wavelet_function.cpp
    cwt.cpp
    mhat_wavelet_function.cpp
    haar_wavelet_function.cpp
    morlet_wavelet_function.cpp
    pseudo_wavelet_function.cpp
    signal_based_wavelet_function.cpp
    spline_based_wavelet_function.cpp
    wavelet.cpp
    )

include_directories(${k52_SOURCE_DIR}/src ${k52_SOURCE_DIR}/include ${K52_ALGLIB_INCLUDE_DIRS} ${K52_BOOST_INCLUDE_DIRS})
link_directories(${K52_ALGLIB_LIBRARY_DIRS})

set(k52_PROCESSING_LIB k52_processing)
add_library(${k52_PROCESSING_LIB} ${K52_LIBS_TYPE} ${PROCESSING_SOURCE} ${PROCESSING_HEADERS})

IF(K52_LIBS_TYPE_DYNAMIC)
    target_link_libraries(${k52_PROCESSING_LIB} ${K52_ALGLIB_LIBRARIES})
ENDIF()

INSTALL_TARGETS(${k52_LIB_DESTINATION} ${k52_PROCESSING_LIB})