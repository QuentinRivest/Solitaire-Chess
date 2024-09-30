#include <iostream>

#include "include/chessboard.h"

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
                const std::vector<std::string>& image
                    = board_.at(i+k).getImage();
                std::cout << image.at(j);
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
std::array<Piece, 16> Chessboard::getBoard() const {
  return board_;
}

// updates the board by replacing the Piece obj at 'new_pos' with the Piece obj
// at 'old_pos';
// also changes Piece obj at 'old_pos' to an empty Piece
void Chessboard::updateBoard(const std::pair<int, int>& old_pos,
                             const std::pair<int, int>& new_pos) {
  // sets Piece obj at 'new_pos' equal to Piece obj at 'old_pos'
  board_.at(coordToIndex(new_pos)) = board_.at(coordToIndex(old_pos));
  // resets the moved Piece obj's stored position value
  board_.at(coordToIndex(new_pos)).setPosition(new_pos);
  // resets the moved Piece obj/s stored range vector value
  board_.at(coordToIndex(new_pos)).setRange();
  // sets Piece obj at 'old_pos' equal to an empty Piece obj
  Piece piece{0, old_pos};
  board_.at(coordToIndex(old_pos)) = piece;
}

// returns true if the spot on the board at the given coordinate coord has a
// chess piece on it, false if spot is empty or not on board
bool Chessboard::spotOccupied(const std::pair<int, int>& coord) const {
  if (!coordExists(coord)) {
    return false;
  }
  if (board_.at(coordToIndex(coord)).getPieceId() >= 1 &&
    board_.at(coordToIndex(coord)).getPieceId() <= 6) {
    return true;
  }
  return false;
}

