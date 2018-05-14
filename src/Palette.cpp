/*
   PALETTE v1.2: 8-channel LED controller for use with
                'Palette' NeoPixel controller and WS2812b leds
                Version 1.4 - Boston, MA - Spring 2018

   Designed by Drew André: www.drew-andre.com, www.linkedin.com/in/drewandre,
      www.instagram.com/_drewandre
 */

// #include <env.h>

#include <animation_manager.h>
#include <led_manager.h>
#include <startup_manager.h>
#include <performance_monitor.h>


void setup() {
  startup();
}

int main() {
#ifdef PRINT_MCU_PERFORMANCE
  printMCUPerformance();
#endif // ifdef PRINT_MCU_PERFORMANCE

  animationManagerTask();
  ledDisplayTask();
}
