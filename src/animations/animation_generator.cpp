#include "../leds/led_manager.h"
#include "../audio/audio_analyzer.h"

#include <env.h>

struct CRGB leds[NUM_LEDS];

uint16_t fftBins[NUM_BANDS];
uint8_t  levelsL[NUM_BANDS];
uint8_t  levelsR[NUM_BANDS];
uint8_t  scaledLevelsL[NUM_BANDS];
uint8_t  scaledLevelsR[NUM_BANDS];

// ---------------------- noise variables ----------------------- //

// uint32_t x, y, z, dist;
// uint16_t scale = 12;
// uint16_t speed = 2;
// uint8_t xOffset, yOffset;
// uint8_t olddata, data, newdata;
// uint16_t dataTwelve;

// ---------------------- color variables ----------------------- //
// uint8_t hue = 0;saturation = 255, brightness = 255;
// uint8_t iHue, fHue;
// uint8_t spectrumWidth = 36;


void mapFFTLeft() {
  static int   band, currentBrightness;
  static int   i, pos, point;
  static float fHue;

  // nscale8(leds, NUM_LEDS, 220);
  // fadeToBlackBy(leds,NUM_LEDS,9);
  if (readFFT(1, false, false)) {
    pos   = 0;
    point = 0;
    fHue  = 0;

    for (band = 0; band < NUM_BANDS - 1; band++) {
      point += FFT_FIXED_SEGMENT_LENGTH;

      if (band == NUM_BANDS - 1) {
        point = NUM_LEDS - 1;
      }

      currentBrightness = levelsL[band];

      for (i = pos; i < point; i++) {
        leds[i] += CHSV(fHue, 255, currentBrightness);
        fHue     = i * 1.65;
      }
      pos = point;
    }
    blur1d(leds, NUM_LEDS, 1);
  }
}

// void mapFFTLeft() {
//   static uint8_t  band, currentBrightness;
//   static uint16_t i, pos, point;
//   static float    fHue;
//
//   // nscale8(leds, NUM_LEDS, 220);
//   // fadeToBlackBy(leds,NUM_LEDS,9);
//   if (readFFT(1, false, false)) {
//     pos   = 0;
//     point = 0;
//     fHue  = 0;
//
//     for (band = 0; band < NUM_BANDS - 1; band++) {
//       point += FFT_FIXED_SEGMENT_LENGTH;
//
//       if (band == NUM_BANDS - 1) {
//         point = NUM_LEDS - 1;
//       }
//       currentBrightness = levelsL[band];
//
//       for (i = pos; i < point; i++) {
//         leds[i] += CHSV(fHue, 255, currentBrightness);
//         fHue     = i * 1.65;
//       }
//       pos = point;
//     }
//
//     blur1d(leds, NUM_LEDS, 1);
//   }
// }

/*
   void splatter() {

   changePalette();

   EVERY_N_MILLISECONDS(15) {
    fadeToBlackBy(leds, NUM_LEDS, 1);
    //    nscale8(leds, NUM_LEDS, 255);
   }

   blur1d(leds, NUM_LEDS, 100);

   EVERY_N_MILLIS_I( drum_timer, 500 ) {
    uint8_t INDEX = random8(0, 255);
    drum_timer.setPeriod( random16( 200, 500) );
    //pos = sin(x);
    uint16_t position = random8(NUM_LEDS - 1);
    uint8_t width = random8(2, 15);
    uint16_t left_pos  = position - width;
    uint16_t right_pos = position + width;
    if (left_pos < 0) {
      left_pos = 0;
    }
    if (right_pos > NUM_LEDS - 1) {
      right_pos = NUM_LEDS - 1;
    }
    for (int i = left_pos; i <= right_pos; i++) {
      leds[i] += ColorFromPalette(gCurrentPalette, INDEX, 255, LINEARBLEND);
    }
   }
   }
 */


