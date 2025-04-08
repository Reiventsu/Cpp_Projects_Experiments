cmake_minimum_required(VERSION 3.20)
project(WeatherSorter)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(WeatherSorter
        main.cpp
)

target_include_directories(WeatherSorter PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)