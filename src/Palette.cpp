/*
   PALETTE v1.2: 8-channel LED controller for use with
                'Palette' NeoPixel controller and WS2812b leds
                Version 1.4 - Boston, MA - Spring 2018

   Designed by Drew André: www.drew-andre.com, www.linkedin.com/in/drewandre,
      www.instagram.com/_drewandre
 */

#include "./animations/animation_manager.h"
#include "./leds/led_manager.h"
#include "./bluetooth/bluetooth_manager.h"
#include "./startup/startup_manager.h"
#include "./helpers/performance_monitor/performance_monitor.h"

#include <macros.h>

void setup() {
#if DEBUG == true
  initSerial();
  printStartupInfo(0);
#endif
  restoreSettingsFromEEPROM();
#if PALETTE_USING_BM64 == true
  initBM64();
#else
  initRN52();
  #endif
  initSGTL5000();
  initWS2812B();
#if DEBUG == true
  printStartupInfo(1);
#endif
}

void loop() {
#if PRINT_MCU_PERFORMANCE == true
  printSystemPerformanceEveryNSeconds(5);
#endif

  animationManagerTask();
  ledDisplayTask();
}
