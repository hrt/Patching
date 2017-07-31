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
  // give it the piece you're looking at and the direction you're at and it tells you if it is accepting/supported
  bool isTurnAccepting[4][4] =    {{true, false, false, true},
                                   {false, false, true, true},
                                   {false, true, true, false},
                                   {true, true, false, false}};
  bool isAdvanceAccepting[4][4] = {{true, false, false ,false},
                                   {false, false, false, true},
                                   {false, false, true, false},
                                   {false, true, false, false}};
  // given the "turn + straight" piece you're looking at AND curent direction it returns (index 0 and 1) array of directions you split into
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
