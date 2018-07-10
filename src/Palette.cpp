/*
   PALETTE v1.2: 8-channel LED controller for use with
                'Palette' NeoPixel controller and WS2812b leds
                Version 1.4 - Boston, MA - Spring 2018

   Designed by Drew André: www.drew-andre.com, www.linkedin.com/in/drewandre,
      www.instagram.com/_drewandre
 */

#include "./macros.h"

#if DEBUG == true
# include "./helpers/debug_manager/debug_manager.h"
using namespace DebugManager;
#endif


#include "./animations/animation_manager.h"
#include "./leds/led_manager.h"
#include "./audio/audio_manager.h"
#include "./bluetooth/bluetooth_manager.h"

void setup() {
#if DEBUG == true
  initializeSerial();
  printStartupInfo(0);
#endif
  LEDManager::initialize();
  AudioManager::initialize();
  AudioManager::initializeFFT();
  BluetoothManager::initialize();

#if DEBUG == true
  printStartupInfo(1);
#endif
}

String buffer = "";

// unsigned long appStartupMillis = millis();
bool startupFlag = true;

// Serial.println("Entering data mode on channel 14...");
// bc127.stdCmd("ENTER_DATA_MODE 14");

void loop() {
  BluetoothManager::enableBLEAdvertising();
  startupFlag = false;

  while (startupFlag == false) {
  #if PRINT_MCU_PERFORMANCE == true
    printSystemPerformanceEveryNSeconds(5);
  #endif
    BluetoothManager::listenAndHandleSPPData();

    // AnimationManager::runTask();
    // LEDManager::show();
  }
}
