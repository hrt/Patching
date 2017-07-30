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
    isValid &= isAccepting(location);
    updateDirection(location);
  }

  return false;
}

// move ahead one
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
  return true;
}

// check if piece is accepting direction
bool Game::isAccepting(location_t location)
{
  piece_t piece = board[location.position];
  int direction = location.direction;

  if (isBlocker(piece))
  {
    return false;
  }
  else if (isStraight(piece))
  {
    return direction % 2 == piece % 2;
  }
  else if (isTurn(piece))
  {
    return piece - TURN_LEFT_UP == direction
        || (piece - TURN_LEFT_UP + 1) % 4 == direction;
  }
  else if (isTurnStraight(piece))
  {
    return (piece - TURN_STRAIGHT_LEFT + 2) % 4 != direction;
  }
  else if (isGrommet(piece))
  {
    return piece - GROMMET_LEFT == direction;
  }
  else if (isTieOff(piece))
  {
    return piece - TIE_OFF_LEFT == direction;
  }
  else if (isSpool(piece))
  {
    return piece - SPOOL_LEFT == direction;
  }
  return false;
}

void Game::updateDirection(location_t& location)
{
  piece_t piece = board[location.position];
  int previousDirection = location.direction;

  // todo: should be location array instead of one
  if (isTurn(piece))
  {
    if (previousDirection % 2 == 0)  // left or right
    {
      if ((piece - TURN_LEFT_UP) % 2 == 0) // left up or right down
      {
        location.direction = (previousDirection + 1) % 4;
      }
      else // left down or right up
      {
        location.direction = ((previousDirection - 1) + 4) % 4;
      }
    }
    else  // up or down
    {
      if ((piece - TURN_LEFT_UP) % 2 == 0) // left up or right down
      {
        location.direction = ((previousDirection - 1) + 4) % 4;
      }
      else // left down or right up
      {
        location.direction = (previousDirection + 1) % 4;
      }
    }
  }
  else if (isTurnStraight(piece))
  {
    // todo : requires earlier todo
  }
}
