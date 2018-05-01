// void splatter() {
//
//   changePalette();
//
//   EVERY_N_MILLISECONDS(15) {
//     fadeToBlackBy(leds, NUM_LEDS, 1);
//     //    nscale8(leds, NUM_LEDS, 255);
//   }
//
//   blur1d(leds, NUM_LEDS, 100);
//
//   EVERY_N_MILLIS_I( drum_timer, 500 ) {
//     uint8_t INDEX = random8(0, 255);
//     drum_timer.setPeriod( random16( 200, 500) );
//     //pos = sin(x);
//     uint16_t position = random8(NUM_LEDS - 1);
//     uint8_t width = random8(2, 15);
//     uint16_t left_pos  = position - width;
//     uint16_t right_pos = position + width;
//     if (left_pos < 0) {
//       left_pos = 0;
//     }
//     if (right_pos > NUM_LEDS - 1) {
//       right_pos = NUM_LEDS - 1;
//     }
//     for (int i = left_pos; i <= right_pos; i++) {
//       leds[i] += ColorFromPalette(gCurrentPalette, INDEX, 255, LINEARBLEND);
//     }
//
//   }
//
// }
//
