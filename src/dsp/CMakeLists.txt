cmake_minimum_required(VERSION 2.8)
project(k52_dsp)

set(DSP_COMMON_INCLUDE ${k52_SOURCE_DIR}/include/k52/dsp)

# dsp library
set(DSP_HEADERS
    ${DSP_COMMON_INCLUDE}/akima_wavelet_function.h
    ${DSP_COMMON_INCLUDE}/bspline_wavelet_function.h
    ${DSP_COMMON_INCLUDE}/cwt.h
    ${DSP_COMMON_INCLUDE}/mhat_wavelet_function.h
    ${DSP_COMMON_INCLUDE}/haar_wavelet_function.h
    ${DSP_COMMON_INCLUDE}/morlet_wavelet_function.h
    ${DSP_COMMON_INCLUDE}/pseudo_wavelet_function.h
    ${DSP_COMMON_INCLUDE}/signal_based_wavelet_function.h
    ${DSP_COMMON_INCLUDE}/spline.h
    ${DSP_COMMON_INCLUDE}/spline_based_wavelet_function.h
    ${DSP_COMMON_INCLUDE}/wavelet.h
    ${DSP_COMMON_INCLUDE}/transform/fourier_transform.h
    ${DSP_COMMON_INCLUDE}/transform/i_fourier_transform.h
    ${DSP_COMMON_INCLUDE}/transform/inverse_fourier_transform.h
    ${DSP_COMMON_INCLUDE}/transform/circular_convolution.h)

# dsp source
set(DSP_SOURCE
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
    tranform/fourier_transform.cpp
    tranform/inverse_fourier_transform.cpp
    tranform/circular_convolution.cpp)

include_directories(${k52_SOURCE_DIR}/src ${k52_SOURCE_DIR}/include ${K52_ALGLIB_INCLUDE_DIRS} ${K52_BOOST_INCLUDE_DIRS})
link_directories(${K52_ALGLIB_LIBRARY_DIRS})

set(k52_DSP_LIB k52_dsp)
add_library(${k52_DSP_LIB} ${K52_LIBS_TYPE} ${DSP_SOURCE} ${DSP_HEADERS})

if(K52_LIBS_TYPE_DYNAMIC)
    target_link_libraries(${k52_DSP_LIB} ${K52_ALGLIB_LIBRARIES})
endif()

install_targets(${k52_LIB_DESTINATION} ${k52_DSP_LIB})
