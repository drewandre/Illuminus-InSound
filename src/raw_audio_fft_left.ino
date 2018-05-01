//void raw_audio_fft_left() {
//
//  READ_FFT_LEFT(1);
//
//  uint16_t pos = 0;
//  uint16_t point = 0;
//
//  hue = 0;
//
//  for (uint8_t band = 0; band < NUM_BANDS - 1; band++) {
//    hue = band * hue_length;
//    point += segment_length;
//    if (band == NUM_BANDS - 1) {
//      point = NUM_LEDS - 1;
//    }
//
//    uint8_t curr_brightness = levels_l[band];
//
//    for (uint16_t i = pos; i < point; i++) {
//      leds[i] = CHSV(hue, 255, curr_brightness);
//    }
//    pos = point;
//  }
//
//  //blur1d(leds,NUM_LEDS,10);
//}
