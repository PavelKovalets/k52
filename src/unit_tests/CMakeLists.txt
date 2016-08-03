if(BUILD_WITH_BOOST_UNIT_TESTS)
    set(PROJECT_NAME k52_unit_tests)
    project(${PROJECT_NAME})
    
    set(k52_UNIT_TESTS_SOURCE
        common/floating_point.test.cpp
        common/helpers.test.cpp
        optimization/linear_mutator.test.cpp
        common/random.test.cpp
        common/settings_manager.test.cpp
        dsp/akima_spline.test.cpp
        dsp/circular_convolution.test.cpp
        dsp/fourier_transform.test.cpp
        dsp/fourier_functional.test.cpp
        dsp/inverse_fourier_transform.test.cpp
        dsp/scale.test.cpp
        runner.cpp
        boost_test_tools_extensions.h
        boost_test_tools_extensions.cpp
    )

    include_directories(${k52_SOURCE_DIR}/include ${K52_BOOST_INCLUDE_DIRS})
    link_directories(${K52_BOOST_LIBRARY_DIRS})

    add_executable(${PROJECT_NAME} ${k52_UNIT_TESTS_SOURCE})

    set(k52_UNIT_TESTS_LINK_LIBS
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARIES}
        k52_dsp
        k52_common
        k52_parallel
        k52_optimization
        ${K52_MPI_LIBRARIES}
        ${K52_BOOST_LIBRARIES}
    )

    if(FFTW3_FOUND)
        set(k52_UNIT_TESTS_LINK_LIBS ${k52_UNIT_TESTS_LINK_LIBS} ${FFTW3_LIBRARIES})
    endif()

    target_link_libraries(${PROJECT_NAME} ${k52_UNIT_TESTS_LINK_LIBS})

    add_test(NAME "Unit_Tests" COMMAND ${PROJECT_NAME})

    set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER ${TESTS_SOLUTION_FOLDER_NAME})
endif(BUILD_WITH_BOOST_UNIT_TESTS)
