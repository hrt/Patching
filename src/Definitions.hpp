#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

#include <array>

// Board dimensions
#define BOARD_HEIGHT 6
#define BOARD_WIDTH 7


// Directions you can face
#define DIRECTION_LEFT 0
#define DIRECTION_UP 1
#define DIRECTION_RIGHT 2
#define DIRECTION_DOWN 3


// Pieces in the game
#define SPOOL_LEFT 0              // 0-
#define SPOOL_UP 1
#define SPOOL_RIGHT 2
#define SPOOL_DOWN 3

#define TIE_OFF_LEFT 4            // x-
#define TIE_OFF_UP 5
#define TIE_OFF_RIGHT 6
#define TIE_OFF_DOWN 7

#define BLOCKER 8

#define STRAIGHT_HORIZONTAL 12    // _
#define STRAIGHT_VERTICAL 13

#define TURN_LEFT_UP 14           // |_
#define TURN_RIGHT_UP 15
#define TURN_RIGHT_DOWN 16
#define TURN_LEFT_DOWN 17

#define TURN_STRAIGHT_LEFT 18     // |-
#define TURN_STRAIGHT_UP 19
#define TURN_STRAIGHT_RIGHT 20
#define TURN_STRAIGHT_DOWN 21

#define GROMMET_LEFT 22           // o-
#define GROMMET_UP 23
#define GROMMET_RIGHT 24
#define GROMMET_DOWN 25

// Generic piece functions
#define isSpool(x) (x >= SPOOL_LEFT && x <= SPOOL_DOWN)
#define isTieOff(x) (x >= TIE_OFF_LEFT && x <= TIE_OFF_DOWN)
#define isBlocker(x) (x == BLOCKER)
#define isStraight(x) (x == STRAIGHT_VERTICAL || x == STRAIGHT_HORIZONTAL)
#define isTurn(x) (x >= TURN_LEFT_UP && x <= TURN_LEFT_DOWN)
#define isTurnStraight(x) (x >= TURN_STRAIGHT_LEFT && x <= TURN_STRAIGHT_DOWN)
#define isGrommet(x) (x >= GROMMET_LEFT && x <= GROMMET_DOWN)
#define isMoveable(x) (x >= STRAIGHT_HORIZONTAL)


// Representation of the board
typedef int piece_t;
typedef std::array<piece_t, BOARD_WIDTH * BOARD_HEIGHT> board_t;

#endif
