cmake_minimum_required(VERSION 2.6)
project(k52_settings_manager_test)

set(K52_SETTINGS_MANAGER_TEST_SOURCE
    settings_manager_test_main.cpp
    )

include_directories(${k52_SOURCE_DIR}/include ${K52_BOOST_INCLUDE_DIRS})
add_executable(k52_settings_manager_test ${K52_SETTINGS_MANAGER_TEST_SOURCE})

add_test(NAME "Settings-manager-test" COMMAND k52_settings_manager_test)
