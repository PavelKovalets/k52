#!/usr/bin/env bash

SCRIPT_DIR="$(cd "$(dirname ${BASH_SOURCE[0]})" && pwd)"
TOP_DIR="${SCRIPT_DIR}/.."
EXAMPLES_DIR="${TOP_DIR}/examples"

BUILD_ROOT="${TOP_DIR}/build"
K52_BUILD_DIR="${BUILD_ROOT}/k52"
EXAMPLES_BUILD_DIR="${BUILD_ROOT}/examples"

#Build and install k52
cd ${TOP_DIR}
[ -d ${K52_BUILD_DIR} ] && rm -r ${K52_BUILD_DIR}
mkdir -p ${K52_BUILD_DIR}
cd ${K52_BUILD_DIR}

cmake ${TOP_DIR}
[ $? -ne 0 ] && echo "k52 libraries cmake failed" && exit 1

make && make test && make install
[ $? -ne 0 ] && echo "k52 libraries build failed" && exit 1

#Build examples
[ -d ${EXAMPLES_BUILD_DIR} ] && rm -r ${EXAMPLES_BUILD_DIR}
mkdir -p ${EXAMPLES_BUILD_DIR}
cd ${EXAMPLES_BUILD_DIR}

cmake ${EXAMPLES_DIR}
[ $? -ne 0 ] && echo "k52 examples cmake failed" && exit 1

make
[ $? -ne 0 ] && echo "k52 examples build failed" && exit 1

#Run examples
echo "Run continuous_optimization_example:"
./continuous_optimization/continuous_optimization_example
[ $? -ne 0 ] && echo "k52 continious optimization example failed" && exit 1

echo "Run genetic_algorithm_example:"
mpiexec -np 2 ./genetic_algorithm/genetic_algorithm_example
[ $? -ne 0 ] && echo "k52 genetic algorithm example failed" && exit 1
