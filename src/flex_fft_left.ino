//void flex_fftLeft() {
//
//  // 172 fps
//
//  uint16_t left_pos    = half_pos;
//  uint16_t left_point  = half_pos;
//  uint16_t right_pos   = half_pos;
//  uint16_t right_point = half_pos;
//
//  uint8_t current_hue = 0;
//  //uint8_t next_hue = 0;
//
//  readFFTLeft(0.18);
//
//  nscale8(leds, NUM_LEDS, 230);
//
//  for (int band = 0; band < NUM_BANDS; band++) {
//
//    uint8_t currentBrightness = levelsL[band];
//
//    left_point -= scaledLevelsL[band];
//    right_point += scaledLevelsL[band];
//
//    //    if (band < NUM_BANDS - 1) {
//    current_hue += HUE_LENGTH;
//    //    }
//
//    //    else {
//    //      current_hue = next_hue;
//    //      //next_hue = current_hue;
//    //      //left_next_brightness = 0;
//    //      //right_next_brightness = 0;
//    //      left_point = 0;
//    //      right_point = NUM_LEDS - 1;
//    //    }
//
//    for (uint8_t i = left_pos; i > left_point; i--) {
//      leds[i] += CHSV(current_hue, 255, currentBrightness);
//    }
//    for (uint8_t i = right_pos; i < right_point; i++) {
//      leds[i] += CHSV(current_hue, 255, currentBrightness);
//    }
//
//    // fun-ish times with 16 bit math
//    //    for (uint16_t p = left_pos; p > left_point; p--) {
//    //      CRGB color = CHSV(current_hue, 255, currentBrightness);
//    //      setPartialPixel(p, color);
//    //    }
//    //    for (uint16_t p = right_pos; p < right_point; p++) {
//    //      CRGB color = CHSV(current_hue, 255, currentBrightness);
//    //      setPartialPixel(p, color);
//    //    }
//
//    left_pos = left_point;
//    right_pos = right_point;
//
//  }
//  //FastLED.show();
//
//}
