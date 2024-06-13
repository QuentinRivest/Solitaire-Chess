// (non-) member functions of Piece class forward declared here
#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <array>

#include "piece.h"

// a class with board properties
class Chessboard {
  public:
    Chessboard(int level);

    void printBoard();
    std::array<Piece, 16> getBoard() const;
    void updateBoard(const std::pair<int, int>& old_pos,
                     const std::pair<int, int>& new_pos);
    bool spotOccupied(const std::pair<int, int>& coordinate) const;
    std::vector<std::pair<int, int>> getMoves(
        const std::pair<int, int>& position) const;

  private:
    // array of all pieces on board, including empty spaces, in left-to-right,
    // top-to-bottom order
    std::array<Piece, 16> board_;
};

// converts 1A-format coordinate to two-digit coordinate
std::pair<int, int> displayToCoord(const std::string& num_char);

// converts two-digit coordinate to 1A-format coordinate
std::string coordToDisplay(const std::pair<int, int>& coord);

// converts two-digit coordinate to index usable by .at() function
int coordToIndex(const std::pair<int, int>& coord);

// converts index to two-digit coordinate
std::pair<int, int> indexToCoord(int index);

// takes an int representing the level the user is on in Solitaire Chess
// returns vector of ints representing the list of piece IDs in order of the
// arrangement of pieces at the start of the given level
std::array<int, 16> getStartingBoard(int level);

// returns vector of Pieces based on return value of getStartingBoard(level)
std::array<Piece, 16> setUpBoard(int level);

#endif