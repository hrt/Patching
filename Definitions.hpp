#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

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

// Representation of the board
typedef int board_t[BOARD_WIDTH * BOARD_HEIGHT];

#endif
