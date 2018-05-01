void READ_FFT_LEFT(float smoothing) {
 static float left_volume  = 0.00;

 if (fft_l.available()) {
   // left_volume = 0;
   for (uint8_t band = 0; band < NUM_BANDS; band++) {
     uint16_t currentBin = fftBins[band];
     uint16_t nextBin = fftBins[band + 1] - 1;
     uint8_t previousAmp = levels_l[band];

     float currentAmp = fft_l.read(currentBin, nextBin) * 255.0;
     levels_l[band]  = previousAmp + (currentAmp - previousAmp) * smoothing;
     #ifdef PRINT_FFT
       Serial.print(levels_l[band]); Serial.print("\t");
       // Serial.print(currentAmp); Serial.print("\t");
     #endif
     currentAmp = constrain(currentAmp, 1.00, 255.0);
     levels_l[band] = map(currentAmp, 1.00, 255.0, 0.00, 255.0);
     // left_volume += levels_l[band];
   }
   #ifdef PRINT_FFT
     Serial.println();
   #endif
   // float left_factor = HALF_POS / left_volume;
   // //uint16_t left_factor_16 = 18000 / left_volume; // was HALF_POS_16
   // for (uint8_t band = 0; band < NUM_BANDS; band++) {
   //   float mapped_left_volume = levels_l[band] * left_factor;
   //   //uint16_t mapped_left_volume_16 = levels_l[band] * left_factor_16;
   //   mapped_left[band] = mapped_left_volume;
   //   //mapped_left_16[band] = mapped_left_volume_16;
   // }
 }
}
