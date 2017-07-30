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

  std::vector<location_t> locations;
  locations.push_back(location);

  bool isValid = true;

  while (isValid && !isFinished(locations))
  {
    isValid &= advancePositions(locations);
    isValid &= isAccepting(locations);
    updateDirections(locations);
  }

  return isValid;
}

// move ahead one
bool Game::advancePositions(std::vector<location_t> &locations)
{
  for (int i = 0; i < (int) locations.size(); i++)
  {
    switch (locations[i].direction)
    {
      case DIRECTION_LEFT:
      if (locations[i].position % BOARD_WIDTH == 0)                   // left edge
        return false;
      locations[i].position -= 1;
      break;

      case DIRECTION_UP:
      if (locations[i].position < BOARD_WIDTH)                        // top edge
        return false;
      locations[i].position -= BOARD_WIDTH;
      break;

      case DIRECTION_RIGHT:
      if (locations[i].position % BOARD_WIDTH == BOARD_WIDTH - 1)     // right edge
        return false;
      locations[i].position += 1;
      break;

      case DIRECTION_DOWN:
      if (locations[i].position >= BOARD_WIDTH * (BOARD_HEIGHT - 1))  // bottom edge
        return false;
      locations[i].position += BOARD_WIDTH;
      break;

      default:
      return false;
    }
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
    int pieceDirection = piece - TURN_LEFT_UP;
    return isAcceptingLookup[pieceDirection][direction];
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

bool Game::isAccepting(std::vector<location_t> locations)
{
  bool allAccepting = true;
  for (int i = 0; i < (int) locations.size(); i++)
    allAccepting &= isAccepting(locations[i]);
  return allAccepting;
}


void Game::updateDirections(std::vector<location_t> &locations)
{
  for (int i = 0; i < (int) locations.size(); i++)
  {
    piece_t piece = board[locations[i].position];
    int previousDirection = locations[i].direction;

    // todo: should be location array instead of one
    if (isTurn(piece))
    {
      if (previousDirection % 2 == 0)  // left or right
      {
        if ((piece - TURN_LEFT_UP) % 2 == 0) // left up or right down
        {
          locations[i].direction = (previousDirection + 1) % 4;
        }
        else // left down or right up
        {
          locations[i].direction = ((previousDirection - 1) + 4) % 4;
        }
      }
      else  // up or down
      {
        if ((piece - TURN_LEFT_UP) % 2 == 0) // left up or right down
        {
          locations[i].direction = ((previousDirection - 1) + 4) % 4;
        }
        else // left down or right up
        {
          locations[i].direction = (previousDirection + 1) % 4;
        }
      }
    }
    else if (isTurnStraight(piece))
    {
      // todo : pushback a new location and update current!
    }
  }
}

bool Game::isFinished(std::vector<location_t> locations)
{
  // todo : multiple tie offs, a.k.a check that all tieoffs are met and location.position s are tie offs or grommet
  return true;
}
