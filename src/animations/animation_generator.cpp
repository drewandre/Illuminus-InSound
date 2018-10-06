#include "./animation_generator.h"

namespace AnimationGenerator {
void mapFFTMono() {
  static int   band, currentBrightness;
  static int   i, pos, point;
  static float fHue;
  static int FFT_FIXED_SEGMENT_LENGTH = NUM_LEDS / NUM_BANDS;
  
  // nscale8(leds, NUM_LEDS, 220);
  // fadeToBlackBy(leds,NUM_LEDS,9);
  if (readFFT(0.3, false, false)) {
    fill_solid(leds, NUM_LEDS, CRGB::Black);

    pos   = 0;
    point = 0;
    fHue  = 0.0;

    for (band = 0; band < NUM_BANDS; band++) {
      point += FFT_FIXED_SEGMENT_LENGTH;
      currentBrightness = levelsL[band];

      for (i = pos; i < point; i++) {
        // setPartialPixel(4.5, CRGB::Green, leds);
        leds[i] += CHSV(fHue, 255, currentBrightness);
        fHue     = float(i * 1.6);
      }
      pos = point;
    }
    // blur1d(leds, NUM_LEDS, 10);
  }
}

void flexFFTStereo() {
  static float currentLeftAmp;
  static float currentRightAmp;
  static float leftPos;
  static float leftPoint;
  static float rightPos;
  static float rightPoint;
  static uint16_t i;
  static uint8_t band;
  static float currentHue;

  leftPos    = HALF_POS;
  leftPoint  = HALF_POS;
  rightPos   = HALF_POS;
  rightPoint = HALF_POS;
  currentHue = 0;

  if (readFFT(0.08, true, true)) {
    nscale8(leds, NUM_LEDS, 230);

    for (band = 0; band < NUM_BANDS; band++) {
      currentLeftAmp = levelsL[band];
      currentRightAmp = levelsR[band];

      leftPoint -= scaledLevelsL[band];
      rightPoint += scaledLevelsR[band];
      if (leftPoint < 0) leftPoint = 0;
      if (rightPoint > NUM_LEDS - 1) rightPoint = 0;

      currentHue = band * 10.5;

      for (i = leftPos; i > leftPoint; i--) {
        leds[i] += CHSV(currentHue, 255, currentLeftAmp);
      }
      for (i = rightPos; i < rightPoint; i++) {
        leds[i] += CHSV(currentHue, 255, currentRightAmp);
      }

      leftPos = leftPoint;
      rightPos = rightPoint;
    }
    blur1d(leds, NUM_LEDS, 10);
  };
}

void drawFractionalBar( int pos16, int width, uint8_t hue) {
  static int i;
  static uint8_t frac, firstpixelbrightness, lastpixelbrightness, bright;

  i = pos16 / 16; // convert from pos to raw pixel number
  frac = pos16 & 0x0F; // extract the 'factional' part of the position
 
  // brightness of the first pixel in the bar is 1.0 - (fractional part of position)
  // e.g., if the light bar starts drawing at pixel "57.9", then
  // pixel #57 should only be lit at 10% brightness, because only 1/10th of it
  // is "in" the light bar:
  //
  //                       57.9 . . . . . . . . . . . . . . . . . 61.9
  //                        v                                      v
  //  ---+---56----+---57----+---58----+---59----+---60----+---61----+---62---->
  //     |         |        X|XXXXXXXXX|XXXXXXXXX|XXXXXXXXX|XXXXXXXX |  
  //  ---+---------+---------+---------+---------+---------+---------+--------->
  //                   10%       100%      100%      100%      90%        
  //
  // the fraction we get is in 16ths and needs to be converted to 256ths,
  // so we multiply by 16.  We subtract from 255 because we want a high
  // fraction (e.g. 0.9) to turn into a low brightness (e.g. 0.1)
  firstpixelbrightness = 255 - (frac * 16);
 
  // if the bar is of integer length, the last pixel's brightness is the
  // reverse of the first pixel's; see illustration above.
  lastpixelbrightness  = 255 - firstpixelbrightness;
 
  // For a bar of width "N", the code has to consider "N+1" pixel positions,
  // which is why the "<= width" below instead of "< width".
 
  bright;
  for( int n = 0; n <= width; n++) {
    if( n == 0) {
      // first pixel in the bar
      bright = firstpixelbrightness;
    } else if( n == width ) {
      // last pixel in the bar
      bright = lastpixelbrightness;
    } else {
      // middle pixels
      bright = 255;
    }
   
    leds[i] += CHSV( hue, 255, bright);
    i++;
    if( i == NUM_LEDS) i = 0; // wrap around
  }
}


void fractionalFlexFFTStereo() {
  static float currentLeftAmp;
  static float currentRightAmp;
  static float nextLeftAmp;
  static float nextRightAmp;
  static float leftPos;
  static float leftPoint;
  static float rightPos;
  static float rightPoint;
  static float currentHue;
  static float nextHue;
  static uint16_t i;
  static uint8_t band;

  leftPos    = HALF_POS;
  leftPoint  = HALF_POS;
  rightPos   = HALF_POS;
  rightPoint = HALF_POS;
  currentHue = 0;

  if (readFFT(0.2, true, true)) {
    nscale8(leds, NUM_LEDS, 180); // lower = faster decay

    for (band = 0; band < NUM_BANDS; band++) {
      currentLeftAmp = levelsL[band];
      currentRightAmp = levelsR[band];
      currentHue = band * 10.5;

      if (band < NUM_BANDS - 1) {
        nextLeftAmp = levelsL[band + 1];
        nextRightAmp = levelsR[band + 1];
        nextHue = (band + 1) * 10.5;
      } else {
        nextLeftAmp = currentLeftAmp;
        nextRightAmp = currentRightAmp;
        nextHue = currentHue;
      }

      leftPoint -= scaledLevelsL[band];
      rightPoint += scaledLevelsR[band];
      if (leftPoint < 0) leftPoint = 0;
      if (rightPoint > NUM_LEDS - 1) rightPoint = NUM_LEDS;

      fill_gradient(
        tempLeds,
        leftPos,
        CHSV(currentHue, 255, currentLeftAmp),
        leftPoint,
        CHSV(nextHue, 255, nextLeftAmp)
      );

      fill_gradient(
        tempLeds,
        rightPos,
        CHSV(currentHue, 255, currentRightAmp),
        rightPoint,
        CHSV(nextHue, 255, nextRightAmp)
      );

      for (i = 0; i < NUM_LEDS; i++) {
        leds[i] += tempLeds[i];
      }

      // for (i = leftPos; i > leftPoint; i--) {
      //   leds[i] = CHSV(currentHue, 255, currentLeftAmp);
      // }
      // for (i = rightPos; i < rightPoint; i++) {
      //   leds[i] = CHSV(currentHue, 255, currentRightAmp);
      // }

      leftPos = leftPoint;
      rightPos = rightPoint;
    }
    blur1d(leds, NUM_LEDS, 10);
  };
}


void rainbow() {
  // static int i = 0;
  // EVERY_N_MILLISECONDS(100) {
  //   i += 1;
  // }
  // fill_rainbow(leds, 144, 0, i);
  fill_solid(leds, NUM_LEDS, CRGB::Blue);
}

void radiateStereo() {
  static uint8_t bassL, midsL, highL, bassR, midsR, highR;

  if (readFFT(0.25, true, true)) {
    leds[HALF_POS].nscale8(170);
    leds[HALF_POS + 1].nscale8(170);

    bassL = fftL.read(1, 3) * 255.0;
    midsL = fftL.read(30, 200) * 255.0;
    highL = fftL.read(275, MAX_BIN) * 255.0;

    bassR = fftR.read(1, 5) * 250.0;
    midsR = fftR.read(30, 200) * 250.0;
    highR = fftR.read(250, MAX_BIN) * 250.0;
    
    // leds[HALF_POS + 1] += ColorFromPalette12(gCurrentPalette,
    // left_fft_average, left_fft_average, LINEARBLEND);
    // leds[HALF_POS] += ColorFromPalette12(gCurrentPalette,
    // right_fft_average, right_fft_average, LINEARBLEND);

    leds[HALF_POS + 1] += CRGB(bassL, midsL, highL);
    leds[HALF_POS] += CRGB(bassR, midsR, highR);

    //    leds[HALF_POS].maximizeBrightness();
    //    leds[HALF_POS + 1].maximizeBrightness();

    EVERY_N_MILLISECONDS(10) {
      for (int i = NUM_LEDS - 1; i > HALF_POS; i--) {
        leds[i].blue = leds[i - 1].blue;
      }
      for (int i = 0; i < HALF_POS + 1; i++) {
        leds[i].blue = leds[i + 1].blue;
      }
    }

    EVERY_N_MILLISECONDS(27) {
      for (int i = NUM_LEDS - 1; i > HALF_POS; i--) {
        leds[i].green = leds[i - 1].green;
      }
      for (int i = 0; i < HALF_POS + 1; i++) {
        leds[i].green = leds[i + 1].green;
      }
    }

    EVERY_N_MILLISECONDS(40) {
      for (int i = NUM_LEDS - 1; i > HALF_POS; i--) {
        leds[i].red = leds[i - 1].red;
      }
      for (int i = 0; i < HALF_POS + 1; i++) {
        leds[i].red = leds[i + 1].red;
      }
    }

    blur1d(leds, NUM_LEDS, 13);
    }
  }

}