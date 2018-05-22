#include "./audio_analyzer.h"

/*======================*/
/*  external variables  */
struct AudioAnalyzeFFT1024 fftL;
struct AudioAnalyzeFFT1024 fftR;

/*======================*/

bool readFFT(float smoothing,
             bool  stereo,
             bool  calculateScaledFFT) {
  static uint16_t currentBin, nextBin;
  static uint8_t  band, previousLeftAmp, previousRightAmp, mappedLeftAmp,
                  mappedRightAmp;
  static float leftVolume, rightVolume, currentLeftAmp, currentRightAmp,
               leftFactor, rightFactor;

  if (stereo) {
  #ifdef WAIT_FOR_FFT_AVAILABILITY

    if (fftL.available() && fftR.available()) {
  #endif // ifdef WAIT_FOR_FFT_AVAILABILITY
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
      #ifdef PRINT_FFT
      Serial << levelsL[band] << endl << "\t";
      #endif // ifdef PRINT_FFT
    }
    #ifdef PRINT_FFT
    Serial << endl;
    #endif // ifdef PRINT_FFT

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
        #ifdef PRINT_MAPPED_FFT
        Serial << scaledLevelsL[band] << "\t";
        #endif // ifdef PRINT_MAPPED_FFT
      }
      #ifdef PRINT_MAPPED_FFT
      Serial << endl;
      #endif // ifdef PRINT_MAPPED_FFT
    }
    return true;

#ifdef WAIT_FOR_FFT_AVAILABILITY
  } else {
    return false;
  }
#endif // ifdef WAIT_FOR_FFT_AVAILABILITY
  }

  else { // if only reading left channel
#ifdef WAIT_FOR_FFT_AVAILABILITY

    if (fftL.available()) {
#endif // ifdef WAIT_FOR_FFT_AVAILABILITY

    for (band = 0; band < NUM_BANDS; band++) {
      currentBin = fftBins[band];
      nextBin    = fftBins[band + 1];

      if (band == NUM_BANDS - 1) nextBin = currentBin;

      previousLeftAmp = levelsL[band];
      currentLeftAmp  = fftL.read(currentBin, nextBin) * 255.0;

      // currentLeftAmp = lerp8by8(previousLeftAmp, currentLeftAmp,
      // smoothing); // higher === smoother!
      currentLeftAmp = previousLeftAmp + (currentLeftAmp - previousLeftAmp)
                       *
                       smoothing;
      currentLeftAmp = constrain(currentLeftAmp, 1, 255);
      levelsL[band]  = map(currentLeftAmp, 1, 255, 0, 255);

      leftVolume += levelsL[band];
      #ifdef PRINT_FFT
      Serial << levelsL[band] << "\t";
      #endif // ifdef PRINT_FFT
    }
    #ifdef PRINT_FFT
    Serial << endl;
    #endif // ifdef PRINT_FFT

    if (calculateScaledFFT) {
      leftFactor = CENTER_LED_POS / leftVolume;

      // uint16_t leftFactor_16 = 18000 / leftVolume; // was
      // CENTER_LED_POS_16

      for (band = 0; band < NUM_BANDS; band++) {
        mappedLeftAmp       = levelsL[band] * leftFactor;
        scaledLevelsL[band] = mappedLeftAmp;
        #ifdef PRINT_MAPPED_FFT
        Serial << scaledLevelsL[band] << "\t";
        #endif // ifdef PRINT_MAPPED_FFT
      }
      #ifdef PRINT_MAPPED_FFT
      Serial << endl;
      #endif // ifdef PRINT_MAPPED_FFT
    }
    return true;

#ifdef WAIT_FOR_FFT_AVAILABILITY
  } else {
    return false;
  }
#endif // ifdef WAIT_FOR_FFT_AVAILABILITY
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
