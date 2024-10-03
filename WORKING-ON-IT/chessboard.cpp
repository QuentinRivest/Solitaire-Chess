#include <iostream>

#include "chessboard.hpp"
#include "coord-conversions.hpp"
#include "piece.hpp"
#include "piece-type-enum.hpp"


/* MEMBER FUNCTIONS */

// constructor for chessboard
Chessboard::Chessboard(int level)
    : board_(setUpBoard(level)) {}

// prints out the visual of what the board currently looks like
void Chessboard::printBoard() {
    std::cout << "   -----------------------------------------------------"
              << "------------\n";
    // prints out all rows of board
    for (int i = 0; i <= 12; i += 4) {
        // prints out one row of the board
        for (int j = 0; j <= 6; j++) {
            if (j == 2) {
                std::cout << " " << 4 - (i / 4) << " ";
            } else {
                std::cout << "   ";
            }
            // prints out one line, one character high
            for (int k = 0; k <= 3; k++) {
                const std::array<std::string, 7>& image = board_[i+k].getImage();
                std::cout << image[j];
            }
            if (j == 6) {
                std::cout << "-\n";
            } else {
                std::cout << "|\n";
            }
        }
    }
    std::cout << "           A               B               C"
              << "               D\n";
}

// returns vector of pieces representing the current board
const std::array<Piece, 16>& Chessboard::getBoard() const {
  return board_;
}

// updates the board by replacing the Piece obj at 'new_pos' with the Piece obj
// at 'old_pos';
// also changes Piece obj at 'old_pos' to an empty Piece
void Chessboard::updateBoard(const std::pair<int, int>& old_pos,
                             const std::pair<int, int>& new_pos) {
  // sets Piece obj at 'new_pos' equal to Piece obj at 'old_pos'
  (*this)[new_pos] = (*this)[old_pos];
  // resets the moved Piece obj's stored position value
  (*this)[new_pos].setPosition(new_pos);
  // resets the moved Piece obj/s stored range vector value
  (*this)[new_pos].setRange();
  // sets Piece obj at 'old_pos' equal to an empty Piece obj
  (*this)[old_pos] = Piece{PieceType::PieceType::EMPTY, old_pos};
}

// returns true if the spot on the board at the given coordinate coord has a
// chess piece on it, false if spot is empty or not on board
bool Chessboard::spotOccupied(const std::pair<int, int>& coord) const {
  if (!Coords::coordExists(coord) ||
      (*this)[coord].getPieceType() == PieceType::PieceType::EMPTY) {
    return false;
  }
  return true;
}

