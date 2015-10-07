if(BUILD_WITH_BOOST_UNIT_TESTS)
    set(PROJECT_NAME k52_unit_tests)
    project(${PROJECT_NAME})
    
    set(k52_UNIT_TESTS_SOURCE
        common/settings_manager.test.cpp
        dsp/fourier_transform.test.cpp
        dsp/inverse_fourier_transform.test.cpp
        dsp/circular_convolution.test.cpp
        runner.cpp)

    include_directories(${k52_SOURCE_DIR}/include ${K52_BOOST_INCLUDE_DIRS})
    link_directories(${K52_BOOST_LIBRARY_DIRS})

    add_executable(${PROJECT_NAME} ${k52_UNIT_TESTS_SOURCE})
    target_link_libraries(${PROJECT_NAME}
                          ${Boost_UNIT_TEST_FRAMEWORK_LIBRARIES}
                          k52_dsp
                          k52_common
                          )

    add_test(NAME "Unit_Tests" COMMAND ${PROJECT_NAME})

    set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER ${TESTS_SOLUTION_FOLDER_NAME})
endif(BUILD_WITH_BOOST_UNIT_TESTS)
