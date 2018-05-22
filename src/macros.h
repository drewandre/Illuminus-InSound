#include <Arduino.h>
#include <FastLED.h>
#include <Audio.h>

#include "./helpers/Streaming.h"

// ------------------- Environment config ------------------- //
#define DEBUG

// ---------------------- Debug config ---------------------- //
#ifdef DEBUG

// # define PRINT_MCU_PERFORMANCE

  # define SWSERIAL_BAUD 115200

// # define BT_USE_RN52 // if uncommented, BM64 used
  # define RN52_ANALOG_OUTPUT

  # define PRINT_RN52

  # define DEMO_CYCLE
  # define FIXED_ANIMATION_INDEX 0

// # define PRINT_FFT

// # define PRINT_MAPPED_FFT
// # define PLAY_TONE_SWEEP_ON_STARTUP

#endif // ifdef DEBUG

// -------------------- Palette config -------------------- //
#define PALETTE_VERSION 0x0001
#define PALETTE_VOLTAGE 5
#define PALETTE_AMPERAGE 2000

// ---------------------- BM64 config ---------------------- //
#ifndef BT_USE_RN52          // if uncommented, BM64 used
# define BM64_SERIAL Serial4 // RX4 (31) + TX4 (32)
# define BM64_UART_TX_IND 21 // BM64 to interrupt MCU on input
# define BM64_SERIAL_BAUD 115200
# define BLUETOOTH_SERIAL_BUFFER_LENGTH 80
#endif // ifndef BT_USE_RN52

// ---------------------- RN52 config ---------------------- //
#define RN52_ANALOG_OUTPUT

#define RN52_GPI02_PIN 8     // RN52 GPIO2 event notifier pin (default HIGH,
// HIGH -> LOW for 100ms on connected device event)
// #define CHECK_RN52_FACTORY_SETTINGS
#define HWSERIAL Serial1     // RX1 + TX1
#define HWSERIAL_BAUD 115200 // RN52 must be at either 115200 or 9600 (if 9600
// GPIO7 should be pulled low)
#define RN52_CMD_PIN 2       // In order to enter command mode,
// GPIO9/RN52_CMD_PIN must be pulled LOW
#define DEVICE_NAME "PALETTE"

// ---------------------- WS2812b config ---------------------- //
#define STRIP_TYPE WS2812B
#define DATA_PIN 3
#define NUM_LEDS 144

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

// ------------------ color palette config ------------------ //
#define COLOR_PALETTE_SPEED 45 // speed for switching between palettes
