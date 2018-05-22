#include <macros.h>

extern struct CRGB leds[NUM_LEDS];

void ledDisplayTask(void);
void setPartialPixel(uint16_t pos,
                     CRGB   & color);
