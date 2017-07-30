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
  location_t location;
  location.position = spoolIndex;
  location.direction = board[spoolIndex];   // direction left === spool left..
  bool isValid = true;

  if (isSpool(location.position))
  {
    isValid &= advancePosition(location);
  }

  return false;
}

// move ahead one and check if next position is accepting
bool Game::advancePosition(location_t& location)
{
  // advance..
  switch (location.direction)
  {
    case DIRECTION_LEFT:
    if (location.position % BOARD_WIDTH == 0)                   // left edge
      return false;
    location.position -= 1;
    break;

    case DIRECTION_UP:
    if (location.position < BOARD_WIDTH)                        // top edge
      return false;
    location.position -= BOARD_WIDTH;
    break;

    case DIRECTION_RIGHT:
    if (location.position % BOARD_WIDTH == BOARD_WIDTH - 1)     // right edge
      return false;
    location.position += 1;
    break;

    case DIRECTION_DOWN:
    if (location.position >= BOARD_WIDTH * (BOARD_HEIGHT - 1))  // bottom edge
      return false;
    location.position += BOARD_WIDTH;
    break;

    default:
    return false;
  }

  // check new position is accepting..
  piece_t nextPiece = board[location.position];

  if (isBlocker(nextPiece))
  {
    return false;
  }
  else if (isStraight(nextPiece))
  {
    return location.direction % 2 == nextPiece % 2;
  }
  else if (isTurn(nextPiece))
  {
    return nextPiece - TURN_LEFT_UP == location.direction
        || (nextPiece - TURN_LEFT_UP + 1) % 4 == location.direction;
  }
  else if (isTurnStraight(nextPiece))
  {
    return (nextPiece - TURN_STRAIGHT_LEFT + 2) % 4 != location.direction;
  }
  else if (isGrommet(nextPiece))
  {
    return nextPiece - GROMMET_LEFT == location.direction;
  }
  else if (isTieOff(nextPiece))
  {
    return nextPiece - TIE_OFF_LEFT == location.direction;
  }
  else if (isSpool(nextPiece))
  {
    return nextPiece - SPOOL_LEFT == location.direction;
  }

  return false;
}
