#include <iostream>
#include <string>

#include "chessboard.hpp"
#include "coord-conversions.hpp"
#include "piece.hpp"
#include "piece-type-enum.hpp"

namespace {
  const std::string line{
  "-----------------------------------------------------------------------\n"
  };

  void enter_and_example() {
    std::string trash;
    std::cout << "Press [ENTER] to continue. ";
    std::getline(std::cin, trash);
    std::cout << line << "EXAMPLE BOARD:\n";
  }

  void enter_to_continue() {
    std::string trash;
    std::cout << "Press [ENTER] to continue. ";
    std::getline(std::cin, trash);
  }

  void tutorial() {
    Chessboard ex_board{0};
    ex_board.printBoard();
    std::cout << "\nAll chess pieces have the same movement rules as "
              << "traditional chess.\n\nHowever, with Solitaire Chess, one MUST"
              << " ATTACK with EACH MOVE.\n\nYour goal is to be left with "
              << "exactly one chess piece.\n\n";
    enter_and_example();

    ex_board.updateBoard({3, 1}, {2, 1});
    ex_board.printBoard();
    std::cout << "\n*queen attacks knight at 2A*\n\nIn this 4x4 board, up is "
              << "forward, so pawns can only move up.\n\n";
    enter_and_example();

    ex_board.updateBoard({3, 2}, {4, 3});
    ex_board.printBoard();
    std::cout << "\n*pawn attacks rook at 4C*\n\n";
    std::cout << "NOTE: Pawns will always move diagonally, since they'll "
              << "always be attacking.\n\n";
    enter_and_example();

    Chessboard ex2_board{0};
    ex2_board.printBoard();
    std::cout << "\nYou're free to move any piece in any legal way, as long as "
              << "it's an attack.\nMeaning you're also allowed to move the same"
              << " piece mulitiple times in a row.\n\n";
    enter_and_example();

    ex2_board.updateBoard({3, 1}, {2, 1});
    ex2_board.printBoard();
    std::cout << "\n*queen attacks knight at 2A*\n\n";
    enter_and_example();

    ex2_board.updateBoard({2, 1}, {3, 2});
    ex2_board.printBoard();
    enter_and_example();

    ex2_board.updateBoard({3, 2}, {4, 3});
    ex2_board.printBoard();
    std::cout << "\n"
              << line << "\t\t\t    END OF TUTORIAL\n"
              << line << "\n";
    enter_to_continue();
    std::cout << "\n\n";
  }
}

