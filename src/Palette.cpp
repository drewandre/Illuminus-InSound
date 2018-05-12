/*
  PALETTE v1.2: 8-channel LED controller for use with
                'Palette' NeoPixel controller and WS2812b leds
                Version 1.4 - Boston, MA - Spring 2018

  Designed by Drew André: www.drew-andre.com, www.linkedin.com/in/drewandre, www.instagram.com/_drewandre
*/

#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include <env_config.h>

#include <Wire.h>
#include <Audio.h>
#include <FastLED.h>

#include <initialize.h>
#include <performance_monitoring.h>
#include <bluetooth_manager.h>

// ---------------------- WS2812b config ---------------------- //
CRGB leds[NUM_LEDS];


// ---------------------- FFT config -------------------------- //
uint16_t fftBins[NUM_BANDS];
uint8_t levelsL[NUM_BANDS];
uint8_t levelsR[NUM_BANDS];
uint8_t scaledLevelsL[NUM_BANDS];
uint8_t scaledLevelsR[NUM_BANDS];

// ---------------------- color palette config ---------------------- //
// extern const TProgmemRGBGradientPalettePtr gGradientPalettes[];
// extern const uint8_t gGradientPaletteCount;
// // Current palette number from the 'playlist' of color palettes
// uint8_t gCurrentPaletteNumber;
// uint8_t palette;
// CRGBPalette16 gCurrentPalette(gGradientPalettes[gGradientPaletteCount]);
// CRGBPalette16 gTargetPalette(gGradientPalettes[gGradientPaletteCount + 1]);

uint8_t hue = 0, saturation = 255, brightness = 255;
uint8_t iHue, fHue;
uint8_t spectrumWidth = 36;

// ---------------------- Animation config ----------------------- //
bool calculateScaledFFT = false;

// ---------------------- RN52 config ----------------------- //
String buffer = ""
String param = ""

void setup() {
  initialize();
}

void loop() {
#ifdef PRINT_MCU_PERFORMANCE
  printMCUPerformance();
#endif

  // mapFFTLeft();
  readBM64();
}

void readBM64() {
  // buffer="";
  // static buffer = [];
  static bool wait_for_BM64 = true;
  unsigned long startTime;
  unsigned long end_time;

  while (BM64SERIAL.available()==0);
  // buffer.concat(BM64SERIAL.read());
  Serial.print("BM64>\t");
  Serial.print(BM64SERIAL.read());
  while(wait_for_BM64) {
    // if (BM64SERIAL.available()) buffer.concat(BM64SERIAL.read());
    if (BM64SERIAL.available()) Serial.print(BM64SERIAL.read());
    startTime = millis();
    end_time = startTime;
    while((end_time - startTime) <= 20) {
      if (BM64SERIAL.available() > 0) {
        wait_for_BM64 = true;
        break;
      }
      end_time = millis();
      wait_for_BM64 = false;
    }
  }
  wait_for_BM64 = true;
  // Serial.print("BM64> "); Serial.print(buffer, HEX);
  Serial.println();
}
