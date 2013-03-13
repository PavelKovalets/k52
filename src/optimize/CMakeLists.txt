cmake_minimum_required(VERSION 2.6)
project(k52-optimize)

# optimization algoritms library
set(OPTIMIZE_SOURCE
    BoundedNelderMead.cpp
    BruteForceSearch.cpp
    CountObjectiveFunctionTask.cpp
    GenerationStatistics.cpp
    GeneticAlgorithm.cpp
    GridSearch.cpp
    Individual.cpp
    InitializationChecker.cpp
    Mutator.cpp
    ObjectiveFunctionCounter.cpp
    ObjectiveFunctionTaskResult.cpp
    Random.cpp
    params/CompositeDiscreteParameters.cpp
    params/ConstChromosomeSizeParemeters.cpp
    params/ContinuousParametersArray.cpp
    params/DiscreteParameters.cpp
    params/DoubleParameter.cpp
    params/DoubleParametersArray.cpp
    params/IntParameter.cpp
    )

message (${k52_SOURCE_DIR}/src)

include_directories(${k52_SOURCE_DIR}/src ${k52_SOURCE_DIR}/include)
add_library (k52-optimize ${OPTIMIZE_SOURCE})
