#include "./led_manager.h"

/*======================*/
/*  external variables  */
CRGB leds[NUM_LEDS];
CRGB tempLeds[NUM_LEDS];

/*======================*/

namespace LedManager {
void initialize() {
#if DEBUG == true
  static unsigned long startTime = millis();
  Serial <<
    "\n======================= INITIALIZING LEDS =======================\n";
#endif
#define WS2801 true
  // FastLED.addLeds<WS2801, 3, 30, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.addLeds<STRIP_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);

#if LED_COLOR_CORRECTION == true
  FastLED.setCorrection(LED_COLOR_CORRECTION);
#endif

#if LED_CONST_FRAMERATE == true
  // #if WS2801 == true
  //   FastLED.setMaxRefreshRate(10);
  // #else
    FastLED.setMaxRefreshRate(255);
  // #endif
  Serial.print("WS2812b framerate set to ");
  Serial.print(LED_FRAMERATE);
  Serial.println();
#endif
  FastLED.setBrightness(255);
  // #if WS2801 != true
  //   FastLED.setMaxPowerInVoltsAndMilliamps(PALETTE_VOLTAGE, PALETTE_AMPERAGE);
  // #endif

  // #if WS2801 == true
  //   fill_solid(leds, NUM_LEDS, CRGB::Red);
  // #else
    fill_solid(leds, NUM_LEDS, CRGB::Black);
  // #endif
  FastLED.show();
  delay(10);
  // while(1);

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
