cmake_minimum_required(VERSION 3.25)
project(unit)

add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
file(GLOB PROJECT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/**/*.cpp)

add_executable(unit ClientContainerTest.cpp ../Application.cpp ../Network.cpp ClientTest.cpp)
target_link_libraries(unit gtest gtest_main ws2_32)
target_include_directories(unit PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)