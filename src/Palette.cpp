/*
   PALETTE v1.2: 8-channel LED controller for use with
                'Palette' NeoPixel controller and WS2812b leds
                Version 1.4 - Boston, MA - Spring 2018

   Designed by Drew André: www.drew-andre.com, www.linkedin.com/in/drewandre,
      www.instagram.com/_drewandre
 */

#include <Arduino.h>

#include "./animations/animation_manager.h"
#include "./leds/led_manager.h"
#include "./startup/startup_manager.h"
#include "./helpers/performance_monitor/performance_monitor.h"

#include <macros.h>

void beginBM64ReadTest() {
  Serial.println("------------------- BEGIN -------------------");
}

void endBM64ReadTest() {
  Serial.println("-------------------- END --------------------");
}

void beginBM64Read() {
  String buffer = "";

  buffer = "";
  unsigned long static startTime;
  unsigned long static endTime;

  // while (!Serial4.available()) ;

  startTime = millis();
  endTime   = startTime;

  while ((endTime - startTime) <= 2000) {
    if (Serial4.available()) {
      buffer.concat(Serial4.read());
    }
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

  attachInterrupt(digitalPinToInterrupt(21), beginBM64ReadTest, FALLING);
  attachInterrupt(digitalPinToInterrupt(21), endBM64ReadTest,   RISING);

  Serial4.begin(115200);
}

void loop() {
#ifdef PRINT_MCU_PERFORMANCE
  printMCUPerformance();
#endif // ifdef PRINT_MCU_PERFORMANCE

  // animationManagerTask();
  // ledDisplayTask();

  EVERY_N_SECONDS(5) {
    Serial.println("\n\nSending data to BM64 and waiting for response...");

    byte message[] = { 0xAA, 0x00, 0x01, 0x01, 0xFE };

    // byte message[] = { 0x0E };
    Serial4.write(message, sizeof(message));

    // Serial4.println(0x0E);
    beginBM64Read();
  }
}
