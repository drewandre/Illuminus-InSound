void DISPLAY_LEDS() {
  //FastLED.setBrightness(255);
  FastLED.show();

#ifdef PRINT_LED_FRAMERATE
  Serial.print("LED framerate: ");
  Serial.print(LEDS.getFPS());
  Serial.print("/second");
  Serial.println();
#endif
}

void setPartialPixel(uint16_t pos, CRGB & color) {
  CRGB c1(color), c2(color);
  uint8_t frac = pos & 0xFF;
  uint8_t idx = pos >> 8;
  c1.nscale8(255 - frac);
  c2.nscale8(frac);
  leds[idx] = c1;
  leds[idx + 1] = c2;
}

void showAnalogRGB( const CRGB& rgb)
{
//  analogWrite(REDPIN,   255 - rgb.r );
//  analogWrite(GREENPIN, 255 - rgb.g );
//  analogWrite(BLUEPIN,  255 - rgb.b );
}

void display_encoder_fft_average() {
//  uint8_t bass_l = averageFFTPortion(levels_l, NUM_BANDS, 0, 3); // 0 => 2
//  uint8_t mids_l = averageFFTPortion(levels_l, NUM_BANDS, 13, 25); // 30 => 60
//  uint8_t high_l = averageFFTPortion(levels_l, NUM_BANDS, 29, 35); // 255 => MAX_BIN
//  showAnalogRGB(CRGB(bass_l, mids_l, high_l));
}
