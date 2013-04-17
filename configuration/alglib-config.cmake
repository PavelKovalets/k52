if(ALGLIB_ROOT)
  message("Using custom alglib root path : ${ALGLIB_ROOT}")
  find_library(ALGLIB_FOUND alglib ${ALGLIB_ROOT}/lib)

  if(ALGLIB_FOUND)
    message("Found library [alglib]")
    add_definitions(-DBUILD_WITH_ALGLIB)
    set(K52_ALGLIB_INCLUDE_DIRS  ${ALGLIB_ROOT}/cpp/src)
    set(K52_ALGLIB_LIBRARY_DIRS  ${ALGLIB_ROOT}/lib)
    set(K52_ALGLIB_LIBRARIES alglib)
  endif(ALGLIB_FOUND)

endif(ALGLIB_ROOT)
