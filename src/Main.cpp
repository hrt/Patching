#include <iostream>
#include "Definitions.hpp"
#include "Parser.hpp"
#include "Game.hpp"
#include <time.h>
#include <pthread.h>
#include <mutex>

#define NUM_THREADS 1               // for some reason, same performance at different threads

board_t board;
int maxScore = 0;
std::mutex mutex;

void printBoard(board_t board)
{
  for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; i++)
    std::cout << (char) (board[i] + 'A');
  std::cout << std::endl;
}

void *randomForce(void *threadId)
{
  long seed = (long) threadId;
  srand(seed + time(NULL));

  Game game(board);
  int count = 0;
  while (true)
  {
    board_t board = game.randomPermutation();
    if (count % 100000 == 0)
    {
      printBoard(board);
    }

    int score = game.isValid();
    if (score > maxScore)
    {
      mutex.lock();
      maxScore = score;
      std::cout << score << std::endl;
      printBoard(board);
      mutex.unlock();
    }
    count++;
  }

  pthread_exit(NULL);
}

int main()
{
  Parser parser;

  board = parser.parseBoard();

  printBoard(board);

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
