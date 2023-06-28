cmake_minimum_required(VERSION 3.22)
project(Sudoku)

set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/googletest/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/googletest)

add_subdirectory(./googletest)

set(LIBRARIES
        gtest
        pthread)

add_executable(Sudoku test.cpp sudoku.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

target_link_libraries(Sudoku gtest)