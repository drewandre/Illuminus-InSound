#include <PALETTE.cpp>
// #include <FastLED.h>

void printMCUPerformance() {
  // static unsigned long previousMillis = 0;
  // static long interval = 1000;

  static long loops = 0;
  loops++;

  EVERY_N_SECONDS(1) {
    Serial.println();

    // print MCU speed
    Serial.print("CPU speed (approx):\t\t"); Serial.print(loops); Serial.print("/second");
    Serial.println();
    loops = 0;

    // print LED framework
    Serial.print("LED FPS:\t\t\t");
    Serial.print(LEDS.getFPS());
    Serial.println();

    // print Stereo FFT memory usage
    Serial.print("Stereo FFT memory usage:\t");
    Serial.print("current: ");
    Serial.print(fftL.processorUsage() + fftR.processorUsage());
    Serial.print("\tmax: ");
    Serial.print(fftL.processorUsageMax() + fftR.processorUsageMax());
    Serial.println();

    // print SGTL5000 Total audio processor usage
    Serial.print("Total audio processor usage:\t");
    Serial.print("current: ");
    Serial.print(AudioProcessorUsage());
    Serial.print("\tmax: ");
    Serial.print(AudioProcessorUsageMax());
    Serial.println();

    // print SGTL5000 Total audio memory usage
    Serial.print("Total audio memory usage:\t");
    Serial.print("current: ");
    Serial.print(AudioMemoryUsage());
    Serial.print("\tmax: ");
    Serial.print(AudioMemoryUsageMax());
    Serial.println();
  }
}
