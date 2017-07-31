#include "Game.hpp"
// #include <iostream>

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

// todo : doesn't take into account patching loops
  while (isValid && !isFinished(locations))
  {
    isValid &= advancePositions(locations);
    isValid &= isAccepting(locations);
    updateDirections(locations);
    // for (int i = 0; i < (int) locations.size(); i++)
    //   std::cout << i << " : " << locations[i].position << std::endl;
  }

  return isValid;
}

// move ahead one
bool Game::advancePositions(std::vector<location_t> &locations)
{
  for (int i = 0; i < (int) locations.size(); i++)
  {
    // if we're terminal then return true
    if (!(isMoveable(board[locations[i].position]) && !isGrommet(board[locations[i].position])) && !isSpool(board[locations[i].position]))
      continue;

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
    return isTurnAccepting[pieceDirection][direction];
  }
  else if (isTurnStraight(piece))
  {
    return (piece - TURN_STRAIGHT_LEFT + 2) % 4 != direction;
  }
  else if (isGrommet(piece))
  {
    int pieceDirection = piece - GROMMET_LEFT;
    return isTieOffAccepting[pieceDirection][direction];
  }
  else if (isTieOff(piece))
  {
    int pieceDirection = piece - TIE_OFF_LEFT;
    return isTieOffAccepting[pieceDirection][direction];
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
  int initialSize = (int) locations.size();
  for (int i = 0; i < initialSize; i++)
  {
    piece_t piece = board[locations[i].position];
    int previousDirection = locations[i].direction;

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
      // split into two directions..
      int pieceDirection = piece - TURN_STRAIGHT_LEFT;
      int direction1 =  turnStraightToDirection[pieceDirection][previousDirection][0];
      int direction2 =  turnStraightToDirection[pieceDirection][previousDirection][1];

      location_t location;
      location.position = locations[i].position;
      location.direction = direction2;

      locations[i].direction = direction1;

      locations.push_back(location);
    }
  }
}

bool Game::isFinished(std::vector<location_t> locations)
{
  // keep track of tie offs found
  std::vector<int> foundTieOffs;

  // check that all endings are actually endings
  // todo : this will fail in case of loops
  for (int i = 0; i < (int) locations.size(); i++)
  {
    piece_t piece = board[locations[i].position];
    if (isTieOff(piece))
    {
      foundTieOffs.push_back(locations[i].position);
      continue;
    }

    if (!(isGrommet(piece)))
      return false;
  }

  // check that all tie offs are met

  if (tieOffIndex.size() > foundTieOffs.size())
    return false;

  for (int i = 0; i < (int) tieOffIndex.size(); i++)
  {
    for (int j = 0; j < (int) foundTieOffs.size(); i++)
    {
      if (foundTieOffs[j] == tieOffIndex[i])
        break;
      return false;
    }
  }

  return true;
}
