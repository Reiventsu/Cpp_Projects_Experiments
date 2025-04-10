cmake_minimum_required(VERSION 3.20)
project(SnakeGame)

set(CMAKE_CXX_STANDARD 20)
find_package(raylib CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(NanoSVG CONFIG REQUIRED)
find_package(Stb REQUIRED)


add_executable(SnakeGame
        main.cpp
)
target_link_libraries(SnakeGame PRIVATE
        raylib glfw NanoSVG::nanosvg NanoSVG::nanosvgrast
)

target_include_directories(SnakeGame PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${Stb_INCLUDE_DIR}
)