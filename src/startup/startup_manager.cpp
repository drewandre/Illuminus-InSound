#include <Audio.h>
#include <BM64.h>

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

#ifdef BT_USE_RN52
  initRN52();
#else // ifdef BT_USE_RN52
  initBM64();
#endif // ifdef BT_USE_RN52

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
  Serial4.begin(115200);
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

  pinMode(RN52_CMD_PIN, OUTPUT);
  digitalWrite(RN52_CMD_PIN, HIGH); // exit data mode
  HWSERIAL.begin(HWSERIAL_BAUD);

  // if (RN52FactorySettings()) { // checks if device name is equal to
  // DEVICE_NAME
#ifdef DEBUG
  Serial << "Configuring RN52...";
#endif // ifdef DEBUG

  // setRN52("SN", DEVICE_NAME); // sets device name
  // http://bluetooth-pentest.narod.ru/software/bluetooth_class_of_device-service_generator.html
  // setRN52("SC", "20043C"); // COD -- Audio, Audio/Video, Video Display and
  // Loudspeaker
  // setRN52("ST", "00");   // mutes disable tones
  #ifdef RN52_ANALOG_OUTPUT

  // setRN52("S|", "00");   // sets audio output to analog out
  // setRN52("SS", "0x09"); // sets speaker gain to maximum
  #else // ifdef RN52_ANALOG_OUTPUT

  // setRN52("S|", "0102");
  #endif // ifdef RN52_ANALOG_OUTPUT

  // }
#ifdef DEBUG

  // printRN52("D"); // prints status
  // printRN52("V"); // prints version number

  static unsigned long totalTime = millis() - startTime;
  Serial << "RN52 Initialized:\t" << totalTime << "ms" << "\n\n";
#endif // ifdef DEBUG
}

void initBM64() {
  BM64 BM64(BM64_UART_TX_IND, BM64_SERIAL);

  BM64.enable();
}

void initWS2812B() {
#ifdef DEBUG
  static unsigned long startTime = millis();
#endif // ifdef DEBUG

  FastLED.addLeds<STRIP_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);

#ifdef LED_COLOR_CORRECTION
  FastLED.setCorrection(LED_COLOR_CORRECTION);
  Serial <<
    "\n~~~~~~~~~~~~~~~~~~~~~~ set framerate to 69 ~~~~~~~~~~~~~~~~~~~~~~\n\n";
#endif // ifdef LED_COLOR_CORRECTION

  FastLED.setMaxRefreshRate(69);
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

  SGTL5000.enable(); // only if audio out (audio out just comes from RN52 --
  // audio in would require SGTL5000)

#ifdef RN52_ANALOG_OUTPUT

  // WARNING: DO NOT uncomment if using AudioInputI2Sslave -- two inputs (one
  // from the line below) will stress pin 13

  SGTL5000.inputSelect(AUDIO_INPUT_LINEIN);
  SGTL5000.lineInLevel(15);

#endif // ifdef RN52_ANALOG_OUTPUT

  SGTL5000.volume(0.5);

#ifdef DEBUG
  # ifdef PLAY_TONE_SWEEP_ON_STARTUP

  while (1) {
    float   t_ampx     = 0.3;
    uint8_t t_lox      = 20;
    unsigned int t_hix = 12000;
    float t_timex      = 2; // Length of time for the sweep in seconds

    if (!tone_sweep.play(t_ampx, t_lox, t_hix, t_timex)) {
      Serial << "AudioSynthToneSweep - begin failed" << "\n";

      while (1) ;
    }

    while (tone_sweep.isPlaying()) ;                       // wait for the sweep
                                                           // to end

    if (!tone_sweep.play(t_ampx, t_hix, t_lox, t_timex)) { // and now reverse
                                                           // the sweep
      Serial << "AudioSynthToneSweep - begin failed" << "\n";

      while (1) ;
    }

    while (tone_sweep.isPlaying()) ;  // wait for the sweep to end
    Serial << "Done" << "\n"
  }
  # endif // ifdef PLAY_TONE_SWEEP_ON_STARTUP

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