// returns vector of int-int pairs representing the coordinates on the board to
// which a piece at the given coordinate coord can move
// the criteria for a piece to be able to move somewhere is if that where is an
// existent coordinate on the board, and that coordinate is occupied
std::vector<std::pair<int, int>> Chessboard::getMoves(const std::pair<int, int>& position) const {
  // if 'position' doesn't exist on the board, print "error..." and return {-1,-1}
  if (!Coords::coordExists(position)) {
    std::cout << "error: used non-existent coordinate to get moves.\n";
    return {{-1, -1}};
  }

  // construct new Piece obj 'piece' equal to Piece obj at coord of 'position';
  // this way 'piece' can be used each time rather than
  // '(*this)[position]'
  Piece piece = (*this)[position];
  std::vector<std::pair<int, int>> moves{};

  // if 'piece' is a bishop or queen (i.e., if it moves diagonally)
  if ((piece.getPieceType() == 4) || (piece.getPieceType() == 5)) {
    for (const std::pair<int, int>& range_coord : piece.getRange()) {
      // if 'range_coord' is NE of 'piece''s position,
      // and if 'range_coord' is occupied by another piece...
      if ((range_coord.first > position.first) &&
          (range_coord.second > position.second) &&
          (spotOccupied(range_coord))) {
        // ...add that coordinate to 'piece''s possible moves...
        moves.push_back(range_coord);
        // ...and break loop
        // (since, if there's a piece in a given direction, 'piece' can't go
        // any further that direction)
        break;
      }
    }
    // for each coordinate in 'piece''s range...
    for (const std::pair<int, int>& range_coord : piece.getRange()) {
      // if 'range_coord' is NW of 'piece''s position,
      // and if 'range_coord' is occupied by another piece...
      if ((range_coord.first > position.first) &&
          (range_coord.second < position.second) &&
          (spotOccupied(range_coord))) {
        // ...add that coordinate to 'piece''s possible moves...
        moves.push_back(range_coord);
        // ...and break loop
        // (since, if there's a piece in a given direction, 'piece' can't go
        // any further that direction)
        break;
      }
    }
    // for each coordinate in 'piece''s range...
    for (const std::pair<int, int>& range_coord : piece.getRange()) {
      // if 'range_coord' is SE of 'piece''s position,
      // and if 'range_coord' is occupied by another piece...
      if ((range_coord.first < position.first) &&
          (range_coord.second > position.second) &&
          (spotOccupied(range_coord))) {
        // ...add that coordinate to 'piece''s possible moves...
        moves.push_back(range_coord);
        // ...and break loop
        // (since, if there's a piece in a given direction, 'piece' can't go
        // any further that direction)
        break;
      }
    }
    // for each coordinate in 'piece''s range...
    for (const std::pair<int, int>& range_coord : piece.getRange()) {
      // if 'range_coord' is SW of 'piece''s position,
      // and if 'range_coord' is occupied by another piece...
      if ((range_coord.first < position.first) &&
          (range_coord.second < position.second) &&
          (spotOccupied(range_coord))) {
        // ...add that coordinate to 'piece''s possible moves...
        moves.push_back(range_coord);
        // ...and break loop
        // (since, if there's a piece in a given direction, 'piece' can't go
        // any further that direction)
        break;
      }
    }
  }

  // bishop/queen conditional is before others because if 'piece' is a queen,
  // it'll get its diagonal moves first in the above conditional block,
  // and then it's horizontal/vertical moves in the rook/queen conditional
  // block below

  // if the 'piece' is an empty spot
  if (piece.getPieceType() == 0) {
    std::cout << "error: tried to get moves of empty piece.\n";
    return {{0, 0}};
  } else if ((piece.getPieceType() == 1) || (piece.getPieceType() == 3) ||
             (piece.getPieceType() == 6)) {  // if 'piece' is pawn, knight, king
    // for each coordinate in 'piece''s range...
    for (const std::pair<int, int>& coord : piece.getRange()) {
      // ...if that coordinate is occupied by another Piece obj...
      if (spotOccupied(coord)) {
        // ...add that coordinate to 'piece''s possible moves
        // (since, for this game, each move has to be an attack)
        moves.push_back(coord);
      }
    }
    return moves;
  } else if ((piece.getPieceType() == 2) || (piece.getPieceType() == 5)) {
      // ^if piece is a rook or queen (i.e., vertical/horizontal-moving piece)
    // (4 diff. for each loops for 4 diff. directions the piece could go)
    // for each coordinate in 'piece''s range...
    for (const std::pair<int, int>& range_coord : piece.getRange()) {
      // if 'range_coord' is strictly NORTH (not NW/NE) of 'piece''s position,
      // and if 'range_coord' is occupied by another piece...
      if ((range_coord.first > position.first) &&
          (range_coord.second == position.second) &&
          (spotOccupied(range_coord))) {
        // ...add that coordinate to 'piece''s possible moves...
        moves.push_back(range_coord);
        // ...and break loop
        // (since, if there's a piece in a given direction, 'piece' can't go
        // any further that direction)
        break;
      }
    }
    // for each coordinate in 'piece''s range...
    for (const std::pair<int, int>& range_coord : piece.getRange()) {
      // if 'range_coord' is strictly SOUTH (not SW/SE) of 'piece''s position,
      // and if 'range_coord' is occupied by another piece...
      if ((range_coord.first < position.first) &&
          (range_coord.second == position.second) &&
          (spotOccupied(range_coord))) {
        // ...add that coordinate to 'piece''s possible moves...
        moves.push_back(range_coord);
        // ...and break loop
        // (since, if there's a piece in a given direction, 'piece' can't go
        // any further that direction)
        break;
      }
    }
    // for each coordinate in 'piece''s range...
    for (const std::pair<int, int>& range_coord : piece.getRange()) {
      // if 'range_coord' is strictly EAST (not NE/SE) of 'piece''s position,
      // and if 'range_coord' is occupied by another piece...
      if ((range_coord.first == position.first) &&
          (range_coord.second > position.second) &&
          (spotOccupied(range_coord))) {
        // ...add that coordinate to 'piece''s possible moves...
        moves.push_back(range_coord);
        // ...and break loop
        // (since, if there's a piece in a given direction, 'piece' can't go
        // any further that direction)
        break;
      }
    }
    // for each coordinate in 'piece''s range...
    for (const std::pair<int, int>& range_coord : piece.getRange()) {
      // if 'range_coord' is strictly WEST (not NW/SW) of 'piece''s position,
      // and if 'range_coord' is occupied by another piece...
      if ((range_coord.first == position.first) &&
          (range_coord.second < position.second) &&
          (spotOccupied(range_coord))) {
        // ...add that coordinate to 'piece''s possible moves...
        moves.push_back(range_coord);
        // ...and break loop
        // (since, if there's a piece in a given direction, 'piece' can't go
        // any further that direction)
        break;
      }
    }
    return moves;
  } else {
    std::cout << "error: tried to get moves of non-existent piece.\n";
    moves.push_back({-1, -1});
  }

  return moves;
}



