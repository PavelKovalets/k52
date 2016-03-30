# Module that searches for the FFTW3 lib

# Steps to use this module
# 1) Set FFTW3_ROOT_DIR variable to the path where FFTW3 is located (if necessary)
# 2) Call find_package(FFTW3) where needed
# 3) Use the variables that are set by the module:
#  a) FFTW3_FOUND
#  b) FFTW3_INCLUDE_DIR
#  c) FFTW3_LIBRARIES

find_path(
    FFTW3_INCLUDE_DIR fftw3.h 
    HINTS ${FFTW3_ROOT_DIR} 
    PATH_SUFFIXES include
)

find_library(
    FFTW3_LIBRARIES 
    NAMES fftw3 libfftw3.a libfftw3-3.a libfftw3-3
    HINTS ${FFTW3_ROOT_DIR} 
    PATH_SUFFIXES lib
)

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(FFTW3 DEFAULT_MSG
    FFTW3_LIBRARIES FFTW3_INCLUDE_DIR
)
