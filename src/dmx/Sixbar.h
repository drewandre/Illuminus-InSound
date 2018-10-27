#ifndef SIXBAR_H
#define SIXBAR_H

#include <Arduino.h>
#include "./dmx_manager.h"

class Sixbar
{
public:
  uint16_t startingDMXAddress;
  uint16_t redChannel;
  uint16_t greenChannel;
  uint16_t blueChannel;
  uint16_t whiteChannel;
  uint16_t amberChannel;
  uint16_t uvChannel;

  Sixbar()
  {
    startingDMXAddress = 1;
    redChannel = startingDMXAddress;
    greenChannel = startingDMXAddress;
    blueChannel = startingDMXAddress + 2;
    whiteChannel = startingDMXAddress + 3;
    amberChannel = startingDMXAddress + 4;
    uvChannel = startingDMXAddress + 5;
  }

  Sixbar(uint16_t startingDMXAddress)
  {
    startingDMXAddress = startingDMXAddress;
    redChannel = startingDMXAddress;
    greenChannel = startingDMXAddress + 1;
    blueChannel = startingDMXAddress + 2;
    whiteChannel = startingDMXAddress + 3;
    amberChannel = startingDMXAddress + 4;
    uvChannel = startingDMXAddress + 5;
    Serial.print("Sixbar initialized with starting address of ");
    Serial.print(startingDMXAddress);
    Serial.println();
    Serial.print("\tredChannel\t");
    Serial.print(redChannel);
    Serial.println();
    Serial.print("\tgreenChannel\t");
    Serial.print(greenChannel);
    Serial.println();
    Serial.print("\tblueChannel\t");
    Serial.print(blueChannel);
    Serial.println();
    Serial.print("\twhiteChannel\t");
    Serial.print(whiteChannel);
    Serial.println();
    Serial.print("\tamberChannel\t");
    Serial.print(amberChannel);
    Serial.println();
    Serial.print("\tuvChannel\t");
    Serial.print(uvChannel);
    Serial.println();
  }

  ~Sixbar(){};

  void draw(const CRGB &rgb);
};
#endif // ifndef SIXBAR_H
