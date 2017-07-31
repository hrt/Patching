#ifndef LOCATION_HPP
#define LOCATION_HPP

struct location_t
{
  bool isActive;      // whether or not we should continue looking ahead
  int position;
  int direction;
};

#endif
