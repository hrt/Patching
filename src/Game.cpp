#include "Game.hpp"
#include <iostream>

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
  for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; i++)  // set all starts positions to false
    startPositions[i] = false;

  location_t location;
  location.isActive = true;
  location.position = spoolIndex;
  location.direction = board[spoolIndex];   // direction left === spool left..

  startPositions[spoolIndex] = true; // marking start position

  std::vector<location_t> locations;
  locations.push_back(location);

  bool isValid = true;

// todo : loop patches will iterate infinitly
  while (isValid && !isFinished(locations))
  {
    isValid &= advancePositions(locations);
    isValid &= isAccepting(locations);
    updateDirections(locations);
    for (int i = 0; i < (int) locations.size(); i++)
      if (locations[i].isActive)
        std::cout << i << " : " << locations[i].position << std::endl;
  }

  return isValid;
}

// move ahead one
bool Game::advancePositions(std::vector<location_t> &locations)
{
  for (int i = 0; i < (int) locations.size(); i++)
  {
    // if we're terminal (spool is not terminal) then return true
    if (!(isMoveable(board[locations[i].position]) && !isGrommet(board[locations[i].position])) && !isSpool(board[locations[i].position]))
      continue;

    if (!locations[i].isActive)
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
bool Game::isAccepting(location_t& location)
{
  if (!location.isActive)
    return true;

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
    int pieceDirection = piece - SPOOL_LEFT;
    if (isTieOffAccepting[pieceDirection][(direction + 2) % 4])
    {
      // if we just hit a spool then turn inactive (caused by patch loop)
      if (isSpool(board[location.position]))
        location.isActive = false;
      return true;
    }
    else
    {
      // we just left the spool
      return isTieOffAccepting[pieceDirection][direction];
    }
  }
  return false;
}

bool Game::isAccepting(std::vector<location_t> &locations)
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

    if (!locations[i].isActive)
      continue;

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
      // determine if it is a reoccuring loop
      if (startPositions[i])
      {
        // loop -> remove the current location from locations
        locations[i].isActive = false;
      }
      else
      {
        // split
        startPositions[i] = true; // marking start position

        int pieceDirection = piece - TURN_STRAIGHT_LEFT;
        int direction1 =  turnStraightToDirection[pieceDirection][previousDirection][0];
        int direction2 =  turnStraightToDirection[pieceDirection][previousDirection][1];

        location_t location;
        location.position = locations[i].position;
        location.direction = direction2;

        location.isActive = true;

        locations.push_back(location);

        locations[i].direction = direction1;

      }
    }
  }
}

bool Game::isFinished(std::vector<location_t> locations)
{
  // keep track of tie offs found
  std::vector<int> foundTieOffs;

  // check that all endings are actually endings
  for (int i = 0; i < (int) locations.size(); i++)
  {
    if (!locations[i].isActive)
      continue;

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
    bool foundMatch = false;
    for (int j = 0; j < (int) foundTieOffs.size(); i++)
    {
      if (foundTieOffs[j] == tieOffIndex[i])
      {
        foundMatch = true;
        break;
      }
    }
    if (!foundMatch)
      return false;
  }

  return true;
}
