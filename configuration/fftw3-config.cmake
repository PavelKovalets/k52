if(FFTW3_ROOT)
  set(FFTW3_ROOT_DIR "${FFTW3_ROOT}")
  message("${K52_MESSAGE_PREFIX} Using custom fftw3 root path : ${FFTW3_ROOT_DIR} ${K52_MESSAGE_POSTFIX}")
endif(FFTW3_ROOT)

find_package(FFTW3)

if(FFTW3_FOUND)
  message("${K52_MESSAGE_PREFIX} Found library [fftw3] : ${FFTW3_LIBRARIES} ${K52_MESSAGE_POSTFIX}")
  add_definitions(-DBUILD_WITH_FFTW3)
endif(FFTW3_FOUND)

if(NOT FFTW3_FOUND)
  message(WARNING "${K52_MESSAGE_PREFIX} fftw3 has not been found. FFT depended code will fail to execute. ${K52_MESSAGE_POSTFIX}")
endif(NOT FFTW3_FOUND)
