set(K52_MPI_INCLUDE_PATH "")
set(K52_MPI_LIBRARY_PATH "")
set(K52_MPI_LIBRARIES "")

find_package(MPI)
if(MPI_FOUND)
  message("Mpi has been found")

  if(Boost_MPI_FOUND AND Boost_SERIALIZATION_FOUND)
    message("Using mpi")
    add_definitions(-DBUILD_WITH_MPI)
  endif(Boost_MPI_FOUND AND Boost_SERIALIZATION_FOUND)

endif(MPI_FOUND)

