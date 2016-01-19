if(BUILD_WITH_BOOST_UNIT_TESTS)
    set(PROJECT_NAME k52_unit_tests)
    project(${PROJECT_NAME})
    
    set(k52_UNIT_TESTS_SOURCE
        common/helpers.test.cpp
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
    target_link_libraries(
        ${PROJECT_NAME}
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARIES}
        k52_dsp
        ${FFTW3_LIBRARIES}
        k52_common
        ${K52_BOOST_LIBRARIES}
    )

    add_test(NAME "Unit_Tests" COMMAND ${PROJECT_NAME})

    set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER ${TESTS_SOLUTION_FOLDER_NAME})
endif(BUILD_WITH_BOOST_UNIT_TESTS)
