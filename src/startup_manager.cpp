#include <Audio.h>
#include <FastLED.h>
#include <env_config.h>
#include <initialize.h>
#include <bluetooth_manager.h>

void initialize() {
#ifdef DEBUG
static unsigned long startTime = millis();
  initSerial();
  Serial.println("\n---------------------- INITIALIZING ----------------------\n");
#endif
  initEEPROM();
  initRN52();
  initSGTL5000();
  initWS2812B();
  // initNoise();

  BM64SERIAL.begin(BM64_SERIAL_BAUD);

#ifdef DEBUG
  unsigned long totalTime = millis() - startTime;
  Serial.println();
  Serial.print(DEVICE_NAME); Serial.print(" configured!\n\n");
  Serial.print("Dev startup time:\t");
  Serial.print(totalTime);
  Serial.println("ms");
  Serial.print("\n---------------------- "); Serial.print(DEVICE_NAME); Serial.print(" MAIN APPLICATION LOOP ----------------------\n");
#endif
}

void initSerial() {
#ifdef DEBUG
  Serial.begin(SWSERIAL_BAUD);
  while(!Serial);
#endif
}

void initEEPROM() {
#ifdef DEBUG
  unsigned long startTime = millis();
#endif
#ifdef DEBUG
  unsigned long totalTime = millis() - startTime;
  Serial.print("Settings restored:\t");
  Serial.print(totalTime);
  Serial.print("ms");
  Serial.println("\n");
#endif
}

void initRN52() {
#ifdef DEBUG
  unsigned long startTime = millis();
#endif
  pinMode(RN52_CMD_PIN, OUTPUT);
  digitalWrite(RN52_CMD_PIN, HIGH); // exit data mode
  HWSERIAL.begin(HWSERIAL_BAUD);
  // if (RN52FactorySettings()) { // checks if device name is equal to DEVICE_NAME
  #ifdef DEBUG
    Serial.println("Configuring RN52...");
  #endif
    // setRN52("SN", DEVICE_NAME); // sets device name
    // http://bluetooth-pentest.narod.ru/software/bluetooth_class_of_device-service_generator.html
    // setRN52("SC", "20043C"); // COD -- Audio, Audio/Video, Video Display and Loudspeaker
    // setRN52("ST", "00"); // mutes disable tones
  #ifdef RN52_ANALOG_OUTPUT
    // setRN52("S|", "00"); // sets audio output to analog out
    // setRN52("SS", "0x09"); // sets speaker gain to maximum
  #else
    // setRN52("S|", "0102");
  #endif
  // }
#ifdef DEBUG
  // printRN52("D"); // prints status
  // printRN52("V"); // prints version number

  pinMode(RN52_GPI02_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(RN52_GPI02_PIN), readRN52Event, CHANGE);

  unsigned long totalTime = millis() - startTime;
  Serial.print("RN52 Initialized:\t");
  Serial.print(totalTime);
  Serial.print("ms");
  Serial.println("\n");
#endif
}


void initWS2812B() {
#ifdef DEBUG
  unsigned long startTime = millis();
#endif
  FastLED.addLeds<STRIP_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
#ifdef LED_COLOR_CORRECTION
  FastLED.setCorrection(LED_COLOR_CORRECTION);
#endif
  FastLED.setMaxPowerInVoltsAndMilliamps(PALETTE_VOLTAGE, PALETTE_AMPERAGE);
  FastLED.setBrightness(255);
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
  delay(10);
#ifdef DEBUG
  unsigned long totalTime = millis() - startTime;
  Serial.print("Leds Initialized:\t");
  Serial.print(totalTime);
  Serial.print("ms");
  Serial.println();
#endif
}

void initSGTL5000() {
#ifdef DEBUG
  unsigned long startTime = millis();
#endif
  float e = getFFTBins();
  AudioMemory(20);
  SGTL5000.enable(); // only if audio out (audio out just comes from RN52 -- audio in would require SGTL5000)
#ifdef RN52_ANALOG_OUTPUT
  // WARNING: DO NOT uncomment if using AudioInputI2Sslave -- two inputs (one from the line below) will stress pin 13
  SGTL5000.inputSelect(AUDIO_IN);
  SGTL5000.lineInLevel(15);
#endif
  // SGTL5000.volume(0.5);

#ifdef DEBUG
  #ifdef PLAY_TONE_SWEEP_ON_STARTUP
  while(1) {
    float t_ampx = 0.3;
    int t_lox = 20;
    int t_hix = 12000;
    float t_timex = 2; // Length of time for the sweep in seconds

    if(!tone_sweep.play(t_ampx,t_lox,t_hix,t_timex)) {
      Serial.println("AudioSynthToneSweep - begin failed");
      while(1);
    }
    while(tone_sweep.isPlaying()); // wait for the sweep to end

    if(!tone_sweep.play(t_ampx,t_hix,t_lox,t_timex)) { // and now reverse the sweep
      Serial.println("AudioSynthToneSweep - begin failed");
      while(1);
    }

    while(tone_sweep.isPlaying()); // wait for the sweep to end
    Serial.println("Done");
  }
  #endif
  unsigned long totalTime = millis() - startTime;
  Serial.print("Audio Initialized:\t");
  Serial.print(totalTime);
  Serial.println("ms");
  Serial.print("FFT NUM_BANDS:\t\t");
  Serial.println(NUM_BANDS);
  Serial.print("FFT MAX_BIN:\t\t");
  Serial.print(MAX_BIN);
  Serial.println("hz");
  Serial.print("FFT E calculation:\t");
  Serial.println(e);
  Serial.println();
#endif
}

float getFFTBins() {
  float e, n;
  uint16_t b, bands, bins, count = 0, d;
  bands = NUM_BANDS;                      // Frequency bands; (Adjust to desired value)
  bins = MAX_BIN;
  e = FindE(bands, bins);                 // Find calculated E value
  if (e) {                                // If a value was returned continue
    for (b = 0; b < bands; b++) {         // Test and print the bins from the calculated E
      n = pow(e, b);
      d = int(n + 0.5);
      extern uint16_t fftBins[b] = count;
      count += d - 1;
      ++count;
    }
  }
#ifdef DEBUG
  else {
    Serial.println("Error calculating FFT bins\n");            // Error, something happened
  }
#endif
  return e;
}


float FindE(int bands, int bins) {
  float increment = 0.1, eTest, n;
  int b, count, d;

  for (eTest = 1; eTest < bins; eTest += increment) {     // Find E through brute force calculations
    count = 0;
    for (b = 0; b < bands; b++) {                         // Calculate full log values
      n = pow(eTest, b);
      d = int(n + 0.5);
      count += d;
    }
    if (count > bins) {     // We calculated over our last bin
      eTest -= increment;   // Revert back to previous calculation increment
      increment /= 10.0;    // Get a finer detailed calculation & increment a decimal point lower
    }
    else if (count == bins)   // We found the correct E
      return eTest;           // Return calculated E
    if (increment < 0.0000001)        // Ran out of calculations. Return previous E. Last bin will be lower than (bins-1)
      return (eTest - increment);
  }
  return 0; // Return error 0
}

void initNoise() {
  unsigned long startTime = millis();
  // x = random16();
  // y = random16();
  // z = random16();
  // dist = random16(12345);
#ifdef DEBUG
  unsigned long totalTime = millis() - startTime;
  Serial.print("Noise values set:\t");
  Serial.print(totalTime);
  Serial.println("ms");
#endif
}
