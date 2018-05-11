//#include <Arduino.h>
//
//void flexflexstereo() {
//
//  left_pos    = half_pos;
//  left_point  = half_pos;
//  right_pos   = half_pos;
//  right_point = half_pos;
//
//  lowPass_audio = 0.13;
//  filter_min  = 130;
//  spectrumWidth = 32;
//
//  for (int band = 0; band < 7; band++) {
//
//    left_current_brightness = map(left[band], 10, 255, 10, 255);
//    right_current_brightness = map(right[band], 10, 255, 10, 255);
//
//    if (band < 6) {
//      left_next_brightness = map(left[band + 1], 10, 255, 10, 255);
//      right_next_brightness = map(right[band + 1], 10, 255,  10, 255);
//
//    } else {
//      left_next_brightness = left_current_brightness;
//      right_next_brightness = right_current_brightness;
//    }
//
//    current_hue = band * spectrumWidth;
//    next_hue = (band + 1) * spectrumWidth;
//
//    left_point -=  scaledLevelsL[band];
//    right_point += scaledLevelsR[band];
//
//    if (band == 6) (left_point = 0) && (right_point = NUM_LEDS - 1) && (next_hue = band * spectrumWidth) /*&& (left_next_brightness = 0) && (right_next_brightness = 0)*/;
//
//    fill_gradient(leds, left_pos, CHSV(current_hue, 255, left_current_brightness), left_point, CHSV(next_hue, 255, left_next_brightness), SHORTEST_HUES);
//    fill_gradient(leds, right_pos, CHSV(current_hue, 255, right_current_brightness), right_point, CHSV(next_hue, 255, right_next_brightness), SHORTEST_HUES);
//
//    left_pos  = left_point;
//    right_pos = right_point;
//  }
//
//  blur1d(leds, NUM_LEDS, 30);
//  FastLED.show();
//}








//#ifdef stereo_analysis
//void flex_stereo() {
//
//  //changePalette();
//  fadeToBlackBy(leds, NUM_LEDS, 30);
//
//  static float flex_low_pass_stereo = 0.14;
//
//  if (fftL.available() && fftR.available()) {
//
//    //Serial.println("---------------------------------------------------------");
//
//    READ_FFT();
//
//    //fHue = 0;
//
//    left_pos    = half_pos;
//    left_point  = half_pos;
//    right_pos   = half_pos;
//    right_point = half_pos;
//
//    colorIndex = 0;
//
//    for (int band = 0; band < NUM_BANDS; band++) {
//
//      left_point -= scaledLevelsL[band];
//      prev_brightness_left = levelsL[band] * SCALE;
//      //prev_brightness_k_left = levelsL[band + 1] * SCALE;
//
//      right_point += scaledLevelsR[band];
//      prev_brightness_right = levelsR[band] * SCALE;
//      //prev_brightness_k_right = levelsR[band + 1] * SCALE;
//
//      //      if (band == 0) {
//      //        next_hue += HUE_LENGTH;
//      //
//      //        left_current_brightness  = (levelsL[band] + levelsR[band]) * 0.5 * SCALE;
//      //        left_current_brightness  = prev_brightness_left + (left_current_brightness - prev_brightness_left)  * flex_low_pass_stereo;
//      //        levelsL[band] = left_current_brightness;
//      //        right_current_brightness = left_current_brightness;
//      //
//      //        left_next_brightness     = levelsL[band + 1] * SCALE;
//      //        left_next_brightness     = prev_brightness_k_left + (left_next_brightness - prev_brightness_k_left)  * flex_low_pass_stereo;
//      //
//      //        right_current_brightness  = levelsR[band] * SCALE;
//      //        right_current_brightness  = prev_brightness_right + (right_current_brightness - prev_brightness_right)  * flex_low_pass_stereo;
//      //        levelsR[band] = right_current_brightness;
//      //
//      //        right_next_brightness     = levelsR[band + 1] * SCALE;
//      //        right_next_brightness     = prev_brightness_k_right + (right_next_brightness - prev_brightness_k_right)  * flex_low_pass_stereo;
//      //
//      //      }
//
//      //if (/*(band > 0) &&*/ (band < NUM_BANDS - 1)) {
//
//      //next_hue += HUE_LENGTH;
//
//      left_current_brightness  = levelsL[band] * SCALE;
//      left_current_brightness  = prev_brightness_left + (left_current_brightness - prev_brightness_left)  * flex_low_pass_stereo;
//      levelsL[band] = left_current_brightness;
//
//      //      left_next_brightness     = levelsL[band + 1] * SCALE;
//      //      left_next_brightness     = prev_brightness_k_left + (left_next_brightness - prev_brightness_k_left)  * flex_low_pass_stereo;
//
//      right_current_brightness  = levelsR[band] * SCALE;
//      right_current_brightness  = prev_brightness_right + (right_current_brightness - prev_brightness_right)  * flex_low_pass_stereo;
//      levelsR[band] = right_current_brightness;
//
//      if (band == 0) {
//        left_current_brightness = (left_current_brightness + right_current_brightness) * 0.5;
//        right_current_brightness = left_current_brightness;
//      }
//
//      //      right_next_brightness     = levelsR[band + 1] * SCALE;
//      //      right_next_brightness     = prev_brightness_k_right + (right_next_brightness - prev_brightness_k_right)  * flex_low_pass_stereo;
//
//      //}
//
//      //      else {
//      //
//      //        //next_hue = current_hue;
//      //
//      //        left_current_brightness  = left_next_brightness;
//      //        //left_current_brightness  = prev_brightness_left + (left_current_brightness - prev_brightness_left)  * flex_low_pass_stereo;
//      //
//      //        right_current_brightness  = right_next_brightness;
//      //        //right_current_brightness  = prev_brightness_right + (right_current_brightness - prev_brightness_right)  * flex_low_pass_stereo;
//      //
//      //        left_next_brightness = 0;
//      //        right_next_brightness = 0;
//      //
//      //        left_point = 0;
//      //        right_point = NUM_LEDS - 1;
//      //      }
//
//
//      if (band == NUM_BANDS - 1) { // prevent from drawing outside of strip dimensions
//        left_point = 0;
//        right_point = NUM_LEDS - 1;
//      }
//
//      for (uint8_t i = left_pos; i > left_point; i--) {
//        colorIndex = i * PALETTE_INDEX_INCREMENT;
//        leds[i] += ColorFromPalette( gCurrentPalette, colorIndex, left_current_brightness, LINEARBLEND);
//      }
//      for (uint8_t i = right_pos; i < right_point; i++) {
//        colorIndex = i * PALETTE_INDEX_INCREMENT;
//        leds[i] += ColorFromPalette( gCurrentPalette, colorIndex, right_current_brightness, LINEARBLEND);
//      }
//
//      left_pos  = left_point;
//      right_pos = right_point;
//      //current_hue = next_hue;
//      //INDEX += HUE_LENGTH;
//
//    }
//
//    //blur1d(leds, NUM_LEDS, 100);
//
//  }
//
//  display_encoder_fft_average();
//
//}
//#endif
//
