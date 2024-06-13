// (non-) member functions of Piece class forward declared here
#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <utility>
#include <vector>

// a class with the properties of each chess piece
class Piece {
  public:
    Piece() = default;
    Piece(int piece_id, const std::pair<int, int>& position);

    int getPieceId() const;
    std::string getName() const;
    void setPosition(const std::pair<int, int>& position);
    std::pair<int, int> getPosition() const;
    void setRange();
    std::vector<std::pair<int, int>> getRange() const;
    std::vector<std::string> getImage() const;
    
  private: 
    // one-digit number to id chess piece
    int piece_id_;
    // current position of the piece
    std::pair<int, int> position_;
    // name of each chess piece
    std::string name_;
    // coordinates where each chess piece can move
    std::vector<std::pair<int, int>> range_;
    // ASCII art image of chess pieces that will show up on user's display
    std::vector<std::string> image_;
};

// returns name based on piece ID
std::string createName(int piece_id);

// returns true if coord param. exists in the grid of coordinates on the board
bool coordExists(std::pair<int, int> coord);

// takes piece ID and position of chess piece
// returns vector of int-int pairs for range of piece
std::vector<std::pair<int, int>> createRange(int piece_id,
                                             const std::pair<int, int>&
                                             position);

// takes piece ID
// returns vector of std::string's representing image of chess piece
std::vector<std::string> createImage(int piece_id);

#endif