#include "./led_manager.h"

/*======================*/
/*  external variables  */
CRGB leds[NUM_LEDS];

/*======================*/

namespace LEDManager {
void initialize() {
#if DEBUG == true
  static unsigned long startTime = millis();
  Serial <<
    "\n======================= INITIALIZING LEDS =======================\n";
#endif
  FastLED.addLeds<STRIP_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);

#if LED_COLOR_CORRECTION == true
  FastLED.setCorrection(LED_COLOR_CORRECTION);

#endif

#if LED_CONST_FRAMERATE == true
  Serial << STRIP_TYPE << " framerate set to " << LED_FRAMERATE;
  FastLED.setMaxRefreshRate(LED_FRAMERATE);
#endif
  FastLED.setBrightness(255);
  FastLED.setMaxPowerInVoltsAndMilliamps(PALETTE_VOLTAGE, PALETTE_AMPERAGE);

  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
  delay(10);

#if DEBUG == true
  static unsigned long totalTime = millis() - startTime;
  Serial << "Leds Initialized:\t" << totalTime << "ms" << endl;
  Serial << "-----------------------------------------------------------------\n";
#endif
}

void show() {
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
}
