#include "Game.hpp"

Game::Game(board_t board)
{
  this->board = board;
  for (int i = 0; i < (int) board.size(); i++)
  {
    if (isSpool(board[i]))
      this->spoolIndex = i;
    if (isTieOff(board[i]))
      this->tieOffIndex.push_back(i);
  }
}

bool Game::isValid()
{
  return false;
}
