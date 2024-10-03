// definitions of (non-)member
#include <iostream>

#include "piece.hpp"
#include "piece-type-enum.hpp"


/* MEMBER FUNCTIONS */

// constructor for a chess piece
Piece::Piece(PieceType::PieceType piece_type, const std::pair<int, int>& position)
  : piece_type_(piece_type), position_(position), name_(createName(piece_type)),
    range_(createRange(piece_type, position)), image_(createImage(piece_type)) {}

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

// sets range for a chess piece
void Piece::setRange() {
  range_ = createRange(piece_type_, position_);
}

// returns range of a chess piece
const std::vector<std::pair<int, int>>& Piece::getRange() const {
  return range_;
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
    if (piece_type == PieceType::PieceType::EMPTY)
    {
      return "Empty";
    }
    else if (piece_type == PieceType::PieceType::PAWN)
    {
      return "Pawn";
    }
    else if (piece_type == PieceType::PieceType::ROOK)
    {
      return "Rook";
    }
    else if (piece_type == PieceType::PieceType::KNIGHT)
    {
      return "Knight";
    }
    else if (piece_type == PieceType::PieceType::BISHOP)
    {
      return "Bishop";
    }
    else if (piece_type == PieceType::PieceType::QUEEN)
    {
      return "Queen";
    }
    else if (piece_type == PieceType::PieceType::KING)
    {
      return "King";
    }
    else
    {
      std::cout << "error: tried to create name for non-chess-piece\n";
      return "ERROR";
    }
  }

  // sets the range for a chess piece, depending on what type of piece it is and
  // where it is on the board
  std::vector<std::pair<int, int>> createRange(PieceType::PieceType piece_type,
                                              const std::pair<int, int>&
                                              position) {
    // if the piece is an empty space
    if (piece_type == PieceType::PieceType::EMPTY) {
      return {{0, 0}};
    } else if (piece_type == PieceType::PieceType::PAWN) {  // if the piece is a pawn
      // vector of pairs for range of pawn moves
      std::vector<std::pair<int, int>> pawn_range{};
      // if there's one move north of current position is in board range...
      if ((position.first + 1) <= 4) {
        // ...and if one move northeast of current position is in board range...
        if ((position.second + 1) <= 4) {
          // ...add that coordinate to pawn_range
          pawn_range.push_back({(position.first + 1), (position.second + 1)});
        }
        // ...and if one move northwest of current position is in board range...
        if ((position.second - 1) >= 1) {
          // ...add that coordinate to pawn_range
          pawn_range.push_back({(position.first + 1), (position.second - 1)});
        }
      } else {  // no moves in range for pawn (i.e., pawn is at top row of board)
        // fill pawn_range with one int-int pair of 0's
        pawn_range.push_back({0,0});
      }
      return pawn_range;
    } else if (piece_type == PieceType::PieceType::ROOK) {  // if the piece is a rook
      // vector of pairs for range of rook moves
      std::vector<std::pair<int, int>> rook_range{};
      for (int i = 1; (position.first + i) <= 4; i++) {
        // adds coordinates north of current position to rook_range vector until
        // y-pos goes over 4 (doesn't affect x-direction)
        rook_range.push_back({(position.first + i), position.second});
      }
      for (int i = 1; (position.first - i) >= 1; i++) {
        // adds coordinates south of current position to rook_range vector until
        // y-pos goes under 1 (doesn't affect x-direction)
        rook_range.push_back({(position.first - i), position.second});
      }
      for (int i = 1; (position.second + i) <= 4; i++) {
        // adds coordinates east of current position to rook_range vector until
        // x-pos goes over 4 (doesn't affect y-direction)
        rook_range.push_back({position.first, (position.second + i)});
      }
      for (int i = 1; (position.second - i) >= 1; i++) {
        // adds coordinates west of current position to rook_range vector until
        // x-pos goes under 1 (doesn't affect y-direction)
        rook_range.push_back({position.first, (position.second - i)});
      }
      return rook_range;
    } else if (piece_type == PieceType::PieceType::KNIGHT) {  // if the piece is a knight
      // vector of pairs for range of knight moves
      std::vector<std::pair<int, int>> knight_range{};
      // if the knight can move up 2...
      if ((position.first + 2) <= 4) {
        // ...and if the knight can move right 1...
        if ((position.second + 1) <= 4) {
          // ...then add this coordinate to range
          knight_range.push_back({(position.first + 2), (position.second + 1)});
        }
        // ...and if the knight can move left 1...
        if ((position.second - 1) >= 1) {
          // ...then add this coordinate to range
          knight_range.push_back({(position.first + 2), (position.second - 1)});
        }
      } else {  // if the knight can move down 2...
        // ...and if the knight can move right 1...
        if ((position.second + 1) <= 4) {
          // ...then add this coordinate to range
          knight_range.push_back({(position.first - 2), (position.second + 1)});
        }
        // ...and if the knight can move left 1...
        if ((position.second - 1) >= 1) {
          // ...then add this coordinate to range
          knight_range.push_back({(position.first - 2), (position.second - 1)});
        }
      }
      // if the knight can move right 2...
      if ((position.second + 2) <= 4) {
        // ...and if the knight can move up 1...
        if ((position.first + 1) <= 4) {
          // ...then add this coordinate to range
          knight_range.push_back({(position.first + 1), (position.second + 2)});
        }
        // ...and if the knight can move down 1...
        if ((position.second - 1) >= 1) {
          // ...then add this coordinate to range
          knight_range.push_back({(position.first - 1), (position.second + 2)});
        }
      } else {  // if the knight can move left 2...
        // ...and if the knight can move up 1...
        if ((position.first + 1) <= 4) {
          // ...then add this coordinate to range
          knight_range.push_back({(position.first + 1), (position.second - 2)});
        }
        // ...and if the knight can move down 1...
        if ((position.second - 1) >= 1) {
          // ...then add this coordinate to range
          knight_range.push_back({(position.first - 1), (position.second - 2)});
        }
      }
      return knight_range;
    } else if (piece_type == PieceType::PieceType::BISHOP) {  // if the piece is a bishop
      // vector of pairs for range of bishop moves
      std::vector<std::pair<int, int>> bishop_range{};
      // concerning coordinates in board range and north of current position...
      for (int i = 1; (position.first + i) <= 4; i++) {
        // if the position i moves northeast of current position is in range...
        if ((position.second + i) <= 4) {
          // ...add that coordinate to bishop_range
          bishop_range.push_back({(position.first + i), (position.second + i)});
        }
        // if the position i-moves northwest of current position is in range...
        if ((position.second - i) >= 1) {
          // ...add that coordinate to bishop_range
          bishop_range.push_back({(position.first + i), (position.second - i)});
        }
      }
      // concerning coordinates in board range and south of current position...
      for (int i = 1; (position.first - i) >= 1; i++) {
        // if the position i moves northeast of current position is in range...
        if ((position.second + i) <= 4) {
          // ...add that coordinate to bishop_range
          bishop_range.push_back({(position.first - i), (position.second + i)});
        }
        // if the position i-moves northwest of current position is in range...
        if ((position.second - i) >= 1) {
          // ...add that coordinate to bishop_range
          bishop_range.push_back({(position.first - i), (position.second - i)});
        }
      }
      return bishop_range;
    } else if (piece_type == PieceType::PieceType::QUEEN) {  // if the piece is a queen
      // vector of pairs for range of queen moves
      std::vector<std::pair<int, int>> queen_range{};
      // concerning coordinates in board range and north of current position...
      for (int i = 1; (position.first + i) <= 4; i++) {
        // adds coordinates north of current position to queen_range vector until
        // y-pos goes over 4 (doesn't affect x-direction)
        queen_range.push_back({(position.first + i), position.second});
        // if the position i moves northeast of current position is in range...
        if ((position.second + i) <= 4) {
          // ...add that coordinate to bishop_range
          queen_range.push_back({(position.first + i), (position.second + i)});
        }
        // if the position i-moves northwest of current position is in range...
        if ((position.second - i) >= 1) {
          // ...add that coordinate to bishop_range
          queen_range.push_back({(position.first + i), (position.second - i)});
        }
      }
      // concerning coordinates in board range and south of current position...
      for (int i = 1; (position.first - i) >= 1; i++) {
        // adds coordinates south of current position to queen_range vector until
        // y-pos goes under 1 (doesn't affect x-direction)
        queen_range.push_back({(position.first - i), position.second});
        // if the position i moves northeast of current position is in range...
        if ((position.second + i) <= 4) {
          // ...add that coordinate to bishop_range
          queen_range.push_back({(position.first - i), (position.second + i)});
        }
        // if the position i-moves northwest of current position is in range...
        if ((position.second - i) >= 1) {
          // ...add that coordinate to bishop_range
          queen_range.push_back({(position.first - i), (position.second - i)});
        }
      }
      for (int i = 1; (position.second + i) <= 4; i++) {
        // adds coordinates east of current position to queen_range vector until
        // x-pos goes over 4 (doesn't affect y-direction)
        queen_range.push_back({position.first, (position.second + i)});
      }
      for (int i = 1; (position.second - i) >= 1; i++) {
        // adds coordinates west of current position to queen_range vector until
        // x-pos goes under 1 (doesn't affect y-direction)
        queen_range.push_back({position.first, (position.second - i)});
      }
      return queen_range;
    } else if (piece_type == PieceType::PieceType::KING) {  // if the piece is a king
      // vector of pairs for range of king moves
      std::vector<std::pair<int, int>> king_range{};
      // if coordinate one move north of current position is in range...
      if ((position.first + 1) <= 4) {
        // ...add that coordinate to king_range
        king_range.push_back({(position.first + 1), position.second});
        // ...and if coordinate one move northeast of current position is too...
        if ((position.second + 1) <= 4) {
          // ...add that coordinate to king_range...
          king_range.push_back({(position.first + 1), (position.second + 1)});
          // ...as well as coordinate one move east
          king_range.push_back({position.first, (position.second + 1)});
        }
        // ...and if coordinate one move northwest of current position is too..
        if ((position.second - 1) >= 1) {
          // ...add that coordinate to king_range...
          king_range.push_back({(position.first + 1), (position.second - 1)});
          // ...as well as coordinate one move west
          king_range.push_back({position.first, (position.second - 1)});
        }
      } else {  // if the space north is out of range...
        // ...but the space one move east IS in range...
        if ((position.second + 1) <= 4) {
          // ...then add that coordinate to king_range
          king_range.push_back({position.first, (position.second + 1)});
        }
        // ...but the space one move west IS in range...
        if ((position.second - 1) >= 1) {
          // ...then add that coordinate to king_range
          king_range.push_back({position.first, (position.second + 1)});
        }
      }
      // if coordinate one move south of current position is in range...
      if ((position.first - 1) >= 1) {
        // ...add that coordinate to king_range
        king_range.push_back({(position.first - 1), position.second});
        // ...and if coordinate one move northeast of current position is too...
        if ((position.second + 1) <= 4) {
          // ...add that coordinate to king_range
          king_range.push_back({(position.first - 1), (position.second + 1)});
        }
        // ...and if coordinate one move northwest of current position is too..
        if ((position.second - 1) >= 1) {
          // ...add that coordinate to king_range
          king_range.push_back({(position.first - 1), (position.second - 1)});
        }
      }
      return king_range;
    } else {
      std::cout << "error: tried to create range of non-chess-piece.\n";
      return {{-1, -1}};
    }
  }

  // creates the image of a chess piece given the piece type
  std::array<std::string, 7> createImage(PieceType::PieceType piece_type) {
    if (piece_type == PieceType::PieceType::EMPTY) {
      return {"|               ",
              "|               ",
              "|               ",
              "|               ",
              "|               ",
              "|               ",
              "----------------"};
    } if (piece_type == PieceType::PieceType::PAWN) {
      return {"|               ",
              "|       _       ",
              "|      (_)      ",
              "|     _/_\\_     ",
              "|    (_____)    ",
              "|               ",
              "----------------"};
    } else if (piece_type == PieceType::PieceType::ROOK) {
      return {"|               ",
              "|     |UUU|     ",
              "|      |_|      ",
              "|     _)_(_     ",
              "|    (_____)    ",
              "|               ",
              "----------------"};
    } else if (piece_type == PieceType::PieceType::KNIGHT) {
      return {"|               ",
              "|    ____|\\     ",
              "|    L__  |7    ",
              "|      /  |7    ",
              "|     (___)     ",
              "|    (_____)    ",
              "----------------"};
    } else if (piece_type == PieceType::PieceType::BISHOP) {
      return {"|               ",
              "|       o       ",
              "|      (/)      ",
              "|      {_}      ",
              "|     _)_(_     ",
              "|    (_____)    ",
              "----------------"};
    } else if (piece_type == PieceType::PieceType::QUEEN) {
      return {"|       o       ",
              "|     \\^^^/     ",
              "|     <___>     ",
              "|      )_(      ",
              "|     (___)     ",
              "|    (_____)    ",
              "----------------"};
    } else if (piece_type == PieceType::PieceType::KING) {
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
