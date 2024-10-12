// (non-) member functions of Piece class forward declared here
#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <array>
#include <string>
#include <utility>
#include <vector>

#include "piece.hpp"

// a class with board properties
class Chessboard {
  public:
    Chessboard(int level);

    void printBoard();
    const std::array<Piece, 16>& getBoard() const;

    void updateBoard(const std::pair<int, int>& old_pos,
                     const std::pair<int, int>& new_pos);
    bool spotOccupied(const std::pair<int, int>& coordinate) const;
    std::vector<std::pair<int, int>> getMoves(const std::pair<int, int>& position) const;

    Piece& operator[](int index);
    const Piece& operator[](int index) const;
    Piece& operator[](const std::pair<int, int>& coord);
    const Piece& operator[](const std::pair<int, int>& coord) const;

  private:
    // array of all pieces on board, including empty spaces, in left-to-right,
    // top-to-bottom order
    std::array<Piece, 16> board_;
};

namespace {
  // returns vector of Pieces based on return value of getStartingBoard(level)
  std::array<Piece, 16> setUpBoard(int level);

  // takes an int representing the level the user is on in Solitaire Chess
  // returns vector of ints representing the list of piece IDs in order of the
  // arrangement of pieces at the start of the given level
  std::array<PieceType::PieceType, 16> getLevelOutline(int level);
}

#endif
