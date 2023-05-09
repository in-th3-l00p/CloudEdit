cmake_minimum_required(VERSION 3.25)
project(Server)

set(CMAKE_CXX_STANDARD 17)

add_executable(Server main.cpp Application.cpp Application.h Network.cpp Network.h Config.h)
