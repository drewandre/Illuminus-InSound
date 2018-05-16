#include "../../audio/audio_manager.h"

void printMCUPerformance() {
  static long loops = 0;

  loops++;

  EVERY_N_SECONDS(1) {
    Serial << endl;

    // print MCU speed
    Serial << "CPU speed (approx):\t\t" << loops << "/second" << endl;
    loops = 0;

    // print LED framework
    Serial << "LED FPS:\t\t\t" << LEDS.getFPS() << endl;

    // print Stereo FFT memory usage
    Serial << "Stereo FFT memory usage:\tcurrent: " << fftL.processorUsage() +
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
