#ifndef LED_MANAGER_H
#define LED_MANAGER_H

#include "../macros.h"

extern CRGB leds[NUM_LEDS];
extern CRGB tempLeds[NUM_LEDS];

namespace LedManager {
void initialize(void);
void show(void);
void setPartialPixel(uint16_t pos,
                     CRGB   & color);
}

#endif
