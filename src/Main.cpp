#include <iostream>
#include "Definitions.hpp"
#include "Parser.hpp"
#include "Game.hpp"
#include <time.h>

int main()
{
  srand(time(NULL));

  Parser parser;
  board_t board = parser.parseBoard();

  Game game(board);

  int maxScore = -1;
  while (true)
  {
    board = game.randomPermutation();
    int score = game.isValid();
    if (score > maxScore)
    {
      maxScore = score;
      std::cout << score << std::endl;
      for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; i++)
        std::cout << (char) (board[i] + 'A');
      std::cout << std::endl;
    }
  }

  return 0;
}
