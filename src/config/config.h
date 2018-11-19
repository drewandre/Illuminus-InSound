#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <DmxSimple.h>

#define FASTLED_INTERNAL
#include <FastLED.h>

#include "debug.h"
#include "dmx.h"
#include "animations.h"
#include "MSGEQ7.h"
#include "color_palettes.h"

#define PRODUCT_SHORT_DESCRIPTION "DMX controller."
#define CURRENT_DATE "Fall 2018"
#define DEVICE_NAME "InSound"

#define SWSERIAL_BAUD 9600
#define WAIT_FOR_SERIAL false
#define PRODUCT_VERSION 1.0

#define FILTER_MIN 120
#define FILTER_MAX 600
#define AUDIO_BAND_MAX_AMPLITUDE 255
#define MAX_BRIGHTNESS 255
#define SMOOTHING_ARR 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.4       // low to high frequency
#define FADE_TO_BLACK_VALUES 1, 1, 2, 2, 1, 1, 1              // low to high frequency
#define NSCALE_VALUES 254, 254, 253, 253, 254, 254, 254       // low to high frequency
#define FILTER_MAX_VALUES 600, 600, 1000, 1000, 600, 600, 600 // low to high frequency

#define BLUR_ANIMATION false
#define BLUR_VALUE 10

#define USE_COLOR_PALETTES false
#define COLOR_PALETTE_SPEED 90 // speed for switching between palettes
#define COLOR_PALETTE_BLEND_UPDATE_SPEED_MILLISECONDS 10
#define CHANGE_PALETTE_EVERY_N_SECONDS 10

#define AUDIO_FRAMES_PER_SECOND 20

#endif
