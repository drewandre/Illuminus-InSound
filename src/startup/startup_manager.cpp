#include <Audio.h>

#if BM64 == true
# include <BM64.h>
#else // if BM64 == true
# include <RN52.h>
#endif // if BM64 == true

#include "../leds/led_manager.h"
#include "./startup_manager.h"

#include <macros.h>

/*======================*/
/*  external variables  */
struct AudioControlSGTL5000 SGTL5000;
uint16_t fftBins[NUM_BANDS];

/*======================*/

void startup() {
#ifdef DEBUG
  static unsigned long startTime = millis();

  initSerial();
  Serial << "\n---------------------- INITIALIZING ----------------------\n";
#endif // ifdef DEBUG

  // initEEPROM();

#if BM64 == true
  initBM64();
#else // if BM64 == true
  initRN52();
#endif // if BM64 == true
  initSGTL5000();
  initWS2812B();

  // initNoise();

#ifdef DEBUG
  static unsigned long totalTime = millis() - startTime;

  Serial << "\n" << DEVICE_NAME << " configured!\n\n" <<
    "Dev startup time:\t" <<
    totalTime << "ms\n" << "\n---------------------- " << DEVICE_NAME <<
    " MAIN APPLICATION LOOP ----------------------\n";
#endif // ifdef DEBUG
}

void initSerial() {
#ifdef DEBUG
  Serial.begin(SWSERIAL_BAUD);
  Serial << '\n';

  while (!Serial) ;
#endif // ifdef DEBUG
}

void initEEPROM() {
#ifdef DEBUG
  static unsigned long startTime = millis();
#endif // ifdef DEBUG

#ifdef DEBUG
  static unsigned long totalTime = millis() - startTime;

  Serial << "Settings restored:\t" << totalTime << "ms" << "\n\n";
#endif // ifdef DEBUG
}

void initRN52() {
#ifdef DEBUG
  static unsigned long startTime = millis();
#endif // ifdef DEBUG
  RN52 RN52(RN52_CMD_PIN, &Serial1);

  RN52.enable();

#ifdef DEBUG
  RN52.printVersion();
  RN52.printStatus();
#endif // ifdef DEBUG

#ifdef BT_CHECK_IF_FACTORY_SETTINGS

  if (RN52.factorySettings(DEVICE_NAME)) { // checks device name
#endif // ifdef BT_CHECK_IF_FACTORY_SETTINGS
  RN52.setDeviceName(DEVICE_NAME);
  RN52.setDeviceType(BT_DEVICE_TYPE);      // sets device name loudspeaker?
  RN52.muteTones();
  RN52.setAnalogAudioOutput();
  RN52.setMaxSpeakerGain();
#ifdef BT_CHECK_IF_FACTORY_SETTINGS
}

#endif // ifdef BT_CHECK_IF_FACTORY_SETTINGS

#ifdef DEBUG
  static unsigned long totalTime = millis() - startTime;
  Serial << "RN52 Initialized:\t" << totalTime << "ms" << "\n\n";
#endif // ifdef DEBUG
}

#if BM64 == true
void initBM64() {
  BM64 BM64(BM64_UART_TX_IND, BM64_SERIAL);

  BM64.enable();
}

#endif // if BM64 == true

void initWS2812B() {
#ifdef DEBUG
  static unsigned long startTime = millis();
#endif // ifdef DEBUG

  FastLED.addLeds<STRIP_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);

#ifdef LED_COLOR_CORRECTION
  FastLED.setCorrection(LED_COLOR_CORRECTION);

#endif // ifdef LED_COLOR_CORRECTION

#if LED_CONST_FRAMERATE
  Serial << STRIP_TYPE << " framerate set to " << LED_FRAMERATE;
  FastLED.setMaxRefreshRate(LED_FRAMERATE);
#endif // ifdef LED_COLOR_CORRECTION
  FastLED.setBrightness(255);
  FastLED.setMaxPowerInVoltsAndMilliamps(PALETTE_VOLTAGE, PALETTE_AMPERAGE);

  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
  delay(10);

#ifdef DEBUG
  static unsigned long totalTime = millis() - startTime;
  Serial << "Leds Initialized:\t" << totalTime << "ms" << endl;
#endif // ifdef DEBUG
}

void initSGTL5000() {
#ifdef DEBUG
  static unsigned long startTime = millis();
#endif // ifdef DEBUG

  float e = getFFTBins();

  AudioMemory(20);

  SGTL5000.enable();
  SGTL5000.inputSelect(AUDIO_INPUT_LINEIN);
  SGTL5000.lineInLevel(15);
  SGTL5000.volume(0.5);

#ifdef DEBUG
  static unsigned long totalTime = millis() - startTime;

  Serial << "Audio Initialized:\t" << totalTime << "ms" << endl;
  Serial << "FFT NUM_BANDS:\t\t" << NUM_BANDS << endl;
  Serial << "FFT MAX_BIN:\t\t" << MAX_BIN << "hz" << endl;
  Serial << "FFT E calculation:\t" << e << endl;
#endif // ifdef DEBUG
}

float getFFTBins() {
  float e, n;
  uint16_t b, bands, bins, count = 0, d;

  bands = NUM_BANDS;              // Frequency bands; (Adjust to desiredvalue)
  bins  = MAX_BIN;
  e     = FindE(bands, bins);     // Find calculated E value

  if (e) {                        // If a value was returned continue
    for (b = 0; b < bands; b++) { // Test and print the bins from the calculated
      n          = pow(e, b);
      d          = int(n + 0.5);
      fftBins[b] = count;
      count     += d - 1;
      ++count;
    }
  }
#ifdef DEBUG
  else {
    Serial << "Error calculating FFT bins\n"; // Error, something happened
  }
#endif // ifdef DEBUG

  return e;
}

float FindE(uint8_t bands, uint8_t bins) {
  float   increment = 0.1, eTest, n;
  uint8_t b, count, d;

  for (eTest = 1; eTest < bins; eTest += increment) { // Find E through brute
                                                      // force calculations
    count = 0;

    for (b = 0; b < bands; b++) {                     // Calculate full log
                                                      // values
      n      = pow(eTest, b);
      d      = int(n + 0.5);
      count += d;
    }

    if (count > bins) {       // We calculated over our last bin
      eTest     -= increment; // Revert back to previous calculation
      increment /= 10.0;      // Get a finer detailed calculation & increment a

      // decimal point lower
    }
    else if (count == bins)    // We found the correct E
      return eTest;            // Return calculated E

    if (increment < 0.0000001) // Ran out of calculations. Return previous E.
                               // Last bin will be lower than (bins-1)
      return eTest - increment;
  }
  return 0;                    // Return error 0
}

void initNoise() {
#ifdef DEBUG
  static unsigned long startTime = millis();
#endif // ifdef DEBUG

  // x    = random16();
  // y    = random16();
  // z    = random16();
  // dist = random16(12345);
#ifdef DEBUG
  static unsigned long totalTime = millis() - startTime;

  Serial << "Noise values set:\t" << totalTime << "ms" << "\n";
#endif // ifdef DEBUG
}
