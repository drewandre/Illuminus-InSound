#ifndef SIXBAR_H
#define SIXBAR_H

#include <Arduino.h>
#include "./dmx_manager.h"

class Sixbar
{
public:
  Sixbar(uint16_t startingDMXAddress);

  ~Sixbar();

  void draw(const CRGB &rgb);

private:
  Sixbar() {}

  uint16_t startingDMXAddress = 1;
  uint16_t redChannel = startingDMXAddress;
  uint16_t greenChannel = startingDMXAddress + 1;
  uint16_t blueChannel = startingDMXAddress + 2;
  uint16_t whiteChannel = startingDMXAddress + 3;
  uint16_t amberChannel = startingDMXAddress + 4;
  uint16_t uvChannel = startingDMXAddress + 5;
};
#endif // ifndef SIXBAR_H
