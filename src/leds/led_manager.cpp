#include <macros.h>

void ledDisplayTask() {
  FastLED.show();
}

void setPartialPixel(uint16_t pos, CRGB& color, CRGB leds) {
  CRGB c1(color), c2(color);
  uint8_t frac = pos & 0xFF;
  uint8_t idx  = pos >> 8;

  c1.nscale8(255 - frac);
  c2.nscale8(frac);
  leds[idx]     = c1;
  leds[idx + 1] = c2;
}