/*
   void radiate_left() {

   changePalette();

   readFFTLeft(0.18);

   leds[half_pos].nscale8(170);
   leds[half_pos + 1].nscale8(170);

   uint8_t bass_l = fftL.read(1, 2);
   uint8_t mids_l = fftL.read(30, 200);
   uint8_t high_l = fftL.read(250, MAX_BIN);

   //  if (bass_l < 8) {
   //    bass_l = 0;
   //  }
   //  if (mids_l < 8) {
   //    mids_l = 0;
   //  }
   //  if (high_l < 8) {
   //    high_l = 0;
   //  }
   //
   //  if (bass_r < 8) {
   //    bass_r = 0;
   //  }
   //  if (mids_r < 8) {
   //    mids_r = 0;
   //  }
   //  if (high_r < 8) {
   //    high_r = 0;
   //  }

   //    uint16_t left_fft_average  = (bass_l + mids_l + high_l) / 3;
   //    uint16_t right_fft_average = (bass_r + mids_r + high_r) / 3;

   //    leds[half_pos + 1] += ColorFromPalette12(gCurrentPalette,
      left_fft_average, left_fft_average, LINEARBLEND);
   //    leds[half_pos] += ColorFromPalette12(gCurrentPalette,
      right_fft_average, right_fft_average, LINEARBLEND);
   //leds[half_pos + 1] += CRGB(bass_l, mids_l, high_l);
   leds[half_pos] += CRGB(bass_l, mids_l, high_l);

   //    leds[half_pos].maximizeBrightness();
   //    leds[half_pos + 1].maximizeBrightness();

   EVERY_N_MILLISECONDS(10) {
     for (int i = NUM_LEDS - 1; i > half_pos; i--) {
       leds[i].blue = leds[i - 1].blue;
     }
     for (int i = 0; i < half_pos + 1; i++) {
       leds[i].blue = leds[i + 1].blue;
     }
   }

   EVERY_N_MILLISECONDS(27) {
     for (int i = NUM_LEDS - 1; i > half_pos; i--) {
       leds[i].green = leds[i - 1].green;
     }
     for (int i = 0; i < half_pos + 1; i++) {
       leds[i].green = leds[i + 1].green;
     }
   }

   EVERY_N_MILLISECONDS(40) {
     for (int i = NUM_LEDS - 1; i > half_pos; i--) {
       leds[i].red = leds[i - 1].red;
     }
     for (int i = 0; i < half_pos + 1; i++) {
       leds[i].red = leds[i + 1].red;
     }
   }
   //blur1d(leds, NUM_LEDS, 13);
   //showAnalogRGB(leds[half_pos]);
   }
 */


