// #ifdef stereo_analysis
// void radiate_stereo() {
//
//   changePalette();
//
//   READ_FFT_STEREO(0.18);
//
//   leds[half_pos].nscale8(170);
//   leds[half_pos + 1].nscale8(170);
//
//   uint8_t bass_l = fftL.read(1, 2);
//   uint8_t mids_l = fftL.read(30, 200);
//   uint8_t high_l = fftL.read(250, MAX_BIN);
//
//   uint8_t bass_r = fftR.read(1, 2);
//   uint8_t mids_r = fftR.read(30, 200);
//   uint8_t high_r = fftR.read(250, MAX_BIN);
//
//   //  if (bass_l < 8) {
//   //    bass_l = 0;
//   //  }
//   //  if (mids_l < 8) {
//   //    mids_l = 0;
//   //  }
//   //  if (high_l < 8) {
//   //    high_l = 0;
//   //  }
//   //
//   //  if (bass_r < 8) {
//   //    bass_r = 0;
//   //  }
//   //  if (mids_r < 8) {
//   //    mids_r = 0;
//   //  }
//   //  if (high_r < 8) {
//   //    high_r = 0;
//   //  }
//
//   //    uint16_t left_fft_average  = (bass_l + mids_l + high_l) / 3;
//   //    uint16_t right_fft_average = (bass_r + mids_r + high_r) / 3;
//
//   //    leds[half_pos + 1] += ColorFromPalette12(gCurrentPalette, left_fft_average, left_fft_average, LINEARBLEND);
//   //    leds[half_pos] += ColorFromPalette12(gCurrentPalette, right_fft_average, right_fft_average, LINEARBLEND);
//   leds[half_pos + 1] += CRGB(bass_l, mids_l, high_l);
//   leds[half_pos] += CRGB(bass_r, mids_r, high_r);
//
//   //    leds[half_pos].maximizeBrightness();
//   //    leds[half_pos + 1].maximizeBrightness();
//
//   EVERY_N_MILLISECONDS(10) {
//     for (int i = NUM_LEDS - 1; i > half_pos; i--) {
//       leds[i].blue = leds[i - 1].blue;
//     }
//     for (int i = 0; i < half_pos + 1; i++) {
//       leds[i].blue = leds[i + 1].blue;
//     }
//   }
//
//   EVERY_N_MILLISECONDS(27) {
//     for (int i = NUM_LEDS - 1; i > half_pos; i--) {
//       leds[i].green = leds[i - 1].green;
//     }
//     for (int i = 0; i < half_pos + 1; i++) {
//       leds[i].green = leds[i + 1].green;
//     }
//   }
//
//   EVERY_N_MILLISECONDS(40) {
//     for (int i = NUM_LEDS - 1; i > half_pos; i--) {
//       leds[i].red = leds[i - 1].red;
//     }
//     for (int i = 0; i < half_pos + 1; i++) {
//       leds[i].red = leds[i + 1].red;
//     }
//   }
//
//   //blur1d(leds, NUM_LEDS, 13);
//   //showAnalogRGB(leds[half_pos]);
//
// }
// #endif
// //#else
// //void radiate_left() {
// //
// //  changePalette();
// //
// //  readFFTLeft(0.18);
// //
// //  leds[half_pos].nscale8(170);
// //  leds[half_pos + 1].nscale8(170);
// //
// //  uint8_t bass_l = fftL.read(1, 2);
// //  uint8_t mids_l = fftL.read(30, 200);
// //  uint8_t high_l = fftL.read(250, MAX_BIN);
// //
// //  //  if (bass_l < 8) {
// //  //    bass_l = 0;
// //  //  }
// //  //  if (mids_l < 8) {
// //  //    mids_l = 0;
// //  //  }
// //  //  if (high_l < 8) {
// //  //    high_l = 0;
// //  //  }
// //  //
// //  //  if (bass_r < 8) {
// //  //    bass_r = 0;
// //  //  }
// //  //  if (mids_r < 8) {
// //  //    mids_r = 0;
// //  //  }
// //  //  if (high_r < 8) {
// //  //    high_r = 0;
// //  //  }
// //
// //  //    uint16_t left_fft_average  = (bass_l + mids_l + high_l) / 3;
// //  //    uint16_t right_fft_average = (bass_r + mids_r + high_r) / 3;
// //
// //  //    leds[half_pos + 1] += ColorFromPalette12(gCurrentPalette, left_fft_average, left_fft_average, LINEARBLEND);
// //  //    leds[half_pos] += ColorFromPalette12(gCurrentPalette, right_fft_average, right_fft_average, LINEARBLEND);
// //  //leds[half_pos + 1] += CRGB(bass_l, mids_l, high_l);
// //  leds[half_pos] += CRGB(bass_l, mids_l, high_l);
// //
// //  //    leds[half_pos].maximizeBrightness();
// //  //    leds[half_pos + 1].maximizeBrightness();
// //
// //  EVERY_N_MILLISECONDS(10) {
// //    for (int i = NUM_LEDS - 1; i > half_pos; i--) {
// //      leds[i].blue = leds[i - 1].blue;
// //    }
// //    for (int i = 0; i < half_pos + 1; i++) {
// //      leds[i].blue = leds[i + 1].blue;
// //    }
// //  }
// //
// //  EVERY_N_MILLISECONDS(27) {
// //    for (int i = NUM_LEDS - 1; i > half_pos; i--) {
// //      leds[i].green = leds[i - 1].green;
// //    }
// //    for (int i = 0; i < half_pos + 1; i++) {
// //      leds[i].green = leds[i + 1].green;
// //    }
// //  }
// //
// //  EVERY_N_MILLISECONDS(40) {
// //    for (int i = NUM_LEDS - 1; i > half_pos; i--) {
// //      leds[i].red = leds[i - 1].red;
// //    }
// //    for (int i = 0; i < half_pos + 1; i++) {
// //      leds[i].red = leds[i + 1].red;
// //    }
// //  }
// //
// //  //blur1d(leds, NUM_LEDS, 13);
// //  //showAnalogRGB(leds[half_pos]);
// //
// //}
// //#endif
//
