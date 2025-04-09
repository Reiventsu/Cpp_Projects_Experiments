cmake_minimum_required(VERSION 3.20)
project(SnakeGame)

set(CMAKE_CXX_STANDARD 20)

add_executable(SnakeGame
        main.cpp
)
target_include_directories(SnakeGame PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)