/*
   PALETTE v1.2: 8-channel LED controller for use with
                'Palette' NeoPixel controller and WS2812b leds
                Version 1.4 - Boston, MA - Spring 2018

   Designed by Drew André: www.drew-andre.com, www.linkedin.com/in/drewandre,
      www.instagram.com/_drewandre
 */

#include <Palette.h>

void setup() {
#if DEBUG == true
  DebugManager::initializeSerial();
  DebugManager::printStartupInfo(0);
#endif

  LEDManager::initialize();
  BluetoothManager::initialize();
  AudioManager::initialize();
  AudioAnalyzer::initialize();

#if DEBUG == true
  DebugManager::printStartupInfo(1);
#endif
}

void loop() {
#if PRINT_MCU_PERFORMANCE == true
  DebugManager::printSystemPerformanceEveryNSeconds(5);
#endif
  AnimationManager::runTask();
  LEDManager::show();
}
