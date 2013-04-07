cmake_minimum_required(VERSION 2.6)
project(k52-processing)

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


if(ALGLIB_ROOT)
  set(ALGLIB_INCLUDE ${ALGLIB_ROOT}/cpp/src)
  set(ALGLIB_LIB ${ALGLIB_ROOT}/lib)
endif(ALGLIB_ROOT)

find_library(ALGLIB_FOUND alglib ${ALGLIB_ROOT}/lib)
if(ALGLIB_FOUND)
  message("Found library [alglib]")
  add_definitions(-DBUILD_WITH_ALGLIB)
  set(PROCESSING_THIRD_PARTY_LIBS ${PROCESSING_THIRD_PARTY_LIBS} alglib)
  link_directories(${ALGLIB_LIB})
endif(ALGLIB_FOUND)

include_directories(${k52_SOURCE_DIR}/src ${k52_SOURCE_DIR}/include ${ALGLIB_INCLUDE} ${K52_BOOST_INCLUDE_DIRS})
add_library(k52-processing-static STATIC ${PROCESSING_SOURCE} ${PROCESSING_HEADERS})
add_library(k52-processing SHARED ${PROCESSING_SOURCE} ${PROCESSING_HEADERS})
target_link_libraries(k52-processing ${PROCESSING_THIRD_PARTY_LIBS})

INSTALL_TARGETS(${k52_LIB_DESTINATION} k52-processing-static)
INSTALL_TARGETS(${k52_LIB_DESTINATION} k52-processing)
