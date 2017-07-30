#include <iostream>
#include "Definitions.hpp"
#include "Parser.hpp"
#include "Game.hpp"

int main()
{
  Parser parser;
  board_t board = parser.parseBoard();

  Game game(board);

  if (game.isValid())
    std::cout << "Board is valid" << std::endl << std::endl;

  for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; i++)
    std::cout << (char) (board[i] + 'A');
  std::cout << std::endl;
  return 0;
}