int main() {
  // explain rules to user
  std::cout << line << "\t\t\t    SOLITAIRE CHESS\n" << line;
  std::cout << "Solitaire Chess is a one-player game with chess pieces and "
            << "a 4x4 board.\n\n";
  enter_and_example();

  std::cout << "\nWould you like to skip the tutorial ('s') or view it ('v')?\n\n";

  std::string tutorial_choice;
  std::getline(std::cin, tutorial_choice);

  if ( !(tutorial_choice.empty() || tutorial_choice[0] != 's' || tutorial_choice[0] != 'S') ) {
    tutorial();
  }

  // GAMEPLAY BEGINS, going to title screen

  // setting default val. for level
  int level{ 1 };

  while (true) { // LOOP1: this loop containes whole operation of game
    // print main menu
    std::cout << line << "\t\t\t      LEVEL SELECT\n" << line;
    std::cout << "Easy:\n\t[ 1] [ 2] [ 3] [ 4] [ 5]\n\n"
              << "Intermediate:\n\t[ 6] [ 7] [ 8] [ 9] [10]\n\n"
              << "Advanced:\n\t[11] [12] [13] [14] [15]\n\n"
              << "Expert:\n\t[16] [17] [18] [19] [20]\n\n"
              << line << "\t\t\t\tQUIT ('q')\n" << line
              << "\nEnter the number of the level you'd like to enter,\nor "
              << "enter \"q\" to quit: ";
    std::string lvl_choice;
    std::getline(std::cin, lvl_choice);

    std::cout << "\n" << line << "\n";

    if (lvl_choice.empty()) {
      std::cout << "Please try again.\n\n";
      enter_to_continue();
      continue;
    } else if ((lvl_choice.at(0) == 'q') || (lvl_choice.at(0) == 'Q')) {
      break;
      // if the first char in lvl_choice is a digit between 1 and 9, inclusive
    } else if (std::isdigit(lvl_choice.at(0)) && (lvl_choice.at(0) > 48) &&
                (lvl_choice.at(0) < 58)) {
      level = std::stoi(lvl_choice.substr(0,1));
      // if lvl_choice is longer than 1 AND a digit AND either:
      //  (level is currently 1 AND the 2nd char in lvl_choice is between 0
      //  and 9, inclusive) OR
      //  (level is currently 2 AND the 2nd char in lvl_choice is 0)
      if ((lvl_choice.size() > 1) && std::isdigit(lvl_choice.at(1)) &&
          (((level == 1) && (lvl_choice.at(1) > 47) &&
            (lvl_choice.at(1) < 58)) ||
            ((level == 2) && (lvl_choice.at(1) == 48)))) {
        level = std::stoi(lvl_choice.substr(0,2));
      }
    } else {
      std::cout << "Please try again.\n\n";
      enter_to_continue();
      continue;
    }
    // creates Chessboard object with user's given level
    Chessboard board{ level };
    bool is_first_move{ true };

    while (true) { // LOOP 2: this loop contains each move (move loop)
      board.printBoard();
      // prompt user with options: go back, restart level, select coordinate
        // if is_first_move == true, don't include restart option,
        // else DO include restart option
      std::cout << "\nEnter the coordinate of the piece you'd like to move "
                << "(enter coordinate in \"1A\" format),";
      if (is_first_move) {
        std::cout << "\nor \"b\" to go back to main menu: ";
      } else {
        std::cout << "\n\"b\" to go back to main menu, or \"r\" to restart: ";
      }
      // gets the users response (as a std::string) to the above prompt
      // (using getline so that it doesn't break if they put a space)
      std::string user_choice;
      std::getline(std::cin, user_choice);

      // horizontal line for spacing out text
      std::cout << "\n" << line << "\n";
      // if the user doesn't choose to 'go back to main menu' or 'restart',
      // they'll select coordinate of the piece they wish to move;
      // it's this coordinate -- their piece's starting position -- that this
      // variable is meant to store
      std::pair<int, int> initial_spot{0, 0};
      // will store name of selected piece
      std::string piece_name;

      // if the user entered no characters at all, have them try again
      if (user_choice.empty()) {
        std::cout << "Please try again.\n\n";
        // halts progression of program till user presses 'enter'
        enter_to_continue();
        // goes back to beginning of this while loop
        continue;
      } else if (!(is_first_move) && ( (user_choice.at(0) == 'r') ||
                  (user_choice.at(0) == 'R') )) {
          // ^if this is not the first move in the level,
          // AND if the first character in the user's input is 'r' or 'R'...

        // makes a new Chessboard obj that is the same setup at the beginning of
        // 'level' (which's the level the user's currently on)...
        Chessboard new_board{ level };
        // and sets board equal to that board, resetting the board to how it was
        // in the beginning of the level
        board = new_board;
        // goes back to beginning of LOOP 2
        continue;
      } else if ((user_choice.at(0) == 'b') || (user_choice.at(0) == 'B')) {
          // ^if first character of user's input is 'b' or 'B'...
        // breaks this while loop (LOOP 2), going back to LOOP 1 (i.e., going
        // back to main menu)
        break;
      } else if (user_choice.size() > 1) {
          // ^if there's more than one character in the user's input
          // (which there must be if the user's trying to enter a coordinate,
          // since a coordinate (e.g., '2C') is two characters long)
        // takes the first two characters of user's input and treats it as a
        // coordinate in int-char format and translates it to int-int pair
        // format (if these characters don't translate to any existing
        // coordinate, it'll return '{-1, -1}')
        initial_spot = Coords::displayToCoord(user_choice.substr(0,2));
        // if the coordinate the user entered does exist,
        // AND if that coordinate is occupied by a non-empty Piece obj...
        std::cout << "CHECK 1: " << initial_spot.first << ", " << initial_spot.second << " - "
                  << std::boolalpha << board.spotOccupied(initial_spot) << '\n';
        if ((initial_spot.first > 0) && board.spotOccupied(initial_spot)) {
          // set 'piece_name' equal to the name of the piece that is at the
          // selected coordinate on the board
          piece_name = board[initial_spot].getName();
          // if selected piece has no moves...
          if (board.getMoves(initial_spot).empty()) {
            // explain that this piece has no moves and ask them to try again
            std::cout << "Sorry, it seems the piece you selected has no moves "
                      << "in which it attacks another piece.\n"
                      << "It is required that all moves be an attack.\n"
                      << "Please try again with a different piece.\n\n";
            // haults progression of program till user presses 'enter'
            enter_to_continue();
            // goes back to beginning of LOOP 2
            continue;
          }
          // confirms to user their piece selection and its location
          std::cout << "You selected the " << piece_name << " at "
                    << Coords::coordToDisplay(initial_spot) << ".\n\n";
          // haults progression of program till user presses 'enter'
          enter_to_continue();
        } else {
            // ^if, either, the coordinate DOESN'T exist,
            // OR if that coordinate is unoccupied...

          // asks the user to try again
          std::cout << "Please try again with an occupied spot on the board."
                    << "\n\n";
          // haults progression of program till user presses 'enter'
          enter_to_continue();
          // goes back to beginning of LOOP 2
          continue;
        }
      } else {
          // ^if none of the above are true --
          // if the first character of the user's input is NOT epmty, isn't an
          // upper-/lower-case 'r' or 'b', and isn't more than 1 character
          // long...

        // asks the user to try again
        std::cout << "Please try again.\n\n";
        // haults progression of program till user presses 'enter'
        enter_to_continue();
        // goes back to beginning of LOOP 2
        continue;
      }

      // if this's the first move at this point in the level, then set
      // 'is_first_move' to false for the next time around in the loop
      if (is_first_move) { is_first_move = false; }

      // prints out line to space out text
      std::cout << "\n" << line << "\n";

      // true if level is beaten, remains false otherwise
      bool level_beaten{false};
      while (true) { // LOOP 3: loops until user chooses valid move
        // gives user the options of where to move
        board.printBoard();

        // tells user that the following list is going to the be their options
        // for where to move their piece
        std::cout << "\nMove options for your " << piece_name << ":\n\n";

        // stores the possible moves the Piece obj at 'initial_spot' can make
        // in the vector of int-int pairs 'moves'
        const std::vector<std::pair<int, int>> moves{
            board.getMoves(initial_spot)};

        // lists out numbers 1-n, n being the amount of moves the piece can make
        // (this's so that the user can enter the number under which the
        // coordinate they want their piece ot move to is, rather than them
        // entering the two-char-long string representing the coordinate, to
        // make the user input more simple)
        for (int i = 1; i <= moves.size(); i++) {
          std::cout << "[" << i << "] ";
        }
        std::cout << "\n";
        // lists each coordinate in 'moves' vector underneath the listed numbers
        for (const std::pair<int, int>& coord : moves) {
          std::cout << " " << Coords::coordToDisplay(coord) << " ";
        }
        std::cout << "\n\nPlease enter the digit above the coordinate you'd "
                  << "like to move your piece to: ";
        // stores the user's input as a std::string 'mv_choice'
        std::string mv_choice;
        std::getline(std::cin, mv_choice);

        // horizontal line to space out text
        std::cout << "\n" << line << "\n";

        // if user input no characters...
        if (mv_choice.empty()) {
          // have them try again
          std::cout << "Please try again.\n\n";
          // haults progression till user presses 'enter'
          enter_to_continue();
          // goes back to beginning LOOP 3
          continue;
        }
        // changes val of 'mv_choice' to only its first character
        mv_choice = mv_choice.substr(0,1);
        // if 'mv_choice' is a digit,
        // AND if that digit is between 1 and the size of the 'moves' vector
        // (inclusive of bounds)
        if (std::isdigit(mv_choice.at(0)) && (std::stoi(mv_choice) > 0) &&
            (std::stoi(mv_choice) <= moves.size())) {
          // an int-int pair that is the coordinate that the user selected to
          // be their selected piece's new spot to move to
          std::pair<int, int> new_spot{ moves.at(std::stoi(mv_choice) - 1) };
          // updates the Chessboard obj 'board' so that the piece currently at
          // 'initial_spot' is moved to 'new_spot',
          // 'initial_spot' then being filled with an empty Piece obj;
          // this is basically a piece taking another piece
          board.updateBoard(initial_spot, new_spot);

          // counts how many pieces are on the board
          int counter{0};
          for (const Piece& piece : board.getBoard()) {
            if (piece.getPieceType() != 0) {
              counter++;
            }
          }

          // if there's only one piece left on the board...
          if (counter == 1) {
            // display board one last time
            board.printBoard();
            std::cout << "\nCongratulations! You beat this level!\n\n";
            // haults progression till user presses 'enter'
            enter_to_continue();
            // set level_beat to 'true'
            level_beaten = true;
            // break loop
            break;
          }

          // confirms to user their decision to move their selected piece to
          // their selected new position
          std::cout << "You decided to move your " << piece_name << " to "
                    << Coords::coordToDisplay(new_spot) << ".\n\n";
          // haults progression till user presses 'enter'
          enter_to_continue();
          //
          break;
        } else {
            // ^if 'mv_choice' is NOT a digit that is within the range 1-n
            // inclusive (n being the number of elements in 'moves' vector)...
          // asks user to try again
          std::cout << "Please try again.\n\n";
          // haults progression till user presses 'enter'
          enter_to_continue();
        }
        // if break statement is not reached, LOOP 3 loops till user enters
        // enters valid move
      }
      // if level is beaten...
      if (level_beaten) {
        // go back to main menu
        break;
      }
    }
  }

  return 0;
}
