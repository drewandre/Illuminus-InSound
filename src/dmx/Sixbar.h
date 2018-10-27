#ifndef Sixbar_H
#define Sixbar_H

#include <Arduino.h>

#define DEBUG true

class Sixbar
{
public:
  Sixbar(int startingAddress);

  ~Sixbar();

  void draw();

private:
  Sixbar() {}

  int startingAddress = 1;
};
#endif // ifndef Sixbar_H
