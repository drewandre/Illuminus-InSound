#include <Arduino.h>
#include <iostream>
#include <string>

// ------------------- Environment config ------------------- //
#define DEBUG
using namespace std;

// ---------------------- Debug config ---------------------- //
#ifdef DEBUG
  #define SWSERIAL_BAUD 115200 // RN52 must be at either 115200 or 9600 (if 9600 GPIO7 should be pulled low)
  // #define PRINT_MCU_PERFORMANCE
  #define PRINT_RN52
  // #define PRINT_FFT
  // #define PRINT_MAPPED_FFT
  // #define PLAY_TONE_SWEEP_ON_STARTUP
#endif

// -------------------- Palette config -------------------- //
#define PALETTE_VERSION 0x0001
#define PALETTE_VOLTAGE 5
#define PALETTE_AMPERAGE 2000

// ---------------------- BM64 config ---------------------- //
#define BM64SERIAL Serial4 // RX4 (31) + TX4 (32)
#define BM64_SERIAL_BAUD 115200

// ---------------------- RN52 config ---------------------- //
#define RN52_ANALOG_OUTPUT

#define RN52_GPI02_PIN 8     // RN52 GPIO2 event notifier pin (default HIGH, HIGH -> LOW for 100ms on connected device event)
// #define CHECK_RN52_FACTORY_SETTINGS
#define HWSERIAL Serial1     // RX1 + TX1
#define HWSERIAL_BAUD 115200 // RN52 must be at either 115200 or 9600 (if 9600 GPIO7 should be pulled low)
#define RN52_CMD_PIN 2       // In order to enter command mode, GPIO9/RN52_CMD_PIN must be pulled LOW
#define DEVICE_NAME "PALETTE"

// ---------------------- WS2812b config ---------------------- //
#define STRIP_TYPE WS2812B
#define DATA_PIN 3
#define NUM_LEDS 144
// #define NUM_LEDS_16 NUM_LEDS * 255;
#define CENTER_LED_POS NUM_LEDS * 0.5
// #define HALF_POS_16 NUM_LEDS_16 * 0.5;
#define COLOR_ORDER GRB
#define LED_COLOR_CORRECTION TypicalLEDStrip
#define FFT_FIXED_SEGMENT_LENGTH NUM_LEDS / NUM_BANDS;
// #define HUE_LENGTH floor(255 / NUM_BANDS - 1);
// #define PALETTE_INDEX_INCREMENT 248.0 / NUM_LEDS;
// #define PALETTE_INDEX_INCREMENT_twelve 4095 / NUM_LEDS;


// -------------- Animation Controller config --------------- //
#define NUM_MODES 5

// -------------- EEPROM config --------------- //
// #define PALETTE_ADDRESS 0
// #define EFFECT_ADDRESS 1

// -------------- FFT config --------------- //
#define NUM_BANDS 32
#define MAX_BIN 511

// ------------------ color palette config ------------------ //
#define COLOR_PALETTE_SPEED 45 // speed for switching between palettes
extern const TProgmemRGBGradientPalettePtr gGradientPalettes[];
extern const uint8_t gGradientPaletteCount;
// Current palette number from the 'playlist' of color palettes
extern uint8_t gCurrentPaletteNumber;
extern uint8_t palette;
// changed from CRGB::Black
CRGBPalette16 gCurrentPalette(gGradientPalettes[gGradientPaletteCount]);
CRGBPalette16 gTargetPalette(gGradientPalettes[gGradientPaletteCount + 1]);
