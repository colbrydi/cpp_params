cmake_minimum_required(VERSION 2.6)
enable_testing()

add_executable(param_test parameterTest.cpp parameter.h)
add_test(param_test  param_test)

include_directories(${CMAKE_CURRENT_LIST_DIR})

add_executable(listTest listTest.cpp parameter.h)
add_test(listTest listTest)
