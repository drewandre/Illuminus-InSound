/*
  InSound:  12-channel DMX controller for use with
            Teensy 3.2 and stereo MSGEQ7 chips.
            Version 1.0 - Boston, MA - Fall 2018

            For use in Boston's Illuminus Festival 2018

  Software by Drew André
    www.drew-andre.com
    www.linkedin.com/in/drewandre,
    www.instagram.com/_drewandre

  Architecture by Stephen Gleason
    https://www.instagram.com/stephengleasonart/
  
  Audio by Tristan Walker
    https://www.walkersounddesign.com/

  Setup notes:
    DMX channel 1 = bin 6 (highest frequency bin) of LEFT channel,
    so data direction should flow RIGHT if looking at InSound.
    See channel_mapping.txt for more information.
 */

#include "./config/config.h"
#include "./debug/debug_manager.h"
#include "./animations/animation_manager.h"
#include "./color_palettes/color_palette_manager.h"
#include "./dmx/dmx_manager.h"
#include "./audio/audio_analyzer.h"

void setup()
{
  DebugManager::initializeSerial();
  DebugManager::printStartupInfo(0);
  DMXManager::initialize();
  AudioAnalyzer::initialize();
  DebugManager::printStartupInfo(1);
}

void loop()
{
#if USE_COLOR_PALETTES
  ColorPaletteManager::runTask();
#endif
  AnimationManager::runTask();
  DMXManager::displayAnimation();
}