/* OPERATOR OVERLOADS */

Piece& Chessboard::operator[](int index) {
  return board_[index];
}
const Piece& Chessboard::operator[](int index) const {
  return board_[index];
}

Piece& Chessboard::operator[](const std::pair<int, int> &coord) {
  // returns an index int within the range 0-15,
  return operator[]( (-4) * ((coord.first) - 4) + ((coord.second) - 1) );
}
const Piece& Chessboard::operator[](const std::pair<int, int> &coord) const {
  // returns an index int within the range 0-15,
  return operator[]( (-4) * ((coord.first) - 4) + ((coord.second) - 1) );
}

/* HELPER or NON-MEMBER FUNCTIONS */

namespace {

  // returns vector of Pieces based on return value of getLevelOutline(level)
  std::array<Piece, 16> setUpBoard(int level) {
    // creates a list of all the piece types in left-right, top-bottom order, and in
    // the order they'll be in the beginning of the level number in the parameter
    std::array<PieceType::PieceType, 16> piece_type_list(getLevelOutline(level));

    // creates an array of Piece objects and fills it with the correct pieces at
    // the correct places according to the piece_type_list array
    std::array<Piece, 16> chess_board{};
    for (int i = 0; i < 16; i ++) {
      // creates a Piece with two parameters: piece type in the piece_type_list array at
      // index "counter", and a std::pair<int, int> converted from an int index
      Piece piece{piece_type_list.at(i), Coords::indexToCoord(i)};
      // add Piece object that was just created to chess_board array
      chess_board.at(i) = std::move(piece);
    }

    return chess_board;
  }

