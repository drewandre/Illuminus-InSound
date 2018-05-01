//void radiate_left() {
//
//  READ_FFT_LEFT(0.30);
//
//  leds[half_pos].nscale8(200);
//
//  uint8_t bass_l = averageFFTPortion(levels_l, NUM_BANDS, 0, 3); // 0 => 2
//  uint8_t mids_l = averageFFTPortion(levels_l, NUM_BANDS, 13, 25); // 30 => 60
//  uint8_t high_l = averageFFTPortion(levels_l, NUM_BANDS, 29, 35); // 255 => MAX_BIN
//
//  leds[half_pos].r += bass_l;
//  leds[half_pos].g += mids_l;
//  leds[half_pos].b += high_l;
//
//  EVERY_N_MILLISECONDS(10) {
//    for (int i = NUM_LEDS - 1; i > half_pos; i--) {
//      leds[i].blue = leds[i - 1].blue;
//    }
//    for (int i = 0; i < half_pos + 1; i++) {
//      leds[i].blue = leds[i + 1].blue;
//    }
//  }
//
//  EVERY_N_MILLISECONDS(27) {
//    for (int i = NUM_LEDS - 1; i > half_pos; i--) {
//      leds[i].green = leds[i - 1].green;
//    }
//    for (int i = 0; i < half_pos + 1; i++) {
//      leds[i].green = leds[i + 1].green;
//    }
//  }
//
//  EVERY_N_MILLISECONDS(40) {
//    for (int i = NUM_LEDS - 1; i > half_pos; i--) {
//      leds[i].red = leds[i - 1].red;
//    }
//    for (int i = 0; i < half_pos + 1; i++) {
//      leds[i].red = leds[i + 1].red;
//    }
//  }
//
//  blur1d(leds, NUM_LEDS, 13);
//
//}
