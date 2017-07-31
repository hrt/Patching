#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include "Definitions.hpp"
#include "Location.hpp"

class Game
{
public:
  Game(board_t board);
  board_t randomPermutation();
  int isValid();
private:
  bool isTurnAccepting[4][4] =   {{true, false, false, true},
                                  {false, false, true, true},
                                  {false, true, true, false},
                                  {true, true, false, false}};
  bool isTieOffAccepting[4][4] = {{true, false, false ,false},
                                  {false, false, false, true},
                                  {false, false, true, false},
                                  {false, true, false, false}};
  int turnStraightToDirection[4][4][2] = {{{DIRECTION_UP, DIRECTION_DOWN}, {DIRECTION_UP, DIRECTION_RIGHT}, {0, 0}, {DIRECTION_DOWN, DIRECTION_RIGHT}},
                                          {{DIRECTION_LEFT, DIRECTION_DOWN}, {DIRECTION_LEFT, DIRECTION_RIGHT}, {DIRECTION_DOWN, DIRECTION_RIGHT}, {0, 0}},
                                          {{0, 0}, {DIRECTION_LEFT, DIRECTION_UP}, {DIRECTION_UP, DIRECTION_DOWN}, {DIRECTION_LEFT, DIRECTION_DOWN}},
                                          {{DIRECTION_LEFT, DIRECTION_UP}, {0, 0}, {DIRECTION_UP, DIRECTION_RIGHT}, {DIRECTION_LEFT, DIRECTION_RIGHT}}};
  board_t board;
  std::array<bool, BOARD_WIDTH * BOARD_HEIGHT> seenPositions;
  int spoolIndex;
  std::vector<int> tieOffIndex;
  int immovableCount;
  bool advancePositions(std::vector<location_t> &locations);
  bool isAccepting(std::vector<location_t> &locations);
  bool isAccepting(location_t &location);
  void updateDirections(std::vector<location_t> &locations);
  bool isFinished(std::vector<location_t> locations);
};

#endif
