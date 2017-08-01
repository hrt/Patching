#include "Game.hpp"

Game::Game(board_t board)
{
  this->board = board;
  this->immovableCount = 0;
  for (int i = 0; i < (int) board.size(); i++)
  {
    if (isSpool(board[i]))
      this->spoolIndex = i;
    if (isTieOff(board[i]))
      this->tieOffIndex.push_back(i);
    if (!isMoveable(board[i]))
      immovableCount += 1;
  }
}

// updates and returns a random permutation of inital board
board_t Game::randomPermutation()
{
  int boardSize = (int) board.size();

  int immovableLeft = immovableCount;

  for (int i = 0; i < boardSize; i++)
  {
    piece_t piece = board[i];
    if (!(isMoveable(piece))) // skip immovable pieces
    {
      immovableLeft -= 1;
      continue;
    }

    int piecesLeft = boardSize - i;
    if (piecesLeft - 1 > immovableLeft) // there are moveables left
    {
      // find a random index that has not been "placed" yet
      int randomIndex = rand() % (piecesLeft);
      while (!(isMoveable(board[randomIndex])))
        randomIndex = rand() % (piecesLeft);

      // swap them
      board[i] = board[randomIndex];
      board[randomIndex] = piece;
    }

    // now randomise rotation
    int basePiece = (board[i] / 4) * 4;
    int randomRotation = 0;
    if (isStraight(board[i]))
    { // there are only two rotations for straight pieces
      randomRotation = rand() % 2;
    }
    else
    {
      randomRotation = rand() % 4;
    }
    board[i] = basePiece + randomRotation;
  }
  return board;
}

// checks if current permutation of board is valid and if yes returns score
int Game::isValid()
{
  for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; i++)  // set all starts positions to false
    seenPositions[i] = false;

  location_t location;
  location.isActive = true;
  location.position = spoolIndex;
  location.direction = board[spoolIndex];   // direction left === spool left..

  seenPositions[spoolIndex] = true; // marking start position

  std::vector<location_t> locations;
  locations.push_back(location);

  bool isValid = true;
  int score = 0;

  while (isValid && !isFinished(locations))
  {
    isValid &= advancePositions(locations);
    score += (int) locations.size();

    isValid &= isAccepting(locations);
    updateDirections(locations);
  }
  return isValid ? score : 0;
}

// advance all unfinished positions by one
bool Game::advancePositions(std::vector<location_t> &locations)
{
  for (int i = 0; i < (int) locations.size(); i++)
  {
    // if we're terminal (spool is not terminal) then don't advance
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

// check if currrent piece accepts current direction
bool Game::isAccepting(location_t& location)
{
  piece_t piece = board[location.position];
  // todo : not sure why this doesn't work yet.., fix it!
  if (isMoveable(piece) && !isGrommet(piece) && seenPositions[location.position]) // we have already seen this!
    location.isActive = false;

  if (!location.isActive)
    return true;

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
    return isAdvanceAccepting[pieceDirection][direction];
  }
  else if (isTieOff(piece))
  {
    int pieceDirection = piece - TIE_OFF_LEFT;
    return isAdvanceAccepting[pieceDirection][direction];
  }
  else if (isSpool(piece))
  {
    int pieceDirection = piece - SPOOL_LEFT;
    if (isAdvanceAccepting[pieceDirection][(direction + 2) % 4]) // checking against opposite direction
    {
      // if we just hit a spool then turn inactive (caused by patch loop)
      location.isActive = false;
      return true;
    }
    else
    {
      // we just left the spool
      return isAdvanceAccepting[pieceDirection][direction];
    }
  }
  return false;
}

bool Game::isAccepting(std::vector<location_t> &locations)
{
  bool allAccepting = true;
  for (int i = 0; i < (int) locations.size(); i++)
  {
    allAccepting &= isAccepting(locations[i]);
  }
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
      int pieceDirection = piece - TURN_LEFT_UP;
      locations[i].direction = turnToDirection[pieceDirection][previousDirection];
    }
    else if (isTurnStraight(piece))
    {
      // determine if it is a reoccuring loop
      if (seenPositions[locations[i].position])
      {
        // loop -> remove the current location from locations
        locations[i].isActive = false;
      }
      else
      {
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

// checks if the game is fully finished
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
