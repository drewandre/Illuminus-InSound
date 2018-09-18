#ifndef MACROS_H
#define MACROS_H

#include <Arduino.h>
#include <FastLED.h>
#include <Audio.h>
#include <BC127.h>

// -------------------- Palette config -------------------- //
#define DEBUG true

#define CYCLE_THROUGH_ANIMATIONS false
#define PRODUCT_VERSION 1.4
#define PALETTE_VOLTAGE 5
#define PALETTE_AMPERAGE 2000
#define DEVICE_NAME "PALETTE"
#define BT_DEVICE_TYPE "20043C" // sets device type to loudspeaker?
#define PRODUCT_SHORT_DESCRIPTION \
  "Smartphone controlled LED bar with audio reactive animations."

// ---------------------- Debug config ---------------------- //
#if DEBUG == true
  # include "./helpers/Streaming.h"
  # define PRINT_MCU_PERFORMANCE false
  # define SWSERIAL_BAUD 115200
  # define PRINT_FFT false
  # define PRINT_MAPPED_FFT false
  # define PRINT_FFT_SETTINGS true
#endif

// ---------------------- BC127 config ---------------------- //
#define BC127_SERIAL Serial1
#define BC127_SERIAL_BAUD 9600
#define BC127_CMD_PIN 2
#define BC127_GPIO_0_PIN 35
#define BC127_GPIO_4_PIN 36
#define BT_CHECK_IF_FACTORY_SETTINGS false
#define BC127_ANALOG_OUTPUT true
#define ECHO_BT_MODULE true

// ---------------------- WS2812b config ---------------------- //
#define STRIP_TYPE WS2812B
#define DATA_PIN 3
#define NUM_LEDS 144
#define LED_CONST_FRAMERATE false
#if LED_CONST_FRAMERATE == true
# define LED_FRAMERATE 69
#endif // ifdef LED_CONST_FRAMERATE
// #define NUM_LEDS_16 NUM_LEDS * 255; // delete multiplication in #define
// int c = NUM_LEDS * 0.5;
// #define CENTER_LED_POS NUM_LEDS * 0.5
#define CENTER_LED_POS 72

// #define HALF_POS_16 NUM_LEDS_16 * 0.5; // delete multiplication in #define
#define COLOR_ORDER GRB
#define LED_COLOR_CORRECTION TypicalLEDStrip

// #define HUE_LENGTH floor(255 / NUM_BANDS - 1);
#define PALETTE_INDEX_INCREMENT 248.0 / NUM_LEDS;
#define PALETTE_INDEX_INCREMENT_TWELVE 4095 / NUM_LEDS;

// -------------- Animation Controller config --------------- //
#define NUM_ANIMATIONS 5
#define SECONDS_PER_DEMO_ANIMATION 10
#define FIXED_ANIMATION_INDEX false
#if FIXED_ANIMATION_INDEX == true
# define FIXED_ANIMATION_INDEX 0
#endif

// -------------------- SGTL5000 config --------------------- //
#define AUDIO_IN AUDIO_INPUT_LINEIN

// ---------------------- FFT config ---------------------- //
#define NUM_BANDS 32
#define MAX_BIN 511
#define WAIT_FOR_FFT_AVAILABILITY true

// ------------------ color palette config ------------------ //
#define CHANGE_PALATTE_PERIODICALLY true
#if CHANGE_PALATTE_PERIODICALLY == true
# define CHANGE_PALETTE_EVERY_N_SECONDS 10
#endif
#define COLOR_PALETTE_SPEED 45 // speed for switching
// between palettes
#define COLOR_PALETTE_BLEND_UPDATE_SPEED_MILLISECONDS 10

// -------------------------- misc -------------------------- //
#define CURRENT_DATE "Spring 2018"

#endif
