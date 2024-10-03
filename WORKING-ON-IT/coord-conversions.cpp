#include <iostream>
#include <string>
#include <utility>

#include "coord-conversions.hpp"

namespace Coords {
  // returns true if coord param. exists in the grid of coordinates on the board
  bool coordExists(std::pair<int, int> coord)
  {
    if ((coord.first > 4) || (coord.first < 1) || (coord.second > 4) ||
        (coord.second < 1))
    {
      return false;
    }
    return true;
  }

  // converts 1A-format coordinate to two-digit coordinate
  std::pair<int, int> displayToCoord(const std::string& disp_coord) {
    if (disp_coord.length() < 2) { return {-1, -1}; }

    // if the first char in the display coord is a digit in the range 1-4
    if (std::isdigit(disp_coord[0]) &&
        ((std::stoi(disp_coord.substr(0,1)) >= 1 ||
          std::stoi(disp_coord.substr(0, 1)) <= 4))) {

      int digit2{0};
      if ((disp_coord[1] >= 'a') && (disp_coord[1] <= 'd')) {
        // store the number in "digit2" that corresponds to letter (e.g., 'a' = 1)
        // if second char is in range a-d
        // (subtracting 96 from ASCII val of lowercase char gives corresponding int)
        digit2 = disp_coord[1] - 96;
      } else if ((disp_coord[1] >= 'A') || (disp_coord[1] <= 'D')) {
        // store the number in "digit2" that corresponds to letter (e.g., 'A' = 1)
        // if second char is in range A-D
        // (subtracting 64 from ASCII val of uppercase char gives corresponding int)
        digit2 = disp_coord[1] - 64;
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
      std::cout << "error: no known coordinate of that value. - "
                << coord.first << ", " << coord.second << '\n';
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
}
