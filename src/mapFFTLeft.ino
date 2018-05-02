void mapFFTLeft() {
  static uint8_t band, currentBrightness;
  static uint16_t i, pos, point;
  static float fHue;

 // nscale8(leds, NUM_LEDS, 220);
 //fadeToBlackBy(leds,NUM_LEDS,9);
 readFFTLeft(1);

 pos = 0;
 point = 0;
 fHue = 0;

 for (band = 0; band < NUM_BANDS - 1; band++) {
   point += segmentLength;
   if (band == NUM_BANDS - 1) {
     point = NUM_LEDS - 1;
   }
   currentBrightness = levelsL[band];

   for (i = pos; i < point; i++) {
     leds[i] += CHSV(fHue, 255, currentBrightness);
     fHue = i * 1.65;
   }
   pos = point;
 }

 blur1d(leds, NUM_LEDS, 1);
 displayLEDs();
}


//void raw_audio_data() {
//
//  nscale8(leds, NUM_LEDS, 230);
//  //fadeToBlackBy(leds,NUM_LEDS,30);
//
//  READ_FFT();
//
//  pos = 0;
//  point = 0;
//  current_hue = 0;
//  next_hue = 0;
//
//  //hue = 0;
//
//  for (band = 0; band < NUM_BANDS; band++) {
//
//    point += segmentLength;
//    next_hue += (255 / NUM_BANDS);
//
//    currentBrightness = levelsL[band];
//    next_brightness = levelsL[band + 1];
//
//    if (band == NUM_BANDS - 1) {
//      point = NUM_LEDS - 2;
//      next_brightness = currentBrightness;
//    }
//
//    for (uint16_t i = pos; i < point; i++) {
//      fill_gradient(temp_hues, pos, CHSV(current_hue, 255, currentBrightness), point, CHSV(next_hue, 255, next_brightness),SHORTEST_HUES);
//      leds[i] += temp_hues[i];
//    }
//
//    current_hue = next_hue;
//    pos = point - overlap;
//
//
//
//  }
//
//}


//void display_fftLeft_old() {
//
//  changePalette();
//
//  nscale8(leds, NUM_LEDS, 230); // stereo_peak
//
//  READ_FFT();
//
//  //fractionalPso
//  pos = 0;
//  point = 0;
//
//  colorIndex = 0;
//
//  for (band = 0; band < NUM_BANDS; band++) {
//
//    point += segmentLength;
//
//    //colorIndex = PALETTE_INDEX_INCREMENT_per_band * float(band);
//
//    if (band < NUM_BANDS - 1) {
//
//      prev_brightness_left = levelsL[band];
//      prev_brightness_k_left = levelsL[band + 1];
//
//      currentBrightness = levelsL[band];
//
//      currentBrightness  = prev_brightness_left + (currentBrightness - prev_brightness_left)  * 0.14;
//      levelsL[band] = currentBrightness;
//      currentBrightness *= SCALE;
//    }
//
//    else {
//      currentBrightness = nxt_brightness;
//      prev_brightness_k_left = levelsL[band];
//      point = NUM_LEDS - 1;
//    }
//
////    Serial.print("band:\t");
////    Serial.print(band);
////    Serial.print("\tpoint:\t");
////    Serial.print(point);
////    Serial.println();
//
//#ifdef print_fft
//    Serial.print(currentBrightness);
//    Serial.print("\t");
//#endif
//
//    for (uint16_t i = pos; i < point; i++) {
//      //colorIndex_twelve = i * PALETTE_INDEX_INCREMENT_twelve;
//      //leds[i] += ColorFromPalette12( gCurrentPalette, colorIndex_twelve, currentBrightness, LINEARBLEND);
//      colorIndex = i * PALETTE_INDEX_INCREMENT;
//      leds[i] += CHSV(colorIndex, 255, currentBrightness);
//      //Serial.println(i);
//    }
//
//    pos = point;
//    //colorIndex = NEXT_INDEX;
//
//  }
//
//#ifdef print_fft
//  Serial.println();
//#endif
//
//  //display_encoder_fft_average();
//  //blur1d(leds, NUM_LEDS, 50);
//
//}
