/*
   InSound: 12-channel DMX controller for use with
                Teensy 3.6 and Teensy audio shield.
                Version 1.0 - Boston, MA - Fall 2018

   Designed by Drew André: www.drew-andre.com, www.linkedin.com/in/drewandre,
      www.instagram.com/_drewandre
 */

#include "./config/config.h"

#if DEBUG == true
#include "./helpers/debug_manager/debug_manager.h"
using namespace DebugManager;
#endif

#include "./animations/animation_manager.h"
#include "./dmx/dmx_manager.h"
#include "./audio/audio_analyzer.h"

void setup()
{
#if DEBUG == true
  initializeSerial();
  printStartupInfo(0);
#endif
  DMXManager::initialize();
  // AudioAnalyzer::initialize();

#if DEBUG == true
  printStartupInfo(1);
#endif
}

void loop()
{
  static int i = 0;
#if PRINT_MCU_PERFORMANCE == true
  printSystemPerformanceEveryNSeconds(5);
#endif

  // AnimationManager::runTask();
  EVERY_N_MILLISECONDS(10)
  {
    i++;
    if (i > 255)
    {
      i = 0;
    }
  }
  DMXManager::testCRGB(CHSV(i, 255, 255));
}
