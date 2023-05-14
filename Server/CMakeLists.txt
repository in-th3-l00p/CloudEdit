cmake_minimum_required(VERSION 3.25)
project(Server)

set(CMAKE_CXX_STANDARD 23)

add_executable(Server main.cpp Application.cpp Application.h Network.cpp Network.h Config.h)
target_link_libraries(Server PRIVATE ws2_32)

add_subdirectory(unit)