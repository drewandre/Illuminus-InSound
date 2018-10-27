#include "./animation_generator.h"

namespace AnimationGenerator
{
void mapFFTMono()
{
  static int band, currentBrightness;
  static int i, pos, point;
  static float fHue;
  static int FFT_FIXED_SEGMENT_LENGTH = 20 / NUM_BANDS;

  // nscale8(leds, NUM_LEDS, 220);
  // fadeToBlackBy(leds,NUM_LEDS,9);
  if (readFFT(0.3, false, PRINT_FFT))
  {
    pos = 0;
    point = 0;
    fHue = 0.0;

    for (band = 0; band < NUM_BANDS; band++)
    {
      point += FFT_FIXED_SEGMENT_LENGTH;
      currentBrightness = levelsL[band];

      for (i = pos; i < point; i++)
      {
        // setPartialPixel(4.5, CRGB::Green, leds);
        // leds[i] += CHSV(fHue, 255, currentBrightness);
        fHue = float(i * 1.6);
      }
      pos = point;
    }
    // blur1d(leds, NUM_LEDS, 10);
  }
}
} // namespace AnimationGenerator