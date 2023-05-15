cmake_minimum_required(VERSION 3.25)
project(Application)

set(CMAKE_CXX_STANDARD 20)

include_directories(lib/SDL2/include)
include_directories(lib/SDL2_ttf/include)
add_executable(Application main.cpp Window.cpp Window.h Configuration.h Application.cpp Application.h EntitySystem.cpp EntitySystem.h NameContainer.h Widgets.cpp Widgets.h Math.cpp Math.h Color.h)
target_link_libraries(Application PRIVATE
        ${CMAKE_SOURCE_DIR}/lib/SDL2/lib/SDL2main.lib
        ${CMAKE_SOURCE_DIR}/lib/SDL2/lib/SDL2.lib
        ${CMAKE_SOURCE_DIR}/lib/SDL2_ttf/lib/SDL2_ttf.lib
)

#add_subdirectory(unit)