/*
   void radiate_stereo() {

    changePalette();

    READ_FFT_STEREO(0.18);

    leds[half_pos].nscale8(170);
    leds[half_pos + 1].nscale8(170);

    uint8_t bass_l = fftL.read(1, 2);
    uint8_t mids_l = fftL.read(30, 200);
    uint8_t high_l = fftL.read(250, MAX_BIN);

    uint8_t bass_r = fftR.read(1, 2);
    uint8_t mids_r = fftR.read(30, 200);
    uint8_t high_r = fftR.read(250, MAX_BIN);

    //  if (bass_l < 8) {
    //    bass_l = 0;
    //  }
    //  if (mids_l < 8) {
    //    mids_l = 0;
    //  }
    //  if (high_l < 8) {
    //    high_l = 0;
    //  }
    //
    //  if (bass_r < 8) {
    //    bass_r = 0;
    //  }
    //  if (mids_r < 8) {
    //    mids_r = 0;
    //  }
    //  if (high_r < 8) {
    //    high_r = 0;
    //  }

    //    uint16_t left_fft_average  = (bass_l + mids_l + high_l) / 3;
    //    uint16_t right_fft_average = (bass_r + mids_r + high_r) / 3;

    //    leds[half_pos + 1] += ColorFromPalette12(gCurrentPalette,
       left_fft_average, left_fft_average, LINEARBLEND);
    //    leds[half_pos] += ColorFromPalette12(gCurrentPalette,
       right_fft_average, right_fft_average, LINEARBLEND);
    leds[half_pos + 1] += CRGB(bass_l, mids_l, high_l);
    leds[half_pos] += CRGB(bass_r, mids_r, high_r);

    //    leds[half_pos].maximizeBrightness();
    //    leds[half_pos + 1].maximizeBrightness();

    EVERY_N_MILLISECONDS(10) {
      for (int i = NUM_LEDS - 1; i > half_pos; i--) {
        leds[i].blue = leds[i - 1].blue;
      }
      for (int i = 0; i < half_pos + 1; i++) {
        leds[i].blue = leds[i + 1].blue;
      }
    }

    EVERY_N_MILLISECONDS(27) {
      for (int i = NUM_LEDS - 1; i > half_pos; i--) {
        leds[i].green = leds[i - 1].green;
      }
      for (int i = 0; i < half_pos + 1; i++) {
        leds[i].green = leds[i + 1].green;
      }
    }

    EVERY_N_MILLISECONDS(40) {
      for (int i = NUM_LEDS - 1; i > half_pos; i--) {
        leds[i].red = leds[i - 1].red;
      }
      for (int i = 0; i < half_pos + 1; i++) {
        leds[i].red = leds[i + 1].red;
      }
    }

    //blur1d(leds, NUM_LEDS, 13);
    //showAnalogRGB(leds[half_pos]);

   }
 */


/*
   void radiate_left() {

   readFFTLeft(0.30);

   leds[half_pos].nscale8(200);

   uint8_t bass_l = averageFFTPortion(levelsL, NUM_BANDS, 0, 3); // 0 => 2
   uint8_t mids_l = averageFFTPortion(levelsL, NUM_BANDS, 13, 25); // 30 =>
   60
   uint8_t high_l = averageFFTPortion(levelsL, NUM_BANDS, 29, 35); // 255 =>
      MAX_BIN

   leds[half_pos].r += bass_l;
   leds[half_pos].g += mids_l;
   leds[half_pos].b += high_l;

   EVERY_N_MILLISECONDS(10) {
    for (int i = NUM_LEDS - 1; i > half_pos; i--) {
      leds[i].blue = leds[i - 1].blue;
    }
    for (int i = 0; i < half_pos + 1; i++) {
      leds[i].blue = leds[i + 1].blue;
    }
   }

   EVERY_N_MILLISECONDS(27) {
    for (int i = NUM_LEDS - 1; i > half_pos; i--) {
      leds[i].green = leds[i - 1].green;
    }
    for (int i = 0; i < half_pos + 1; i++) {
      leds[i].green = leds[i + 1].green;
    }
   }

   EVERY_N_MILLISECONDS(40) {
    for (int i = NUM_LEDS - 1; i > half_pos; i--) {
      leds[i].red = leds[i - 1].red;
    }
    for (int i = 0; i < half_pos + 1; i++) {
      leds[i].red = leds[i + 1].red;
    }
   }

   blur1d(leds, NUM_LEDS, 13);

   }
 */


/*
   void flex_fft_stereo() {

   // 172 fps

   uint16_t left_pos    = half_pos;
   uint16_t left_point  = half_pos;
   uint16_t right_pos   = half_pos;
   uint16_t right_point = half_pos;

   uint8_t current_hue = 0;

   READ_FFT_STEREO(0.18);

   nscale8(leds, NUM_LEDS, 230);

   for (int band = 0; band < NUM_BANDS; band++) {

   uint8_t currentLeftAmp = levelsL[band];
   uint8_t currentRightAmp = levelsR[band];

   left_point -= scaledLevelsL[band];
   right_point += scaledLevelsR[band];

   current_hue += HUE_LENGTH;

   for (uint8_t i = left_pos; i > left_point; i--) {
     leds[i] += CHSV(current_hue, 255, currentLeftAmp);
   }
   for (uint8_t i = right_pos; i < right_point; i++) {
     leds[i] += CHSV(current_hue, 255, currentRightAmp);
   }

   left_pos = left_point;
   right_pos = right_point;

   }

   blur1d(leds, NUM_LEDS, 10);

   }
 */


