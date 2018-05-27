#include "./debug_manager.h"
#include "../../audio/audio_manager.h"

namespace DebugManager {
void printStartupInfo(uint8_t stage) {
  switch (stage) {
  case 0:
    static unsigned long startTime = millis();
    Serial << "\n===================== INITIALIZING " << DEVICE_NAME <<
      " =====================\n";
    Serial <<  "PALETTE " << PALETTE_VERSION << endl <<
      PALETTE_SHORT_DESCRIPTION <<
      endl;
    Serial << "Designed by Drew André in Boston, MA - " << CURRENT_DATE << endl;
    Serial << "www.drew-andre.com" << endl;
    Serial <<
      "-----------------------------------------------------------------\n";
    break;

  case 1:
    static unsigned long totalTime = millis() - startTime;
    Serial << "\n" << DEVICE_NAME << " configured in " << totalTime << "ms\n" <<
      "\n================= " << DEVICE_NAME <<
      " MAIN APPLICATION LOOP =================\n";
    break;
  }
}

void printSystemPerformanceEveryNSeconds(int seconds) {
  static long loops = 0;

  loops++;

  EVERY_N_SECONDS(seconds) {
    Serial << endl;

    // print MCU speed
    Serial << "CPU speed (approx):\t\t" << loops << "/second" << endl;
    loops = 0;

    // print LED framework
    Serial << "LED FPS:\t\t\t" << LEDS.getFPS() << endl;

    // print Stereo FFT memory usage
    Serial << "Stereo FFT memory usage:\tcurrent: " << fftL.processorUsage()
      +
      fftR.processorUsage() << "\tmax: " << fftL.processorUsageMax() +
      fftR.processorUsageMax() << endl;

    // print SGTL5000 Total audio processor usage
    Serial << "Total audio processor usage:\tcurrent: " <<
      AudioProcessorUsage() <<
      "\tmax: " << AudioProcessorUsageMax() << endl;

    // print SGTL5000 Total audio memory usage
    Serial << "Total audio memory usage:\tcurrent: " << AudioMemoryUsage() <<
      "\tmax: " << AudioMemoryUsageMax() << endl;
  }
}
}
