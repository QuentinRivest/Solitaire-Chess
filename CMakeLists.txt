cmake_minimum_required(VERSION 3.22)

project(SolitaireChess)

set(CMAKE_CXX_STANDARD 17)

add_executable(SolitaireChess ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp src/chessboard.cpp
                         ${CMAKE_CURRENT_SOURCE_DIR}/src/piece.cpp
                         ${CMAKE_CURRENT_SOURCE_DIR}/src/coord-conversions.cpp
              )
target_include_directories(SolitaireChess PUBLIC include)
