#include "./audio_analyzer.h"

/*======================*/
/*  external variables  */
AudioAnalyzeFFT1024 fftL;
AudioAnalyzeFFT1024 fftR;

uint16_t fftBins[NUM_BANDS];
uint8_t  levelsL[NUM_BANDS];
uint8_t  levelsR[NUM_BANDS];
uint8_t  scaledLevelsL[NUM_BANDS];
uint8_t  scaledLevelsR[NUM_BANDS];

/*======================*/

namespace AudioAnalyzer {
float FindE(int bands, int bins) {
  float increment = 0.1, eTest, n;
  int   b, count, d;

  for (eTest = 1; eTest < bins; eTest += increment) { // Find E through brute
                                                      // force calculations
    count = 0;

    for (b = 0; b < bands; b++) {                     // Calculate full log
                                                      // values
      n      = pow(eTest, b);
      d      = int(n + 0.5);
      count += d;
    }

    if (count > bins) {        // We calculated over our last bin
      eTest     -= increment;  // Revert back to previous calculation increment
      increment /= 10.0;       // Get a finer detailed calculation & increment a
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

float getFFTBins() {
  static float e, n;
  static uint16_t b, bands, bins, count = 0, d;

  bands = NUM_BANDS;                    // Frequency bands; (Adjust to
                                        // desiredvalue)
  bins = MAX_BIN;
  e    = FindE(bands, bins);            // Find calculated E value

#if PRINT_FFT_SETTINGS == true
  Serial.printf("FFT > E: %4.4f\n", e); // Print calculated E value
#endif

  if (e) {                              // If a value was returned continue
    for (b = 0; b < bands; b++) {       // Test and print the bins from the
                                        // calculated
      n = pow(e, b);
      d = int(n + 0.5);
    #if PRINT_FFT_SETTINGS == true
      Serial.printf("%4d ", count); // Print low bin
    #endif
      fftBins[b] = count;
      count     += d - 1;
    #if PRINT_FFT_SETTINGS == true
      Serial.printf("%4d\n", count); // Print high bin
    #endif
      ++count;
    }
  }
#if PRINT_FFT_SETTINGS == true
  else {
    Serial << "Error calculating FFT bins\n"; // Error, something happened
  }
#endif

  return e;
}

void initializeFFT() {
  #if DEBUG == true
  static unsigned long startTime = millis();

  Serial <<
    "\n================== INITIALIZING AUDIO ANALYZER ==================\n";
  #endif
#if PRINT_FFT_SETTINGS == true
  Serial << "FFT > NUM_BANDS:\t" << NUM_BANDS << endl;
  Serial << "FFT > MAX_BIN:\t\t" << MAX_BIN << "hz" << endl;
#endif
  getFFTBins();

#if DEBUG == true
  static unsigned long totalTime = millis() - startTime;

  Serial << "Audio Initialized:\t" << totalTime << "ms" << endl;
  Serial << "-----------------------------------------------------------------\n";
  #endif
}

bool readFFT(float smoothing,
             bool  stereo,
             bool  calculateScaledFFT) {
  static uint16_t currentBin, nextBin;
  static uint8_t  band, previousLeftAmp, previousRightAmp, mappedLeftAmp,
                  mappedRightAmp;
  static float leftVolume, rightVolume, currentLeftAmp, currentRightAmp,
               leftFactor, rightFactor;

  if (stereo) {
  #if WAIT_FOR_FFT_AVAILABILITY == true

    if (fftL.available() && fftR.available()) {
  #endif
    leftVolume = 0.00;

    if (stereo) rightVolume = 0.00;

    for (band = 0; band < NUM_BANDS; band++) {
      currentBin = fftBins[band];
      nextBin    = fftBins[band + 1];

      if (band == NUM_BANDS - 1) {
        nextBin = currentBin;
      }

      previousLeftAmp  = levelsL[band];
      previousRightAmp = levelsR[band];
      currentLeftAmp   = fftL.read(currentBin, nextBin) * 255.0;
      currentRightAmp  = fftR.read(currentBin, nextBin) * 255.0;

      // currentLeftAmp = lerp8by8(previousLeftAmp, currentLeftAmp,
      //                           smoothing);
      currentLeftAmp = previousLeftAmp + (currentLeftAmp - previousLeftAmp)
                       *
                       smoothing;
      currentLeftAmp = constrain(currentLeftAmp, 1, 255.0);
      levelsL[band]  = map(currentLeftAmp, 1, 255, 0, 255.0);

      // higher === smoother!
      // currentRightAmp = lerp8by8(previousRightAmp, currentRightAmp,
      //                            smoothing);

      currentRightAmp = previousRightAmp +
                        (currentRightAmp - previousRightAmp) * smoothing;
      currentRightAmp = constrain(currentRightAmp, 1, 255.0);
      levelsR[band]   = map(currentRightAmp, 1, 255.0, 0, 255.0);

      if (calculateScaledFFT) {
        leftVolume  += levelsL[band];
        rightVolume += levelsR[band];
      }
      #if PRINT_FFT == true
      Serial << levelsL[band] << endl << "\t";
      #endif
    }
    #if PRINT_FFT == true
    Serial << endl;
    #endif

    if (calculateScaledFFT) {
      leftFactor  = CENTER_LED_POS / leftVolume;
      rightFactor = CENTER_LED_POS / rightVolume;

      // uint16_t leftFactor_16 = 18000 / leftVolume; // was
      // CENTER_LED_POS_16

      for (band = 0; band < NUM_BANDS; band++) {
        mappedLeftAmp       = levelsL[band] * leftFactor;
        mappedRightAmp      = levelsR[band] * rightFactor;
        scaledLevelsL[band] = mappedLeftAmp;
        scaledLevelsR[band] = mappedRightAmp;
        #if PRINT_MAPPED_FFT == true
        Serial << scaledLevelsL[band] << "\t";
        #endif
      }
      #if PRINT_MAPPED_FFT == true
      Serial << endl;
      #endif
    }
    return true;

#if WAIT_FOR_FFT_AVAILABILITY == true
  } else {
    return false;
  }
#endif
  }

  else { // if only reading left channel
#if WAIT_FOR_FFT_AVAILABILITY == true

    if (fftL.available()) {
#endif

    for (band = 0; band < NUM_BANDS; band++) {
      currentBin = fftBins[band];
      nextBin    = fftBins[band + 1];

      previousLeftAmp = levelsL[band];

      if (band < NUM_BANDS) {
        currentLeftAmp  = fftL.read(currentBin, nextBin) * 255.0;
      } else {
        currentLeftAmp  = fftL.read(currentBin) * 255.0;
      }

      // currentLeftAmp  = fftL.read(currentBin, nextBin) * 255.0;
      // levelsL[band]  = fftL.read(currentBin, nextBin) * 255.0;

      // currentLeftAmp = lerp8by8(previousLeftAmp, currentLeftAmp,
      // smoothing); // higher === smoother!

      currentLeftAmp = previousLeftAmp + (currentLeftAmp - previousLeftAmp)
                       *
                       smoothing;
      // currentLeftAmp = constrain(currentLeftAmp, 0, 255);
      // currentLeftAmp = map(currentLeftAmp, 0, 255, 0, 255);

      levelsL[band]  = currentLeftAmp;

      leftVolume += levelsL[band];
      #if PRINT_FFT == true
      Serial << levelsL[band] << "\t";
      #endif
    }
    #if PRINT_FFT == true
    Serial << endl;
    #endif

    if (calculateScaledFFT) {
      leftFactor = CENTER_LED_POS / leftVolume;

      // uint16_t leftFactor_16 = 18000 / leftVolume; // was
      // CENTER_LED_POS_16

      for (band = 0; band < NUM_BANDS; band++) {
        mappedLeftAmp       = levelsL[band] * leftFactor;
        scaledLevelsL[band] = mappedLeftAmp;
        #if PRINT_MAPPED_FFT == true
        Serial << scaledLevelsL[band] << "\t";
        #endif
      }
      #if PRINT_MAPPED_FFT == true
      Serial << endl;
      #endif
    }
    return true;

#if WAIT_FOR_FFT_AVAILABILITY == true
  } else {
    return false;
  }
#endif
  }
}

uint8_t averageFFTPortion(uint8_t *array,
                          uint16_t len,
                          uint16_t startIndex,
                          uint16_t endIndex) {
  // ex: uint8_t bass_l = averageFFTPortion(levelsL, NUM_BANDS, 0, 3); // 0
  // = > 2
  static uint16_t sum, portion;

  sum     = 0;
  portion = endIndex - startIndex;

  for (uint16_t i = startIndex; i < endIndex; i++) {
    sum += array[i];
  }
  return sum / portion;
}
}
