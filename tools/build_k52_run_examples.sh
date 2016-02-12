#!/usr/bin/env bash

#Build and install k52
cd ../source
mkdir tools_build
cd tools_build
cmake ..
make
make test
make install

#Build examples
cd ../../examples
mkdir tools_build
cd tools_build
cmake ..
make

#Run examples
./continuous_optimization/continuous_optimization_example
./genetic_algorithm/genetic_algorithm_example