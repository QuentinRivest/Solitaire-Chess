#include <string>
#include <utility>

namespace Coords {
  // returns true if coord param. exists in the grid of coordinates on the board
  bool coordExists(std::pair<int, int> coord);

  // converts 1A-format coordinate to two-digit coordinate
  std::pair<int, int> displayToCoord(const std::string& num_char);

  // converts two-digit coordinate to 1A-format coordinate
  std::string coordToDisplay(const std::pair<int, int> &coord);

  // converts index to two-digit coordinate
  std::pair<int, int> indexToCoord(int index);
}
