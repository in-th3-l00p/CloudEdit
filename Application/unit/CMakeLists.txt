cmake_minimum_required(VERSION 3.25)
project(unit)

add_subdirectory(lib)
include_directories(${gTEST_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(unit)
target_link_libraries(unit gtest gtest_main)
target_include_directories(unit PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)