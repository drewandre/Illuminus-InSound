//void READ_FFT_STEREO(float smoothing) {
//
//  float leftVolume  = 0.00;
//  float right_volume  = 0.00;
//
//  if (fftL.available() && fft_r.available()) {
//
//    for (uint8_t band = 0; band < NUM_BANDS; band++) {
//
//      uint16_t currentBin = fftBins[band];
//      uint16_t nextBin = fftBins[band + 1] - 1;
//
//      uint8_t previousLeftAmp = levelsL[band];
//      uint8_t previousRightAmp = levelsR[band];
//
//      float currentLeftAmp = fftL.read(currentBin, nextBin) * 255.0;
//      float currentRightAmp = fft_r.read(currentBin, nextBin) * 255.0;
//
//      //currentLeftAmp = lerp8by8(previousLeftAmp, currentLeftAmp, smoothing); // higher === smoother!
//      levelsL[band]  = previousLeftAmp + (currentLeftAmp - previousLeftAmp)  * smoothing;
//      //      currentLeftAmp = constrain(currentLeftAmp, 10, 255);
//      //      levelsL[band] = map(currentLeftAmp, 10, 255, 0, 255);
//
//      //currentRightAmp = lerp8by8(previousRightAmp, currentRightAmp, smoothing); // higher === smoother!
//      levelsR[band]  = previousRightAmp + (currentRightAmp - previousRightAmp)  * smoothing;
//      //      currentRightAmp = constrain(currentRightAmp, 10, 255);
//      //      levelsR[band] = map(currentRightAmp, 10, 255, 0, 255);
//
//      leftVolume += levelsL[band];
//      right_volume += levelsR[band];
//
//    }
//    float leftFactor = half_pos / leftVolume;
//    float right_factor = half_pos / right_volume;
//    //uint16_t leftFactor_16 = 18000 / leftVolume; // was HALF_POS_16
//
//    for (uint8_t band = 0; band < NUM_BANDS; band++) {
//      uint8_t mappedLeftAmp = levelsL[band] * leftFactor;
//      uint8_t mappedRightAmp = levelsR[band] * right_factor;
//      scaledLevelsL[band] = mappedLeftAmp;
//      scaledLevelsR[band] = mappedRightAmp;
//    }
//
//  }
//
//}
