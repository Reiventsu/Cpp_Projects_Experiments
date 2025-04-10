cmake_minimum_required(VERSION 3.29)
project(BMICalculator)

set(CMAKE_CXX_STANDARD 20)

add_executable(BMICalculator
        Kalkylator.cpp
)

target_include_directories(BMICalculator PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)