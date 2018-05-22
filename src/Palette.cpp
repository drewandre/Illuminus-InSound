/*
   PALETTE v1.2: 8-channel LED controller for use with
                'Palette' NeoPixel controller and WS2812b leds
                Version 1.4 - Boston, MA - Spring 2018

   Designed by Drew André: www.drew-andre.com, www.linkedin.com/in/drewandre,
      www.instagram.com/_drewandre
 */

#include "./animations/animation_manager.h"
#include "./leds/led_manager.h"
#include "./startup/startup_manager.h"
#include "./helpers/performance_monitor/performance_monitor.h"

#include <macros.h>

void beginBM64Read() {
  String buffer = "";

  buffer = "";
  unsigned long static startTime;
  unsigned long static endTime;

  startTime = millis();
  endTime   = startTime;


  while ((endTime - startTime) <= 1000) {
    // if (Serial4.available()) {
    buffer.concat(Serial4.read());

    // }

    delay(1);
    endTime = millis();
  }
  Serial << "BM64 > " << buffer << endl;
}

void endBM64Read() {
  Serial.println(
    "~~~~~~~~~~~~~~~~~~~~~ Ending BM64 communication ~~~~~~~~~~~~~~~~~~~~~");
}

void setup() {
  startup();

  // attachInterrupt(digitalPinToInterrupt(21), beginBM64Read, FALLING);
  // attachInterrupt(digitalPinToInterrupt(21), endBM64Read,   RISING);
}

void loop() {
#ifdef PRINT_MCU_PERFORMANCE
  printMCUPerformance();
#endif // ifdef PRINT_MCU_PERFORMANCE

  // animationManagerTask();
  // ledDisplayTask();

  EVERY_N_SECONDS(5) {
    Serial.println("\n\nSending 0x00 to BM64 and waiting for response...");
    Serial4.println(0x0E);
    beginBM64Read();
  }
}
