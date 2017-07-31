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
  bool isTurnAccepting[4][4] =   {{true, false, false, true},
                                  {false, false, true, true},
                                  {false, true, true, false},
                                  {true, true, false, false}};
  bool isTieOffAccepting[4][4] = {{true, false, false ,false},
                                  {false, false, false, true},
                                  {false, false, true, false},
                                  {false, true, false, false}};
  board_t board;
  int spoolIndex;
  std::vector<int> tieOffIndex;
  bool advancePositions(std::vector<location_t> &locations);
  bool isAccepting(std::vector<location_t> locations);
  bool isAccepting(location_t location);
  void updateDirections(std::vector<location_t> &locations);
  bool isFinished(std::vector<location_t> locations);
};

#endif
