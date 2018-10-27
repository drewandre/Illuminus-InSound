#include "./animation_generator.h"

/*======================*/
/*  external variables  */
CRGB colors[NUM_FIXTURES];

/*======================*/

namespace AnimationGenerator
{
void mapFFTStereo(void)
{
  static float currentLeftBrightness, currentRightBrightness, currentHue;
  static float HUE_MULTIPLIER = 255 / NUM_FIXTURES_PER_CHANNEL;

  fadeToBlackBy(colors, NUM_FIXTURES, 2);

  for (uint8_t band = 0; band < NUM_FIXTURES_PER_CHANNEL; band++)
  {
    currentLeftBrightness = levelsL[band];
    currentRightBrightness = levelsR[band];
    currentHue = band * HUE_MULTIPLIER;

    colors[NUM_FIXTURES_PER_CHANNEL_MINUS_ONE - band] += CHSV(currentHue, 255, currentLeftBrightness);
    colors[band + NUM_FIXTURES_PER_CHANNEL] += CHSV(currentHue, 255, currentRightBrightness);
  }
  // blur1d(colors, NUM_FIXTURES, 100);
}
} // namespace AnimationGenerator