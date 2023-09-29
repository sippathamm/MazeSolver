cmake_minimum_required(VERSION 3.24)
project(MazeSolver)

set(CMAKE_CXX_STANDARD 17)

set(GLFW_H /opt/homebrew/Cellar/glfw/3.3.8/include/GLFW)
include_directories(${GLFW_H})
include_directories(include)

set(GLFW_LINK /opt/homebrew/Cellar/glfw/3.3.8/lib/libglfw.3.dylib)
link_libraries(${GLFW_LINK})

set(SOURCE_FILES
        include/Maze.h
        source/Maze.cpp
        main.cpp)

add_executable(MazeSolver ${SOURCE_FILES})

if (APPLE)
    target_link_libraries(MazeSolver "-framework OpenGL")
    target_link_libraries(MazeSolver "-framework GLUT")
endif ()
