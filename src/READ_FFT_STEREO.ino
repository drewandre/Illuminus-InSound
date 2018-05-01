//void READ_FFT_STEREO(float smoothing) {
//
//  float left_volume  = 0.00;
//  float right_volume  = 0.00;
//
//  if (fft_l.available() && fft_r.available()) {
//
//    for (uint8_t band = 0; band < NUM_BANDS; band++) {
//
//      uint16_t currentBin = fftBins[band];
//      uint16_t nextBin = fftBins[band + 1] - 1;
//
//      uint8_t previousLeftAmp = levels_l[band];
//      uint8_t previousRightAmp = levels_r[band];
//
//      float currentLeftAmp = fft_l.read(currentBin, nextBin) * 255.0;
//      float currentRightAmp = fft_r.read(currentBin, nextBin) * 255.0;
//
//      //currentLeftAmp = lerp8by8(previousLeftAmp, currentLeftAmp, smoothing); // higher === smoother!
//      levels_l[band]  = previousLeftAmp + (currentLeftAmp - previousLeftAmp)  * smoothing;
//      //      currentLeftAmp = constrain(currentLeftAmp, 10, 255);
//      //      levels_l[band] = map(currentLeftAmp, 10, 255, 0, 255);
//
//      //currentRightAmp = lerp8by8(previousRightAmp, currentRightAmp, smoothing); // higher === smoother!
//      levels_r[band]  = previousRightAmp + (currentRightAmp - previousRightAmp)  * smoothing;
//      //      currentRightAmp = constrain(currentRightAmp, 10, 255);
//      //      levels_r[band] = map(currentRightAmp, 10, 255, 0, 255);
//
//      left_volume += levels_l[band];
//      right_volume += levels_r[band];
//
//    }
//    float left_factor = half_pos / left_volume;
//    float right_factor = half_pos / right_volume;
//    //uint16_t left_factor_16 = 18000 / left_volume; // was HALF_POS_16
//
//    for (uint8_t band = 0; band < NUM_BANDS; band++) {
//      uint8_t mappedLeftAmp = levels_l[band] * left_factor;
//      uint8_t mappedRightAmp = levels_r[band] * right_factor;
//      mapped_left[band] = mappedLeftAmp;
//      mapped_right[band] = mappedRightAmp;
//    }
//
//  }
//
//}