/*
   void flex_fftLeft() {

   // 172 fps

   uint16_t left_pos    = half_pos;
   uint16_t left_point  = half_pos;
   uint16_t right_pos   = half_pos;
   uint16_t right_point = half_pos;

   uint8_t current_hue = 0;
   //uint8_t next_hue = 0;

   readFFTLeft(0.18);

   nscale8(leds, NUM_LEDS, 230);

   for (int band = 0; band < NUM_BANDS; band++) {

   uint8_t currentBrightness = levelsL[band];

   left_point -= scaledLevelsL[band];
   right_point += scaledLevelsL[band];

   //    if (band < NUM_BANDS - 1) {
   current_hue += HUE_LENGTH;
   //    }

   //    else {
   //      current_hue = next_hue;
   //      //next_hue = current_hue;
   //      //left_next_brightness = 0;
   //      //right_next_brightness = 0;
   //      left_point = 0;
   //      right_point = NUM_LEDS - 1;
   //    }

   for (uint8_t i = left_pos; i > left_point; i--) {
     leds[i] += CHSV(current_hue, 255, currentBrightness);
   }
   for (uint8_t i = right_pos; i < right_point; i++) {
     leds[i] += CHSV(current_hue, 255, currentBrightness);
   }

   // fun-ish times with 16 bit math
   //    for (uint16_t p = left_pos; p > left_point; p--) {
   //      CRGB color = CHSV(current_hue, 255, currentBrightness);
   //      setPartialPixel(p, color);
   //    }
   //    for (uint16_t p = right_pos; p < right_point; p++) {
   //      CRGB color = CHSV(current_hue, 255, currentBrightness);
   //      setPartialPixel(p, color);
   //    }

   left_pos = left_point;
   right_pos = right_point;

   }
   //FastLED.show();

   }

 */


/*
   uint16_t scale_twelve = 400;

   void ambient() {

   changePalette();
   //gCurrentPalette = gGradientPalettes[0];

   // 1, 3, 5, 10, 12,
   // try BROWN
   Serial.println(gCurrentPaletteNumber);

   for (int i = 11; i < NUM_LEDS - 14; i++) {

    dataTwelve = inoise16(x + (i * scale_twelve), y + (dist + scale_twelve),
   z)
       % 4095;
    dataTwelve = constrain(dataTwelve, 0, 4095);

    leds[i] = ColorFromPalette12( gCurrentPalette, dataTwelve, 255,
       LINEARBLEND);

   }

   z += 13;
   y += 15;
   //Serial.println(z);

   blur1d(leds, NUM_LEDS, 150);
   //showAnalogRGB(leds[half_pos]);
   }


 */


/*
   void flex_fft_stereo() {

   // 172 fps

   uint16_t left_pos    = half_pos;
   uint16_t left_point  = half_pos;
   uint16_t right_pos   = half_pos;
   uint16_t right_point = half_pos;

   uint8_t current_hue = 0;

   READ_FFT_STEREO(0.18);

   nscale8(leds, NUM_LEDS, 230);

   for (int band = 0; band < NUM_BANDS; band++) {

   uint8_t currentLeftAmp = levelsL[band];
   uint8_t currentRightAmp = levelsR[band];

   left_point -= scaledLevelsL[band];
   right_point += scaledLevelsR[band];

   current_hue += HUE_LENGTH;

   for (uint8_t i = left_pos; i > left_point; i--) {
     leds[i] += CHSV(current_hue, 255, currentLeftAmp);
   }
   for (uint8_t i = right_pos; i < right_point; i++) {
     leds[i] += CHSV(current_hue, 255, currentRightAmp);
   }

   left_pos = left_point;
   right_pos = right_point;

   }

   blur1d(leds, NUM_LEDS, 10);

   }
 */


