#include <Arduino.h>
#include <FastLED.h>
#include <Audio.h>

#include "./helpers/Streaming.h"

// ------------------- Environment config ------------------- //
#define DEBUG

// ---------------------- Debug config ---------------------- //
#ifdef DEBUG

  # define PRINT_MCU_PERFORMANCE false
  # define SWSERIAL_BAUD 115200
  # define PRINT_RN52 true
  # define DEMO_CYCLE false
  # define FIXED_ANIMATION_INDEX 0
  # define PRINT_FFT false
  # define PRINT_MAPPED_FFT false

#endif // ifdef DEBUG

// -------------------- Palette config -------------------- //
#define PALETTE_VERSION 0x01
#define PALETTE_VOLTAGE 5
#define PALETTE_AMPERAGE 2000
#define DEVICE_NAME "PALETTE"
#define BT_DEVICE_TYPE "20043C" // sets device type to loudspeaker?

// ---------------------- RN52 config ---------------------- //
#define RN52_SERIAL Serial1
#define RN52_SERIAL_BAUD 115200
#define BLUETOOTH_SERIAL_BUFFER_LENGTH 80

#define RN52_GPI02_PIN 8 // RN52 GPIO2 event notifier pin (default HIGH,
// HIGH -> LOW for 100ms on connected device event)

#define RN52_CMD_PIN 2   // GPIO9 LOW for command mode
#define BT_CHECK_IF_FACTORY_SETTINGS false

// ---------------------- WS2812b config ---------------------- //
#define STRIP_TYPE WS2812B
#define DATA_PIN 3
#define NUM_LEDS 144

#define LED_CONST_FRAMERATE false
#ifdef LED_CONST_FRAMERATE
# define LED_FRAMERATE 69
#endif // ifdef LED_CONST_FRAMERATE

// #define NUM_LEDS_16 NUM_LEDS * 255; // delete multiplication in #define
// int c = NUM_LEDS * 0.5;
// #define CENTER_LED_POS NUM_LEDS * 0.5
#define CENTER_LED_POS 72

// #define HALF_POS_16 NUM_LEDS_16 * 0.5; // delete multiplication in #define
#define COLOR_ORDER GRB
#define LED_COLOR_CORRECTION TypicalLEDStrip
#define FFT_FIXED_SEGMENT_LENGTH NUM_LEDS / NUM_BANDS


// #define HUE_LENGTH floor(255 / NUM_BANDS - 1);
#define PALETTE_INDEX_INCREMENT 248.0 / NUM_LEDS;
#define PALETTE_INDEX_INCREMENT_TWELVE 4095 / NUM_LEDS;

// -------------- Animation Controller config --------------- //
#define NUM_ANIMATIONS 5
#define SECONDS_PER_DEMO_ANIMATION 10

// --------------------- EEPROM config --------------------- //
// #define PALETTE_ADDRESS 0
// #define EFFECT_ADDRESS 1

// ---------------------- FFT config ---------------------- //
#define NUM_BANDS 32
#define MAX_BIN 511
#define WAIT_FOR_FFT_AVAILABILITY true

// ------------------ color palette config ------------------ //
#define COLOR_PALETTE_SPEED 45 // speed for switching between palettes
