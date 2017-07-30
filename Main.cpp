#include <iostream>
#include "Definitions.hpp"

int main()
{
  board_t board;
  char c;
  for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; i++)
  {
    std::cin >> c;
    int p = c - '0';
    if (p < 0 || p > GROMMET)
      std::cout << "Parsing error : invalid piece(" << c << ')' << std::endl;
    board[i] = p;
  }

  for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; i++)
    std::cout << (char) (board[i] + '0');
  std::cout << std::endl;
  return 0;
}
