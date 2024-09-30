// (non-) member functions of Piece class forward declared here
#ifndef PIECE_H
#define PIECE_H

#include <array>
#include <string>
#include <utility>
#include <vector>

#include "piece-type-enum.h"

// a class with the properties of each chess piece
class Piece {
  public:
    Piece() = default;
    Piece(PieceType piece_type, const std::pair<int, int>& position);

    PieceType getPieceId() const;
    std::string getName() const;
    void setPosition(const std::pair<int, int>& position);
    std::pair<int, int> getPosition() const;
    void setRange();
    std::vector<std::pair<int, int>> getRange() const;
    std::vector<std::string> getImage() const;

  private:
    PieceType piece_type_;
    std::pair<int, int> position_;
    std::string name_;
    std::vector<std::pair<int, int>> range_;
    std::array<std::string, 7> image_;
};

// returns name based on piece ID
std::string createName(PieceType piece_type);

// returns true if coord param. exists in the grid of coordinates on the board
bool coordExists(std::pair<int, int> coord);

// takes piece ID and position of chess piece
// returns vector of int-int pairs for range of piece
std::vector<std::pair<int, int>> createRange(PieceType piece_type,
                                             const std::pair<int, int>&
                                             position);

// takes piece ID
// returns vector of std::string's representing image of chess piece
std::vector<std::string> createImage(PieceType piece_type);

#endif
