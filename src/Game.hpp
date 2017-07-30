#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include "Definitions.hpp"
#include "Location.hpp"

class Game
{
public:
  Game(board_t board);
  bool isValid();
private:
  board_t board;
  int spoolIndex;
  std::vector<int> tieOffIndex;
  bool advancePosition(location_t& location);
};

#endif
