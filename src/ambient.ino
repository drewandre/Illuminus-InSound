// uint16_t scale_twelve = 400;
//
// void ambient() {
//
//   changePalette();
//   //gCurrentPalette = gGradientPalettes[0];
//
//   // 1, 3, 5, 10, 12,
//   // try BROWN
//   Serial.println(gCurrentPaletteNumber);
//
//   for (int i = 11; i < NUM_LEDS - 14; i++) {
//
//     dataTwelve = inoise16(x + (i * scale_twelve), y + (dist + scale_twelve), z) % 4095;
//     dataTwelve = constrain(dataTwelve, 0, 4095);
//
//     leds[i] = ColorFromPalette12( gCurrentPalette, dataTwelve, 255, LINEARBLEND);
//
//   }
//
//   z += 13;
//   y += 15;
//   //Serial.println(z);
//
//   blur1d(leds, NUM_LEDS, 150);
//   //showAnalogRGB(leds[half_pos]);
// }
//
