add_library( sol-chess-lib-piece src/piece.cpp )
add_library( sol-chess-lib-chessboard src/chessboard.cpp )

target_include_directories( sol-chess-lib-piece PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include )
target_include_directories( sol-chess-lib-chessboard PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include )
