#include "./startup_manager.h"
#include <macros.h>

void initSerial() {
#if DEBUG == true
  Serial.begin(SWSERIAL_BAUD);

  while (!Serial) ;
#endif
}

void restoreSettingsFromEEPROM() {
#if DEBUG == true
  static unsigned long startTime = millis();
  Serial <<
    "\n================ RESTORING SETTINGS FROM EEPROM =================\n";
#endif

#if DEBUG == true
  static unsigned long totalTime = millis() - startTime;

  Serial << "EEPROM restored:\t" << totalTime << "ms" << "\n";
  Serial << "-----------------------------------------------------------------\n";
#endif
}

void initBM64() {
  struct BM64 BM64;

#if DEBUG == true
  static unsigned long startTime = millis();
  Serial <<
    "\n======================= INITIALIZING BM64 =======================\n";
#endif

  BM64.enable();


  // while (1) {
  //   // Serial4.begin(115200);
  //   EVERY_N_SECONDS(2) {
  //     Serial4.write(0x0E);
  //   }
  //   EVERY_N_SECONDS(5) {
  //     Serial4.write(0x03);
  //   }
  //
  //   BM64.readSerial();
  //   delay(5);
  // }

#if DEBUG == true
  static unsigned long totalTime = millis() - startTime;
  Serial << "BM64 Initialized:\t" << totalTime << "ms" << "\n\n";
  Serial << "-----------------------------------------------------------------\n";
#endif
}

void initRN52() {
  struct RN52 RN52; // external object

#if DEBUG == true
  static unsigned long startTime = millis();
  Serial <<
    "\n======================= INITIALIZING RN52 =======================\n";
#endif

  RN52.enable();

#if DEBUG == true
  RN52.printVersion();
  RN52.printStatus();
#endif

#if BT_CHECK_IF_FACTORY_SETTINGS == true

  if (RN52.factorySettings(DEVICE_NAME)) { // checks device name
#endif
  RN52.setDeviceName(DEVICE_NAME);
  RN52.setDeviceType(BT_DEVICE_TYPE);      // sets device name loudspeaker?
  RN52.muteTones();
  RN52.setAnalogAudioOutput();
  RN52.setMaxSpeakerGain();
#if BT_CHECK_IF_FACTORY_SETTINGS == true
}

#endif

#if DEBUG == true
  static unsigned long totalTime = millis() - startTime;
  Serial << "RN52 Initialized:\t" << totalTime << "ms" << "\n";
  Serial << "-----------------------------------------------------------------\n";
#endif
}

void initWS2812B() {
  struct CRGB leds[NUM_LEDS];

#if DEBUG == true
  static unsigned long startTime = millis();
  Serial <<
    "\n======================= INITIALIZING LEDS =======================\n";
#endif

  FastLED.addLeds<STRIP_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);

#if LED_COLOR_CORRECTION == true
  FastLED.setCorrection(LED_COLOR_CORRECTION);

#endif

#if LED_CONST_FRAMERATE == true
  Serial << STRIP_TYPE << " framerate set to " << LED_FRAMERATE;
  FastLED.setMaxRefreshRate(LED_FRAMERATE);
#endif
  FastLED.setBrightness(255);
  FastLED.setMaxPowerInVoltsAndMilliamps(PALETTE_VOLTAGE, PALETTE_AMPERAGE);

  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
  delay(10);

#if DEBUG == true
  static unsigned long totalTime = millis() - startTime;
  Serial << "Leds Initialized:\t" << totalTime << "ms" << endl;
  Serial << "-----------------------------------------------------------------\n";
#endif
}

void initSGTL5000() {
  struct AudioControlSGTL5000 SGTL5000; // external object

#if DEBUG == true
  static unsigned long startTime = millis();
  Serial <<
    "\n===================== INITIALIZING SGTL5000 =====================\n";
#endif

  float e = getFFTBins();

  AudioMemory(20);

  SGTL5000.enable();
  SGTL5000.inputSelect(AUDIO_INPUT_LINEIN);
  SGTL5000.lineInLevel(15);
  SGTL5000.volume(0.5);

#if DEBUG == true
  static unsigned long totalTime = millis() - startTime;

  Serial << "Audio Initialized:\t" << totalTime << "ms" << endl;
  Serial << "  - FFT NUM_BANDS:\t" << NUM_BANDS << endl;
  Serial << "  - FFT MAX_BIN:\t" << MAX_BIN << "hz" << endl;
  Serial << "  - FFT E calculation:\t" << e << endl;
  Serial << "-----------------------------------------------------------------\n";
#endif
}

uint16_t fftBins[NUM_BANDS]; // external variable
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
#if DEBUG == true
  else {
    Serial << "Error calculating FFT bins\n"; // Error, something happened
  }
#endif

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
