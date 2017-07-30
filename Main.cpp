#include <iostream>
#include "Definitions.hpp"
#include "Parser.hpp"

int main()
{
  Parser parser;
  board_t board = parser.parseBoard();

  for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; i++)
    std::cout << (char) (board[i] + '0');
  std::cout << std::endl;
  return 0;
}
