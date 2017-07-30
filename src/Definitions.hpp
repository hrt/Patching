#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

#include <array>

// Board dimensions
#define BOARD_HEIGHT 6
#define BOARD_WIDTH 7


// Pieces in the game
#define SPOOL 0
#define TIE_OFF 1
#define BLOCKER 2
#define STRAIGHT 3
#define TURN 4
#define STRAIGHT_TURN 5
#define GROMMET 6

// Generic piece functions
#define isSpool(x) (x == SPOOL)
#define isTieOff(x) (x == TIE_OFF)
#define isBlocker(x) (x == BLOCKER)
#define isStraight(x) (x == STRAIGHT)
#define isTurn(x) (x == TURN)
#define isStraightTurn(x) (x == STRAIGHT_TURN)
#define isGrommet(x) (x == GROMMET)
#define isMoveable(x) (x >= STRAIGHT)


// Representation of the board
typedef std::array<int, BOARD_WIDTH * BOARD_HEIGHT> board_t;

#endif
