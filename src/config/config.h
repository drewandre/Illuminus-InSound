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

#define DEBUG true
#define WAIT_FOR_SERIAL false
#define PRODUCT_VERSION 1.0
#define PRODUCT_SHORT_DESCRIPTION "DMX controller."
#define CURRENT_DATE "Fall 2018"

#endif
