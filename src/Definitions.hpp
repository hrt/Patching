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
#define SPOOL_LEFT 0              // 0-        // A
#define SPOOL_UP 1                             // B
#define SPOOL_RIGHT 2                          // C
#define SPOOL_DOWN 3                           // D

#define TIE_OFF_LEFT 4            // x-        // E
#define TIE_OFF_UP 5                           // F
#define TIE_OFF_RIGHT 6                        // G
#define TIE_OFF_DOWN 7                         // H

#define BLOCKER 8                              // I

#define STRAIGHT_HORIZONTAL 12    // _         // M
#define STRAIGHT_VERTICAL 13                   // N

#define TURN_LEFT_UP 14           // |_        // O
#define TURN_RIGHT_UP 15                       // P
#define TURN_RIGHT_DOWN 16                     // Q
#define TURN_LEFT_DOWN 17                      // R

#define TURN_STRAIGHT_LEFT 18     // |-        // S
#define TURN_STRAIGHT_UP 19                    // T
#define TURN_STRAIGHT_RIGHT 20                 // U
#define TURN_STRAIGHT_DOWN 21                  // V

#define GROMMET_LEFT 22           // o-        // W
#define GROMMET_UP 23                          // X
#define GROMMET_RIGHT 24                       // Y
#define GROMMET_DOWN 25                        // Z

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
