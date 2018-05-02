void readFFTLeft(float smoothing) {
 static float leftVolume, currentAmp, leftFactor, scaledVolumeL;
 static uint16_t currentBin, nextBin;
 static uint8_t band, previousAmp;

 if (fftL.available()) {
   if (calculateScaledFFT)
     leftVolume = 0.00;

   for (band = 0; band < NUM_BANDS; band++) {
     currentBin = fftBins[band];
     nextBin = fftBins[band + 1];
     if (band == NUM_BANDS - 1) {
       nextBin = currentBin;
     }

     previousAmp = levelsL[band];
     currentAmp = fftL.read(currentBin, nextBin) * 255.0;
     levelsL[band]  = previousAmp + (currentAmp - previousAmp) * smoothing;
     currentAmp = constrain(currentAmp, 1.00, 30.0);
     levelsL[band] = map(currentAmp, 1.00, 30.0, 0.00, 255.0);

     if (calculateScaledFFT)
       leftVolume += levelsL[band];

     #ifdef PRINT_FFT
       Serial.print(levelsL[band]); Serial.print("\t");
     #endif
   }
   #ifdef PRINT_FFT
     Serial.println();
   #endif
   if (calculateScaledFFT) {
     leftFactor = HALF_POS / leftVolume;
     //uint16_t leftFactor_16 = 18000 / leftVolume; // was HALF_POS_16
     for (band = 0; band < NUM_BANDS; band++) {
       scaledVolumeL = levelsL[band] * leftFactor;
       //uint16_t scaledLevelsL_16 = levelsL[band] * leftFactor_16;
       scaledLevelsL[band] = scaledVolumeL;
       //scaledLevelsL_16[band] = scaledLevelsL_16;
     }
   } // end calculateScaledFFT
 } // end fft.available()
}
