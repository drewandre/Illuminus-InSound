//void raw_audio_fftLeft() {
//
//  readFFTLeft(1);
//
//  uint16_t pos = 0;
//  uint16_t point = 0;
//
//  hue = 0;
//
//  for (uint8_t band = 0; band < NUM_BANDS - 1; band++) {
//    hue = band * HUE_LENGTH;
//    point += segmentLength;
//    if (band == NUM_BANDS - 1) {
//      point = NUM_LEDS - 1;
//    }
//
//    uint8_t currentBrightness = levelsL[band];
//
//    for (uint16_t i = pos; i < point; i++) {
//      leds[i] = CHSV(hue, 255, currentBrightness);
//    }
//    pos = point;
//  }
//
//  //blur1d(leds,NUM_LEDS,10);
//}
