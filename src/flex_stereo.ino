//void flex_fft_stereo() {
//
//  // 172 fps
//
//  uint16_t left_pos    = half_pos;
//  uint16_t left_point  = half_pos;
//  uint16_t right_pos   = half_pos;
//  uint16_t right_point = half_pos;
//
//  uint8_t current_hue = 0;
//
//  READ_FFT_STEREO(0.18);
//
//  nscale8(leds, NUM_LEDS, 230);
//
//  for (int band = 0; band < NUM_BANDS; band++) {
//
//    uint8_t currentLeftAmp = levels_l[band];
//    uint8_t currentRightAmp = levels_r[band];
//
//    left_point -= mapped_left[band];
//    right_point += mapped_right[band];
//
//    current_hue += hue_length;
//
//    for (uint8_t i = left_pos; i > left_point; i--) {
//      leds[i] += CHSV(current_hue, 255, currentLeftAmp);
//    }
//    for (uint8_t i = right_pos; i < right_point; i++) {
//      leds[i] += CHSV(current_hue, 255, currentRightAmp);
//    }
//
//    left_pos = left_point;
//    right_pos = right_point;
//
//  }
//
//  blur1d(leds, NUM_LEDS, 10);
//
//}