/*
   void radiate_left() {

   readFFTLeft(0.30);

   leds[half_pos].nscale8(200);

   uint8_t bass_l = averageFFTPortion(levelsL, NUM_BANDS, 0, 3); // 0 => 2
   uint8_t mids_l = averageFFTPortion(levelsL, NUM_BANDS, 13, 25); // 30 =>
   60
   uint8_t high_l = averageFFTPortion(levelsL, NUM_BANDS, 29, 35); // 255 =>
      MAX_BIN

   leds[half_pos].r += bass_l;
   leds[half_pos].g += mids_l;
   leds[half_pos].b += high_l;

   EVERY_N_MILLISECONDS(10) {
   for (int i = NUM_LEDS - 1; i > half_pos; i--) {
     leds[i].blue = leds[i - 1].blue;
   }
   for (int i = 0; i < half_pos + 1; i++) {
     leds[i].blue = leds[i + 1].blue;
   }
   }

   EVERY_N_MILLISECONDS(27) {
   for (int i = NUM_LEDS - 1; i > half_pos; i--) {
     leds[i].green = leds[i - 1].green;
   }
   for (int i = 0; i < half_pos + 1; i++) {
     leds[i].green = leds[i + 1].green;
   }
   }

   EVERY_N_MILLISECONDS(40) {
   for (int i = NUM_LEDS - 1; i > half_pos; i--) {
     leds[i].red = leds[i - 1].red;
   }
   for (int i = 0; i < half_pos + 1; i++) {
     leds[i].red = leds[i + 1].red;
   }
   }

   blur1d(leds, NUM_LEDS, 13);

   }

 */


/*
   void flex_fft_stereo() {

   // 172 fps

   uint16_t left_pos    = half_pos;
   uint16_t left_point  = half_pos;
   uint16_t right_pos   = half_pos;
   uint16_t right_point = half_pos;

   uint8_t current_hue = 0;

   READ_FFT_STEREO(0.18);

   nscale8(leds, NUM_LEDS, 230);

   for (int band = 0; band < NUM_BANDS; band++) {

   uint8_t currentLeftAmp = levelsL[band];
   uint8_t currentRightAmp = levelsR[band];

   left_point -= scaledLevelsL[band];
   right_point += scaledLevelsR[band];

   current_hue += HUE_LENGTH;

   for (uint8_t i = left_pos; i > left_point; i--) {
     leds[i] += CHSV(current_hue, 255, currentLeftAmp);
   }
   for (uint8_t i = right_pos; i < right_point; i++) {
     leds[i] += CHSV(current_hue, 255, currentRightAmp);
   }

   left_pos = left_point;
   right_pos = right_point;

   }

   blur1d(leds, NUM_LEDS, 10);

   }
 */

