cmake_minimum_required(VERSION 2.6)
project(k52-processing)

set(ALGLIB_ROOT /projects/Projects_Kafedra/alglib)
set(ALGLIB_INCLUDE ${ALGLIB_ROOT}/cpp/src)

set(PROCESSING_COMMON_INCLUDE ${k52_SOURCE_DIR}/include/k52/processing)

# processing library
set(PROCESSING_HEADERES
    ${PROCESSING_COMMON_INCLUDE}/bspline_wavelet_function.h
    ${PROCESSING_COMMON_INCLUDE}/cwt.h
    ${PROCESSING_COMMON_INCLUDE}/mhat_wavelet_function.h
    ${PROCESSING_COMMON_INCLUDE}/haar_wavelet_function.h
    ${PROCESSING_COMMON_INCLUDE}/morlet_wavelet_function.h
    ${PROCESSING_COMMON_INCLUDE}/pseudo_wavelet_function.h
    ${PROCESSING_COMMON_INCLUDE}/signal_based_wavelet_function.h
    ${PROCESSING_COMMON_INCLUDE}/wavelet.h
    )

# processing source
set(PROCESSING_SOURCE
    bspline_wavelet_function.cpp
    cwt.cpp
    mhat_wavelet_function.cpp
    haar_wavelet_function.cpp
    morlet_wavelet_function.cpp
    pseudo_wavelet_function.cpp
    signal_based_wavelet_function.cpp
    wavelet.cpp
    )

include_directories(${k52_SOURCE_DIR}/src ${k52_SOURCE_DIR}/include ${ALGLIB_INCLUDE})
add_library (k52-processing-static STATIC ${PROCESSING_SOURCE} ${PROCESSING_HEADERES})
add_library (k52-processing SHARED ${PROCESSING_SOURCE} ${PROCESSING_HEADERES})

INSTALL_TARGETS(${k52_LIB_DESTINATION} k52-processing-static)
INSTALL_TARGETS(${k52_LIB_DESTINATION} k52-processing)
