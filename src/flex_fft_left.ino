//void flex_fft_left() {
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
//  READ_FFT_LEFT(0.18);
//
//  nscale8(leds, NUM_LEDS, 230);
//
//  for (int band = 0; band < NUM_BANDS; band++) {
//
//    uint8_t curr_brightness = levels_l[band];
//
//    left_point -= mapped_left[band];
//    right_point += mapped_left[band];
//
//    //    if (band < NUM_BANDS - 1) {
//    current_hue += hue_length;
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
//      leds[i] += CHSV(current_hue, 255, curr_brightness);
//    }
//    for (uint8_t i = right_pos; i < right_point; i++) {
//      leds[i] += CHSV(current_hue, 255, curr_brightness);
//    }
//
//    // fun-ish times with 16 bit math
//    //    for (uint16_t p = left_pos; p > left_point; p--) {
//    //      CRGB color = CHSV(current_hue, 255, curr_brightness);
//    //      setPartialPixel(p, color);
//    //    }
//    //    for (uint16_t p = right_pos; p < right_point; p++) {
//    //      CRGB color = CHSV(current_hue, 255, curr_brightness);
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

