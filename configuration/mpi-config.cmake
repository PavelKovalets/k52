find_package(MPI)
if(NOT MPI_FOUND)
  set(CMAKE_C_COMPILER mpicc)
  set(CMAKE_CXX_COMPILER mpic++)
  message("Mpi has not been found")
endif(NOT MPI_FOUND)

