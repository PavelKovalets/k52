set(K52_MPI_INCLUDE_PATH "")
set(K52_MPI_LIBRARY_PATH "")
set(K52_MPI_LIBRARIES "")

find_package(MPI)
if(MPI_CXX_FOUND)
  message("${K52_MESSAGE_PREFIX} Mpi has been found ${K52_MESSAGE_POSTFIX}")

  if(Boost_MPI_FOUND AND Boost_SERIALIZATION_FOUND)
    message("${K52_MESSAGE_PREFIX} Using mpi ${K52_MESSAGE_POSTFIX}")
    add_definitions(-DBUILD_WITH_MPI)
    include_directories(${MPI_CXX_INCLUDE_PATH})
    set(K52_MPI_LIBRARIES ${MPI_CXX_LIBRARIES})
    set(k52_LIBS ${k52_LIBS} ${MPI_CXX_LIBRARIES})
  endif(Boost_MPI_FOUND AND Boost_SERIALIZATION_FOUND)

endif(MPI_CXX_FOUND)

