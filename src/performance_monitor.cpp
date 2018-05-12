#include <env_config.h>
#include <FastLED.h>
#include <Audio.h>

void printMCUPerformance() {
  // static unsigned long previousMillis = 0;
  // static long interval = 1000;

  static long loops = 0;
  loops++;

  EVERY_N_SECONDS(1) {
    cout << endl;

    // print MCU speed
    cout << "CPU speed (approx):\t\t"; cout << loops; cout << "/second"; cout << endl;
    loops = 0;

    // print LED framework
    cout << "LED FPS:\t\t\t";
    cout << LEDS.getFPS();
    cout << endl;

    // print Stereo FFT memory usage
    cout << "Stereo FFT memory usage:\tcurrent: ";
    cout << fftL.processorUsage() + fftR.processorUsage();
    cout << "\tmax: ";
    cout << fftL.processorUsageMax() + fftR.processorUsageMax();
    cout << endl;

    // print SGTL5000 Total audio processor usage
    cout << "Total audio processor usage:\tcurrent: ";
    cout << AudioProcessorUsage();
    cout << "\tmax: ";
    cout << AudioProcessorUsageMax();
    cout << endl;

    // print SGTL5000 Total audio memory usage
    cout << "Total audio memory usage:\tcurrent: ";
    cout << AudioMemoryUsage();
    cout << "\tmax: ";
    cout << AudioMemoryUsageMax();
    cout << endl;
  }
}
