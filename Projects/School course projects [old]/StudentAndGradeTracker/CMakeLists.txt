cmake_minimum_required(VERSION 3.29)
project(StudentAndGradeTracker)

set(CMAKE_CXX_STANDARD 20)

add_executable(StudentAndGradeTracker
        main.cpp
)

target_include_directories(StudentAndGradeTracker PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)