  // takes an int representing the level the user is on in Solitaire Chess
  // returns array of ints representing the list of piece types in left-to-right,
  // top-to-bottom order (like you'd read a book in English)
  // 0 = empty, 1 = pawn, 2 = rook, 3 = knight, 4 = bishop, 5 = queen, 6 = king
  std::array<PieceType::PieceType, 16> getLevelOutline(int level) {
    using namespace PieceType;
    if (level == 0) { return {EMPTY, EMPTY, ROOK, EMPTY,
                              QUEEN, PAWN, EMPTY, EMPTY,
                              KNIGHT, EMPTY, EMPTY, EMPTY,
                              EMPTY, EMPTY, EMPTY, EMPTY}; // pg.9

    } else if (level == 1) { return {EMPTY, EMPTY, EMPTY, EMPTY,
                                     EMPTY, ROOK, EMPTY, KNIGHT,
                                     BISHOP, KNIGHT, EMPTY, EMPTY,
                                     EMPTY, EMPTY, EMPTY, EMPTY}; // pg.7

    } else if (level == 2) { return {ROOK, EMPTY, QUEEN, EMPTY,
                                    EMPTY, PAWN, EMPTY, EMPTY,
                                    EMPTY, EMPTY, EMPTY, EMPTY,
                                    KNIGHT, EMPTY, EMPTY, EMPTY}; // pg.11

    } else if (level == 3) { return {EMPTY, KNIGHT, EMPTY, EMPTY,
                                    EMPTY, QUEEN, EMPTY, ROOK,
                                    PAWN, EMPTY, EMPTY, EMPTY,
                                    EMPTY, EMPTY, EMPTY, EMPTY}; // pg.13

    } else if (level == 4) { return {EMPTY, EMPTY, QUEEN, EMPTY,
                                    EMPTY, EMPTY, ROOK, EMPTY,
                                    KNIGHT, EMPTY, EMPTY, EMPTY,
                                    EMPTY, PAWN, EMPTY, EMPTY}; // pg.16

    } else if (level == 5) { return {EMPTY, EMPTY, PAWN, EMPTY,
                                    KNIGHT, QUEEN, EMPTY, EMPTY,
                                    EMPTY, BISHOP, EMPTY, EMPTY,
                                    ROOK, EMPTY, EMPTY, EMPTY}; // pg.19

    } else if (level == 6) { return {KING, EMPTY, ROOK, EMPTY,
                                    EMPTY, EMPTY, BISHOP, EMPTY,
                                    EMPTY, EMPTY, KNIGHT, EMPTY,
                                    PAWN, EMPTY, EMPTY, EMPTY}; // pg.22

    } else if (level == 7) { return {ROOK, EMPTY, EMPTY, EMPTY,
                                    EMPTY, EMPTY, KING, PAWN,
                                    KNIGHT, BISHOP, EMPTY, EMPTY,
                                    EMPTY, EMPTY, EMPTY, EMPTY}; // pg.24

    } else if (level == 8) { return {ROOK, EMPTY, EMPTY, EMPTY,
                                    EMPTY, PAWN, KNIGHT, EMPTY,
                                    EMPTY, EMPTY, EMPTY, EMPTY,
                                    ROOK, EMPTY, KNIGHT, EMPTY}; // pg.25

    } else if (level == 9) { return {ROOK, KNIGHT, EMPTY, EMPTY,
                                    QUEEN, EMPTY, EMPTY, EMPTY,
                                    EMPTY, BISHOP, EMPTY, EMPTY,
                                    KNIGHT, EMPTY, PAWN, EMPTY}; // pg.33

    } else if (level == 10) { return {EMPTY, ROOK, EMPTY, ROOK,
                                      EMPTY, EMPTY, PAWN, EMPTY,
                                      EMPTY, PAWN, EMPTY, EMPTY,
                                      BISHOP, EMPTY, KNIGHT, EMPTY}; // pg.38

    } else if (level == 11) { return {EMPTY, EMPTY, BISHOP, ROOK,
                                      EMPTY, EMPTY, BISHOP, ROOK,
                                      EMPTY, EMPTY, EMPTY, PAWN,
                                      KNIGHT, EMPTY, EMPTY, EMPTY}; // pg.41

    } else if (level == 12) { return {EMPTY, ROOK, EMPTY, KNIGHT,
                                      KNIGHT, EMPTY, PAWN, EMPTY,
                                      EMPTY, BISHOP, EMPTY, EMPTY,
                                      EMPTY, EMPTY, PAWN, EMPTY}; // pg. 45

    } else if (level == 13) { return {EMPTY, EMPTY, BISHOP, KNIGHT,
                                      EMPTY, ROOK, BISHOP, PAWN,
                                      KNIGHT, EMPTY, EMPTY, EMPTY,
                                      EMPTY, PAWN, EMPTY, EMPTY}; // pg. 50

    } else if (level == 14) { return {EMPTY, EMPTY, EMPTY, PAWN,
                                      EMPTY, EMPTY, BISHOP, KNIGHT,
                                      BISHOP, QUEEN, EMPTY, EMPTY,
                                      EMPTY, KNIGHT, PAWN, EMPTY}; // pg. 54

    } else if (level == 15) { return {ROOK, EMPTY, EMPTY, PAWN,
                                      EMPTY, BISHOP, ROOK, EMPTY,
                                      BISHOP, EMPTY, EMPTY, KNIGHT,
                                      EMPTY, EMPTY, PAWN, EMPTY}; // pg. 59

    } else if (level == 16) { return {EMPTY, EMPTY, ROOK, KNIGHT,
                                      EMPTY, EMPTY, EMPTY, KNIGHT,
                                      BISHOP, EMPTY, ROOK, EMPTY,
                                      PAWN, EMPTY, EMPTY}; // pg. 62

    } else if (level == 17) { return {PAWN, BISHOP, EMPTY, EMPTY,
                                      KNIGHT, KNIGHT, EMPTY, EMPTY,
                                      QUEEN, EMPTY, BISHOP, PAWN,
                                      ROOK, EMPTY, EMPTY, EMPTY}; // pg. 66

    } else if (level == 18) { return {EMPTY, EMPTY, KNIGHT, PAWN,
                                      EMPTY, EMPTY, BISHOP, PAWN,
                                      ROOK, ROOK, EMPTY, EMPTY,
                                      BISHOP, KNIGHT, EMPTY, EMPTY}; // pg. 71

    } else if (level == 19) { return {ROOK, ROOK, EMPTY, EMPTY,
                                      KNIGHT, QUEEN, BISHOP, PAWN,
                                      BISHOP, EMPTY, EMPTY, EMPTY,
                                      EMPTY, EMPTY, PAWN, EMPTY}; // pg. 75

    } else if (level == 20) { return {EMPTY, EMPTY, ROOK, PAWN,
                                      EMPTY, ROOK, KNIGHT, EMPTY,
                                      BISHOP, KNIGHT, EMPTY, EMPTY,
                                      PAWN, BISHOP, EMPTY, EMPTY}; // pg. 79

    } else {
      std::cout << "error: no level of that number found; must be within range 0-20.\n";
      return {EMPTY, EMPTY, EMPTY, EMPTY,
              EMPTY, EMPTY, EMPTY, EMPTY,
              EMPTY, EMPTY, EMPTY, EMPTY,
              EMPTY, EMPTY, EMPTY, EMPTY};
    }
  }
}