// returns vector of int-int pairs representing the coordinates on the board to
// which a piece at the given coordinate coord can move
// the criteria for a piece to be able to move somewhere is if that where is an
// existent coordinate on the board, and that coordinate is occupied
std::vector<std::pair<int, int>> Chessboard::getMoves(
    const std::pair<int, int>& position) const {
  // if 'position' doesn't exist on the board, print "error..." and return {-1,-1}
  if (!coordExists(position)) {
    std::cout << "error: used non-existent coordinate to get moves.\n";
    return {{-1, -1}};
  }

  // construct new Piece obj 'piece' equal to Piece obj at coord of 'position';
  // this way 'piece' can be used each time rather than
  // 'board_.at(coordToIndex(position))'
  Piece piece = board_.at(coordToIndex(position));
  std::vector<std::pair<int, int>> moves{};

  // if 'piece' is a bishop or queen (i.e., if it moves diagonally)
  if ((piece.getPieceId() == 4) || (piece.getPieceId() == 5)) {
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
  if (piece.getPieceId() == 0) {
    std::cout << "error: tried to get moves of empty piece.\n";
    return {{0, 0}};
  } else if ((piece.getPieceId() == 1) || (piece.getPieceId() == 3) ||
             (piece.getPieceId() == 6)) {  // if 'piece' is pawn, knight, king
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
  } else if ((piece.getPieceId() == 2) || (piece.getPieceId() == 5)) {
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

// converts 1A-format coordinate to two-digit coordinate
std::pair<int, int> displayToCoord(const std::string& disp_coord) {
  // if the first char in the display coord is a digit in the range 1-4
  if (std::isdigit(disp_coord.at(0)) &&
      ((std::stoi(disp_coord.substr(0,1)) >= 1 ||
        std::stoi(disp_coord.substr(0, 1)) <= 4))) {

    int digit2{0};
    if ((disp_coord.at(1) >= 'a') && (disp_coord.at(1) <= 'd')) {
      // store the number in "digit2" that corresponds to letter (e.g., 'a' = 1)
      // if second char is in range a-d
      // (subtracting 96 from ASCII val of lowercase char gives corres. int)
      digit2 = disp_coord.at(1) - 96;
    } else if ((disp_coord.at(1) >= 'A') || (disp_coord.at(1) <= 'D')) {
      // store the number in "digit2" that corresponds to letter (e.g., 'A' = 1)
      // if second char is in range A-D
      // (subtracting 64 from ASCII val of uppercase char gives corres. int)
      digit2 = disp_coord.at(1) - 64;
    } else {
      // if second char is not in range a-d or A-D, then it's not valid
      return {-1, -1};
    }
    // return pair of first char as int and second char as corresponding int
    return {(std::stoi(disp_coord.substr(0, 1))), digit2};
  }
  // if first char is not a digit, or not in range 1-4, coordinate
  return {-1, -1};
}

// converts two-digit coordinate to 1A-format coordinate
std::string coordToDisplay(const std::pair<int, int>& coord) {
  if (!coordExists(coord)) {
    std::cout << "error: no known coordinate of that value.\n";
    return "ERROR";
  }

  char display_num;
  char display_char;
  for (int i = 1; i <= 4; i++) {
    if (coord.first == i) {
      // converts i to numeric char with ASCII value of i and stores val in
      // display_num
      // (adding 48 to an int converts it to its ASCII value (e.g., '1' = 49))
      display_num = i + 48;
    }
    if (coord.second == i) {
      // converts i to alphabetical char with ASCII value of i and stores val
      // in display_num
      // (adding 64 to an int converts it to the ASCII value of the
      // corresponding letter (e.g., 'A' = 65), (1 being converted to 'A'))
      display_char = i + 64;
    }
  }
  std::string display_coord{display_num};
  return display_coord.append(1, display_char);
}

// converts std::pair-style coordinate to index usable by .at() function so that
// a piece on the "board_" array of Pieces can be accessed by its position
int coordToIndex(const std::pair<int, int>& coord) {
  // if the coord does not exist: error
  if (!coordExists(coord)) {
    std::cout << "error: no known coordinate of that value.\n";
    return -1;
  }
  // returns an index int within the range 0-15,
  return (-4) * ((coord.first) - 4) + ((coord.second) - 1);
}

// converts index to two-digit coordinate
std::pair<int, int> indexToCoord(int index) {
  // error if index does not exist;
  // since the board has 16 elements, the index should be in the range 0-15
  if (index < 0 || index > 15) {
    std::cout << "error: no index of that value on board.\n";
  }
  // converts 0-3 to 4 ; 4-7 to 3 ; 8-11 to 2 ; and 12-15 to 1
  int y_pos{4 - (index / 4)};
  // converts 0,4,8,12 to 1 ; 1,5,9,13 to 2 ; 2,6,10,14 to 3 ; 3,7,11,15 to 4
  int x_pos{1 + (index % 4)};
  return std::pair<int, int> {y_pos, x_pos};
}

// takes an int representing the level the user is on in Solitaire Chess
// returns array of ints representing the list of piece IDs in left-to-right,
// top-to-bottom order (like you'd read a book in English)
// 0 = empty, 1 = pawn, 2 = rook, 3 = knight, 4 = bishop, 5 = queen, 6 = king
std::array<int, 16> getStartingBoard(int level) {
  if (level == 0) { return {0,0,2,0,5,1,0,0,3,0,0,0,0,0,0,0}; } // pg.9
  else if (level == 1) { return {0,0,0,0,0,2,0,3,4,3,0,0,0,0,0,0}; } // pg.7
  else if (level == 2) { return {2,0,5,0,0,1,0,0,0,0,0,0,3,0,0,0}; } // pg.11
  else if (level == 3) { return {0,3,0,0,0,5,0,2,1,0,0,0,0,0,0,0}; } // pg.13
  else if (level == 4) { return {0,0,5,0,0,0,2,0,3,0,0,0,0,1,0,0}; } // pg.16
  else if (level == 5) { return {0,0,1,0,3,5,0,0,0,4,0,0,2,0,0,0}; } // pg.19
  else if (level == 6) { return {6,0,2,0,0,0,4,0,0,0,3,0,1,0,0,0}; } // pg.22
  else if (level == 7) { return {2,0,0,0,0,0,6,1,3,4,0,0,0,0,0,0}; } // pg.24
  else if (level == 8) { return {2,0,0,0,0,1,3,0,0,0,0,0,2,0,3,0}; } // pg.25
  else if (level == 9) { return {2,3,0,0,5,0,0,0,0,4,0,0,3,0,1,0}; } // pg.33
  else if (level == 10) { return {0,2,0,2,0,0,1,0,0,1,0,0,4,0,3,0}; } // pg.38
  else if (level == 11) { return {0,0,4,2,0,0,4,2,0,0,0,1,3,0,0,0}; } // pg.41
  else if (level == 12) { return {0,2,0,3,3,0,1,0,0,4,0,0,0,0,1,0}; } // pg. 45
  else if (level == 13) { return {0,0,4,3,0,2,4,1,3,0,0,0,0,1,0,0}; } // pg. 50
  else if (level == 14) { return {0,0,0,1,0,0,4,3,4,5,0,0,0,3,1,0}; } // pg. 54
  else if (level == 15) { return {2,0,0,1,0,4,2,0,4,0,0,3,0,0,1,0}; } // pg. 59
  else if (level == 16) { return {0,0,2,3,0,0,0,3,4,0,2,0,1,1,0,0}; } // pg. 62
  else if (level == 17) { return {1,4,0,0,3,3,0,0,5,0,4,1,2,0,0,0}; } // pg. 66
  else if (level == 18) { return {0,0,3,1,0,0,4,1,2,2,0,0,4,3,0,0}; } // pg. 71
  else if (level == 19) { return {2,2,0,0,3,5,4,1,4,0,0,0,0,0,1,0}; } // pg. 75
  else if (level == 20) { return {0,0,2,1,0,2,3,0,4,3,0,0,1,4,0,0}; } // pg. 79
  else {
    std::cout << "error: no level of that number found.\n";
    return {6};
  }
}

// returns vector of Pieces based on return value of getStartingBoard(level)
std::array<Piece, 16> setUpBoard(int level) {
  // creates a list of all the piece IDs in left-right, top-bottom order, and in
  // the order they'll be in the beginning of the level number in the parameter
  std::array<int, 16> id_list(getStartingBoard(level));

  // creates an array of Piece objects and fills it with the correct pieces at
  // the correct places according to the id_list array
  std::array<Piece, 16> chess_board{};
  for (int i = 0; i < 16; i ++) {
    // creates a Piece with two parameters: piece ID in the id_list array at
    // index "counter", and a std::pair<int, int> converted from an int index
    Piece piece{id_list.at(i), indexToCoord(i)};
    // add Piece object that was just created to chess_board array
    chess_board.at(i) = piece;
  }

  return chess_board;
}
