cmake_minimum_required(VERSION 3.20)
project(SpaceInvadersGame)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(raylib CONFIG REQUIRED)

add_executable(SpaceInvadersGame
        src/main.cpp
        src/spaceship.cpp
        src/spaceship.h
        src/game.cpp
        src/game.h
        src/laser.cpp
        src/laser.h
)
target_link_libraries(SpaceInvadersGame PRIVATE
        raylib glfw
)

target_include_directories(SpaceInvadersGame PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${Stb_INCLUDE_DIR}
)