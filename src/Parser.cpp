#include <iostream>
#include "Parser.hpp"

board_t Parser::parseBoard()
{
  board_t board;
  char c;
  for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; i++)
  {
    std::cin >> c;
    int p = c - 'A';
    if (p < 0 || p > GROMMET_DOWN)
      std::cout << "Parsing error : invalid piece(" << c << ')' << std::endl;
    board[i] = p;
  }

  return board;
}
