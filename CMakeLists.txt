cmake_minimum_required(VERSION 3.17)
project(cabbage)

set(CMAKE_CXX_STANDARD 20)

add_executable(cabbage main.cpp src/Piece.h src/Board.h src/Board.cpp)