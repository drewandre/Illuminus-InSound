/*
  PALETTE v1.2: 8-channel LED controller for use with
                'Palette' NeoPixel controller and WS2812b leds
                Version 1.4 - Boston, MA - Spring 2018

  Designed by Drew André: www.drewandre.net, www.linkedin.com/in/drewandre, www.instagram.com/_drewandre
*/

#define PALETTE_VERSION 0x0000
#define PALETTE_VOLTAGE 5
#define PALETTE_AMPERAGE 2000

#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <Wire.h>
// #include <EEPROM.h>
#include <Audio.h>
#include <FastLED.h>

// ---------------------- Debug config ---------------------- //
#define DEBUG
#ifdef DEBUG
  #define SWSERIAL_BAUD 115200 // RN52 must be at either 115200 or 9600 (if 9600 GPIO7 should be pulled low)
  #define PRINT_RN52
  // #define PRINT_FFT
  // #define PLAY_TONE_SWEEP_ON_STARTUP
  // #define PRINT_MAPPED_FFT
  // #define PRINT_LED_FRAMERATE
  // #define PRINT_AUDIO_MEMORY
#endif

// ---------------------- WS2812b config ---------------------- //
#define STRIP_TYPE WS2812B
#define DATA_PIN 3
#define NUM_LEDS 144
#define COLOR_ORDER GRB
#define LED_COLOR_CORRECTION TypicalLEDStrip
const uint16_t NUM_LEDS_16 = NUM_LEDS * 255;
const uint16_t HALF_POS_16 = NUM_LEDS_16 * 0.5;
const uint16_t HALF_POS = NUM_LEDS * 0.5;
CRGB leds[NUM_LEDS];

// ---------------------- RN52 config ---------------------- //
#define RN52_GPI02 8 // RN52 GPIO2 event notifier pin (default HIGH, HIGH -> LOW for 100ms on connected device event)
#define RN52_ANALOG_OUTPUT
// #define CHECK_RN52_FACTORY_SETTINGS
#define HWSERIAL Serial1     // RX1 + TX1
#define HWSERIAL_BAUD 115200 // RN52 must be at either 115200 or 9600 (if 9600 GPIO7 should be pulled low)
#define RN52_CMD_PIN 2       // In order to enter command mode, GPIO9/RN52_CMD_PIN must be pulled LOW
String DEVICE_NAME = "PALETTE";
String buffer = "";
String param = "";

// ---------------------- SGTL5000 config -------------------------- //
#ifdef RN52_ANALOG_OUTPUT // analog audio input from SGTL5000
const int AUDIO_IN = AUDIO_INPUT_LINEIN;
AudioInputI2S        audioInput;
// AudioOutputI2S       audioOutput; // SGTL5000 headphones & line-out
// AudioConnection      patchCord1(audioInput, 0, audioOutput, 0);
// AudioConnection      patchCord2(audioInput, 1, audioOutput, 1);
#else // I2S audio input from RN52
AudioInputI2Sslave   audioInput;
#endif

AudioAnalyzeFFT1024  fft_l;
AudioConnection      patchCord3(audioInput, 0, fft_l, 0);

#ifdef PLAY_TONE_SWEEP_ON_STARTUP
AudioSynthToneSweep  tone_sweep;
AudioConnection      patchCord4(tone_sweep, 0, audioOutput, 0);
AudioConnection      patchCord5(tone_sweep, 0, audioOutput, 1);
#endif

AudioControlSGTL5000 SGTL5000;

const uint16_t NUM_BANDS = 32;
const uint16_t MAX_BIN = 511;
uint16_t fftBins[NUM_BANDS];
uint8_t levels_l[NUM_BANDS];
uint8_t levels_r[NUM_BANDS];
uint8_t mapped_left[NUM_BANDS];
uint8_t mapped_right[NUM_BANDS];

// ---------------------- color palette config ---------------------- //
// uint8_t maxChanges = 45; // speed for switching between palettes
// extern const TProgmemRGBGradientPalettePtr gGradientPalettes[];
// extern const uint8_t gGradientPaletteCount;
// // Current palette number from the 'playlist' of color palettes
// uint8_t gCurrentPaletteNumber;
// uint8_t palette;
// // EEMPROM saved variables
// unsigned int palette_address = 0;
// unsigned int effect_address  = 1;
// // changed from CRGB::Black
// CRGBPalette16 gCurrentPalette(gGradientPalettes[gGradientPaletteCount]);
// CRGBPalette16 gTargetPalette(gGradientPalettes[gGradientPaletteCount + 1]);

uint8_t hue = 0, saturation = 255, brightness = 255;
uint8_t ihue, fhue;
uint8_t spectrumWidth = 36;

// ---------------------- noise config ----------------------- //
uint32_t x, y, z, dist;
uint16_t scale = 12;
uint16_t speed = 2;
uint8_t xoffset, yoffset;
uint8_t olddata, data, newdata;
uint16_t data_twelve;

// ---------------------- effect config ----------------------- //
uint8_t effect;
const uint8_t num_modes = 5;

// ---------------------- strip config ---------------------- //
const uint8_t segment_length = NUM_LEDS / NUM_BANDS;
const uint8_t hue_length = floor(255 / NUM_BANDS - 1);
const float palette_index_increment = 248.0 / NUM_LEDS;
const uint16_t palette_index_increment_twelve = 4095 / NUM_LEDS;

void readRN52Event() {
  Serial.println("wow");
}

void setup() {
  INITIALIZE();
}

void loop() {
  EVERY_N_MILLISECONDS(50) {
    READ_FFT_LEFT(0.2);
  }
}
