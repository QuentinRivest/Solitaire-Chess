#ifndef PIECE_TYPE_ENUM_H
#define PIECE_TYPE_ENUM_H


/* Chose namespace-enum combo rather than enum class because of the
 * "getStartingBoard(int level)" function in chessboard.cpp which creates the
 * levels using these enums, and using "PieceType::" for every piece looked
 * very cluttered.
 * I came up with two options: update my compiler to support C++ 20, or use
 * a regular enum and a namespace.
 * I chose the latter, since this is a small project with only one enum, so
 * the implicit conversion to a char won't cause problems since I'm just using
 * it to keep track of what different pieces are.
 */
namespace PieceType {
  enum PieceType : char
  {
    EMPTY,
    PAWN,
    ROOK,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING
  };
}

#endif
