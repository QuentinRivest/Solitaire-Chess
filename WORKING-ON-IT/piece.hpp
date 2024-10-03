// (non-) member functions of Piece class forward declared here
#ifndef PIECE_H
#define PIECE_H

#include <array>
#include <string>
#include <utility>
#include <vector>

#include "piece-type-enum.hpp"

// a class with the properties of each chess piece
class Piece {
  public:
    Piece() = default;
    Piece(PieceType::PieceType piece_type, const std::pair<int, int>& position);

    const PieceType::PieceType& getPieceType() const;
    const std::string& getName() const;
    void setPosition(const std::pair<int, int>& position);
    const std::pair<int, int>& getPosition() const;
    void setRange();
    const std::vector<std::pair<int, int>>& getRange() const;
    const std::array<std::string, 7>& getImage() const;

  private:
    PieceType::PieceType piece_type_;
    std::pair<int, int> position_;
    std::string name_;
    std::vector<std::pair<int, int>> range_;
    std::array<std::string, 7> image_;
};

namespace {
  // returns name based on piece ID
  std::string createName(PieceType::PieceType piece_type);

  // takes piece ID and position of chess piece
  // returns vector of int-int pairs for range of piece
  std::vector<std::pair<int, int>> createRange(PieceType::PieceType piece_type,
                                               const std::pair<int, int>& position);

  // takes piece ID
  // returns vector of std::string's representing image of chess piece
  std::array<std::string, 7> createImage(PieceType::PieceType piece_type);
}

#endif
