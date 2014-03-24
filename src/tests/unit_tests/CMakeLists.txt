if(BUILD_WITH_BOOST_UNIT_TESTS)
	project(k52_unit_tests)
	
	set(k52_UNIT_TESTS_SOURCE
		common/settings_manager.test.cpp)

	include_directories(${k52_SOURCE_DIR}/include ${K52_BOOST_INCLUDE_DIRS})
	link_directories(${K52_BOOST_LIBRARY_DIRS})

	add_executable(k52_unit_tests ${k52_UNIT_TESTS_SOURCE})
	target_link_libraries(k52_unit_tests
						  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARIES}
						  )

	add_test(NAME "Unit_Tests" COMMAND k52_unit_tests)	
endif(BUILD_WITH_BOOST_UNIT_TESTS)
