cmake_minimum_required(VERSION 3.29)
project(BankSimulator)

set(CMAKE_CXX_STANDARD 23)

add_executable(BankSimulator
        bankSimMain.cpp
)

target_include_directories(BankSimulator PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)