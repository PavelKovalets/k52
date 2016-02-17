#!/usr/bin/env bash

#Build and install k52
cd ..
mkdir tools_build
cd tools_build
cmake ..
make
make test
make install

#Build examples
cd ../examples
mkdir tools_build
cd tools_build
cmake ..
make

#Run examples
echo Run continuous_optimization_example:
./continuous_optimization/continuous_optimization_example

echo Run genetic_algorithm_example:
mpiexec -np 2 ./genetic_algorithm/genetic_algorithm_example