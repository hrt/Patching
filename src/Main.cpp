#include <iostream>
#include "Definitions.hpp"
#include "Parser.hpp"
#include "Game.hpp"
#include <time.h>
#include <pthread.h>
#include <mutex>

#define NUM_THREADS 8

board_t board;
int maxScore = -1;
std::mutex mutex;

void *randomForce(void *threadId)
{
  long seed = (long) threadId;
  srand(seed + time(NULL));

  Game game(board);

  while (true)
  {
    board_t board = game.randomPermutation();
    int score = game.isValid();
    if (score > maxScore)
    {
      mutex.lock();
      maxScore = score;
      std::cout << score << std::endl;
      for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; i++)
        std::cout << (char) (board[i] + 'A');
      std::cout << std::endl;
      mutex.unlock();
    }
  }

  pthread_exit(NULL);
}

int main()
{
  Parser parser;

  board = parser.parseBoard();

  std::cout << ((char) (board[0] + 'A')) << std::endl;

  pthread_t threads[NUM_THREADS];
  for (int i = 0; i < NUM_THREADS; i++)
  {
    std::cout << "main() : creating thread, " << i << std::endl;
    if (pthread_create(&threads[i], NULL, randomForce, (void *) i))
      std::cout << "Error:unable to create thread" << std::endl;
  }
  pthread_exit(NULL);

  return 0;
}
