#ifndef LED_MANAGER_H
#define LED_MANAGER_H

#include <macros.h>

extern CRGB leds[NUM_LEDS];

namespace LEDManager {
void initialize(void);
void show(void);
void setPartialPixel(uint16_t pos,
                     CRGB   & color);
}

#endif
