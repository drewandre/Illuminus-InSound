#include <env.h>

void printMCUPerformance() {
  // static unsigned long previousMillis = 0;
  // static long interval = 1000;
  static long loops = 0;

  loops++;

  EVERY_N_SECONDS(1) {
    cout << endl;

    // print MCU speed
    cout << "CPU speed (approx):\t\t" << loops << "/second\n";
    loops = 0;

    // print LED framework
    cout << "LED FPS:\t\t\t" << LEDS.getFPS() << endl;

    // print Stereo FFT memory usage
    cout << "Stereo FFT memory usage:\tcurrent: " << fftL.processorUsage() +
    fftR.processorUsage() << "\tmax: " << fftL.processorUsageMax() +
    fftR.processorUsageMax() << endl;

    // print SGTL5000 Total audio processor usage
    cout << "Total audio processor usage:\tcurrent: " << AudioProcessorUsage() <<
    "\tmax: " << AudioProcessorUsageMax() << endl;

    // print SGTL5000 Total audio memory usage
    cout << "Total audio memory usage:\tcurrent: " << AudioMemoryUsage() <<
    "\tmax: " << AudioMemoryUsageMax() << endl;
  }
}
