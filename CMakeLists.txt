cmake_minimum_required(VERSION 3.22)

project(SolitaireChess)

set(CMAKE_CXX_STANDARD 17)

add_executable(src_files src/main.cpp src/chessboard.cpp src/piece.cpp src/coord-conversions.cpp)
target_include_directories(src_files PUBLIC include)
