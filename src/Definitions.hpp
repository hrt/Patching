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

#define TURN_LEFT_UP 12           // |_        // M
#define TURN_RIGHT_UP 13                       // N
#define TURN_RIGHT_DOWN 14                     // O
#define TURN_LEFT_DOWN 15                      // P

#define TURN_STRAIGHT_LEFT 16     // |-        // Q
#define TURN_STRAIGHT_UP 17                    // R
#define TURN_STRAIGHT_RIGHT 18                 // S
#define TURN_STRAIGHT_DOWN 19                  // T

#define GROMMET_LEFT 20           // o-        // U
#define GROMMET_UP 21                          // V
#define GROMMET_RIGHT 22                       // W
#define GROMMET_DOWN 23                        // X

#define STRAIGHT_HORIZONTAL 24    // _         // Y
#define STRAIGHT_VERTICAL 25                   // Z

// Generic piece functions
#define isSpool(x) (x >= SPOOL_LEFT && x <= SPOOL_DOWN)
#define isTieOff(x) (x >= TIE_OFF_LEFT && x <= TIE_OFF_DOWN)
#define isBlocker(x) (x == BLOCKER)
#define isStraight(x) (x == STRAIGHT_VERTICAL || x == STRAIGHT_HORIZONTAL)
#define isTurn(x) (x >= TURN_LEFT_UP && x <= TURN_LEFT_DOWN)
#define isTurnStraight(x) (x >= TURN_STRAIGHT_LEFT && x <= TURN_STRAIGHT_DOWN)
#define isGrommet(x) (x >= GROMMET_LEFT && x <= GROMMET_DOWN)
#define isMoveable(x) (x >= TURN_LEFT_UP)


// Representation of the board
typedef int piece_t;
typedef std::array<piece_t, BOARD_WIDTH * BOARD_HEIGHT> board_t;

#endif
