// void map_fft_left() {
//
//  nscale8(leds, NUM_LEDS, 220);
//  //fadeToBlackBy(leds,NUM_LEDS,9);
//
//  READ_FFT_LEFT(0.20);
//
//  uint16_t pos = 0;
//  uint16_t point = 0;
//
//  float fhue = 0;
//
//  for (uint8_t band = 0; band < NUM_BANDS - 1; band++) {
//
//    point += segment_length;
//    if (band == NUM_BANDS - 1) {
//      point = NUM_LEDS - 1;
//    }
//
//    uint8_t curr_brightness = levels_l[band];
//
//    for (uint16_t i = pos; i < point; i++) {
//      leds[i] += CHSV(fhue, 255, curr_brightness);
//      fhue = i * 1.65;
//    }
//    pos = point;
//  }
//
//  blur1d(leds, NUM_LEDS, 10);
// }
//
//
////void raw_audio_data() {
////
////  nscale8(leds, NUM_LEDS, 230);
////  //fadeToBlackBy(leds,NUM_LEDS,30);
////
////  READ_FFT();
////
////  pos = 0;
////  point = 0;
////  current_hue = 0;
////  next_hue = 0;
////
////  //hue = 0;
////
////  for (band = 0; band < NUM_BANDS; band++) {
////
////    point += segment_length;
////    next_hue += (255 / NUM_BANDS);
////
////    curr_brightness = levels_l[band];
////    next_brightness = levels_l[band + 1];
////
////    if (band == NUM_BANDS - 1) {
////      point = NUM_LEDS - 2;
////      next_brightness = curr_brightness;
////    }
////
////    for (uint16_t i = pos; i < point; i++) {
////      fill_gradient(temp_hues, pos, CHSV(current_hue, 255, curr_brightness), point, CHSV(next_hue, 255, next_brightness),SHORTEST_HUES);
////      leds[i] += temp_hues[i];
////    }
////
////    current_hue = next_hue;
////    pos = point - overlap;
////
////
////
////  }
////
////}
//
//
////void display_fft_left_old() {
////
////  changePalette();
////
////  nscale8(leds, NUM_LEDS, 230); // stereo_peak
////
////  READ_FFT();
////
////  //fractionalPso
////  pos = 0;
////  point = 0;
////
////  colorIndex = 0;
////
////  for (band = 0; band < NUM_BANDS; band++) {
////
////    point += segment_length;
////
////    //colorIndex = palette_index_increment_per_band * float(band);
////
////    if (band < NUM_BANDS - 1) {
////
////      prev_brightness_left = levels_l[band];
////      prev_brightness_k_left = levels_l[band + 1];
////
////      curr_brightness = levels_l[band];
////
////      curr_brightness  = prev_brightness_left + (curr_brightness - prev_brightness_left)  * 0.14;
////      levels_l[band] = curr_brightness;
////      curr_brightness *= SCALE;
////    }
////
////    else {
////      curr_brightness = nxt_brightness;
////      prev_brightness_k_left = levels_l[band];
////      point = NUM_LEDS - 1;
////    }
////
//////    Serial.print("band:\t");
//////    Serial.print(band);
//////    Serial.print("\tpoint:\t");
//////    Serial.print(point);
//////    Serial.println();
////
////#ifdef print_fft
////    Serial.print(curr_brightness);
////    Serial.print("\t");
////#endif
////
////    for (uint16_t i = pos; i < point; i++) {
////      //colorIndex_twelve = i * palette_index_increment_twelve;
////      //leds[i] += ColorFromPalette12( gCurrentPalette, colorIndex_twelve, curr_brightness, LINEARBLEND);
////      colorIndex = i * palette_index_increment;
////      leds[i] += CHSV(colorIndex, 255, curr_brightness);
////      //Serial.println(i);
////    }
////
////    pos = point;
////    //colorIndex = NEXT_INDEX;
////
////  }
////
////#ifdef print_fft
////  Serial.println();
////#endif
////
////  //display_encoder_fft_average();
////  //blur1d(leds, NUM_LEDS, 50);
////
////}
