// definitions of (non-)member
#include <iostream>

#include "../include/piece.hpp"
#include "../include/piece-type-enum.hpp"


/* MEMBER FUNCTIONS */

// constructor for a chess piece
Piece::Piece(PieceType::PieceType piece_type, const std::pair<int, int>& position)
  : piece_type_(piece_type), position_(position), name_(createName(piece_type)),
    image_(createImage(piece_type)) {}

// returns the PieceType type of a chess piece
const PieceType::PieceType& Piece::getPieceType() const {
  return piece_type_;
}

const std::string& Piece::getName() const {
  return name_;
}

void Piece::setPosition(const std::pair<int, int>& position) {
  position_ = position;
}

const std::pair<int, int>& Piece::getPosition() const {
  return position_;
}

// returns the image of the chess piece
const std::array<std::string, 7>& Piece::getImage() const {
  return image_;
}



/* HELPER or NON-MEMBER FUNCTIONS */

namespace {

  // sets a name for chess piece given its piece type; used in Piece constructor
  std::string createName(PieceType::PieceType piece_type)
  {
    using namespace PieceType;
    if (piece_type == EMPTY)
    {
      return "Empty";
    }
    else if (piece_type == PAWN)
    {
      return "Pawn";
    }
    else if (piece_type == ROOK)
    {
      return "Rook";
    }
    else if (piece_type == KNIGHT)
    {
      return "Knight";
    }
    else if (piece_type == BISHOP)
    {
      return "Bishop";
    }
    else if (piece_type == QUEEN)
    {
      return "Queen";
    }
    else if (piece_type == KING)
    {
      return "King";
    }
    else
    {
      std::cout << "error: tried to create name for non-chess-piece\n";
      return "ERROR";
    }
  }

  // creates the image of a chess piece given the piece type
  std::array<std::string, 7> createImage(PieceType::PieceType piece_type) {
    using namespace PieceType;

    if (piece_type == EMPTY) {
      return {"|               ",
              "|               ",
              "|               ",
              "|               ",
              "|               ",
              "|               ",
              "----------------"};
    } if (piece_type == PAWN) {
      return {"|               ",
              "|       _       ",
              "|      (_)      ",
              "|     _/_\\_     ",
              "|    (_____)    ",
              "|               ",
              "----------------"};
    } else if (piece_type == ROOK) {
      return {"|               ",
              "|     |UUU|     ",
              "|      |_|      ",
              "|     _)_(_     ",
              "|    (_____)    ",
              "|               ",
              "----------------"};
    } else if (piece_type == KNIGHT) {
      return {"|               ",
              "|    ____|\\     ",
              "|    L__  |7    ",
              "|      /  |7    ",
              "|     (___)     ",
              "|    (_____)    ",
              "----------------"};
    } else if (piece_type == BISHOP) {
      return {"|               ",
              "|       o       ",
              "|      (/)      ",
              "|      {_}      ",
              "|     _)_(_     ",
              "|    (_____)    ",
              "----------------"};
    } else if (piece_type == QUEEN) {
      return {"|       o       ",
              "|     \\^^^/     ",
              "|     <___>     ",
              "|      )_(      ",
              "|     (___)     ",
              "|    (_____)    ",
              "----------------"};
    } else if (piece_type == KING) {
      return {"|      _+_      ",
              "|     \\___/     ",
              "|      )_(      ",
              "|     <___>     ",
              "|     (___)     ",
              "|    (_____)    ",
              "----------------"};
    } else {
      std::cout << "error: tried to set image of non-chess-piece.\n";
      return {"E", "R", "R", "O", "R", "!", "!"};
    }
  }

}