/*
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
   //    if (band == 6) (left_point = 0) && (right_point = NUM_LEDS - 1) &&
      (next_hue = band * spectrumWidth) && (left_next_brightness = 0) &&
      (right_next_brightness = 0);
   //
   //    fill_gradient(leds, left_pos, CHSV(current_hue, 255,
      left_current_brightness), left_point, CHSV(next_hue, 255,
      left_next_brightness), SHORTEST_HUES);
   //    fill_gradient(leds, right_pos, CHSV(current_hue, 255,
      right_current_brightness), right_point, CHSV(next_hue, 255,
      right_next_brightness), SHORTEST_HUES);
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
   //




   //Serial.println("---------------------------------------------------------");
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
   //      //        left_current_brightness  = (levelsL[band] +
   levelsR[band])
 * 0.5 * SCALE;
   //      //        left_current_brightness  = prev_brightness_left +
      (left_current_brightness - prev_brightness_left)  *
   flex_low_pass_stereo;
   //      //        levelsL[band] = left_current_brightness;
   //      //        right_current_brightness = left_current_brightness;
   //      //
   //      //        left_next_brightness     = levelsL[band + 1] * SCALE;
   //      //        left_next_brightness     = prev_brightness_k_left +
      (left_next_brightness - prev_brightness_k_left)  *
   flex_low_pass_stereo;
   //      //
   //      //        right_current_brightness  = levelsR[band] * SCALE;
   //      //        right_current_brightness  = prev_brightness_right +
      (right_current_brightness - prev_brightness_right)  *
      flex_low_pass_stereo;
   //      //        levelsR[band] = right_current_brightness;
   //      //
   //      //        right_next_brightness     = levelsR[band + 1] * SCALE;
   //      //        right_next_brightness     = prev_brightness_k_right +
      (right_next_brightness - prev_brightness_k_right)  *
   flex_low_pass_stereo;
   //      //
   //      //      }
   //
   //      //if ((band > 0) && (band < NUM_BANDS - 1)) {
   //
   //      //next_hue += HUE_LENGTH;
   //
   //      left_current_brightness  = levelsL[band] * SCALE;
   //      left_current_brightness  = prev_brightness_left +
      (left_current_brightness - prev_brightness_left)  *
   flex_low_pass_stereo;
   //      levelsL[band] = left_current_brightness;
   //
   //      //      left_next_brightness     = levelsL[band + 1] * SCALE;
   //      //      left_next_brightness     = prev_brightness_k_left +
      (left_next_brightness - prev_brightness_k_left)  *
   flex_low_pass_stereo;
   //
   //      right_current_brightness  = levelsR[band] * SCALE;
   //      right_current_brightness  = prev_brightness_right +
      (right_current_brightness - prev_brightness_right)  *
      flex_low_pass_stereo;
   //      levelsR[band] = right_current_brightness;
   //
   //      if (band == 0) {
   //        left_current_brightness = (left_current_brightness +
      right_current_brightness) * 0.5;
   //        right_current_brightness = left_current_brightness;
   //      }
   //
   //      //      right_next_brightness     = levelsR[band + 1] * SCALE;
   //      //      right_next_brightness     = prev_brightness_k_right +
      (right_next_brightness - prev_brightness_k_right)  *
   flex_low_pass_stereo;
   //
   //      //}
   //
   //      //      else {
   //      //
   //      //        //next_hue = current_hue;
   //      //
   //      //        left_current_brightness  = left_next_brightness;
   //      //        //left_current_brightness  = prev_brightness_left +
      (left_current_brightness - prev_brightness_left)  *
   flex_low_pass_stereo;
   //      //
   //      //        right_current_brightness  = right_next_brightness;
   //      //        //right_current_brightness  = prev_brightness_right +
      (right_current_brightness - prev_brightness_right)  *
      flex_low_pass_stereo;
   //      //
   //      //        left_next_brightness = 0;
   //      //        right_next_brightness = 0;
   //      //
   //      //        left_point = 0;
   //      //        right_point = NUM_LEDS - 1;
   //      //      }
   //
   //
   //      if (band == NUM_BANDS - 1) { // prevent from drawing outside of
   strip
      dimensions
   //        left_point = 0;
   //        right_point = NUM_LEDS - 1;
   //      }
   //
   //      for (uint8_t i = left_pos; i > left_point; i--) {
   //        colorIndex = i * PALETTE_INDEX_INCREMENT;
   //        leds[i] += ColorFromPalette( gCurrentPalette, colorIndex,
      left_current_brightness, LINEARBLEND);
   //      }
   //      for (uint8_t i = right_pos; i < right_point; i++) {
   //        colorIndex = i * PALETTE_INDEX_INCREMENT;
   //        leds[i] += ColorFromPalette( gCurrentPalette, colorIndex,
      right_current_brightness, LINEARBLEND);
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
 */

//
