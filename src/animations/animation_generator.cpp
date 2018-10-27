#include "./animation_generator.h"
#include "../color_palettes/color_palette_manager.h"

/*======================*/
/*  external variables  */
CRGB colors[NUM_FIXTURES];

/*======================*/

namespace AnimationGenerator
{
void mapFFTStereo(void)
{
  static float currentLeftBrightness, currentRightBrightness, hueIndex;
  static float HUE_MULTIPLIER = 255 / NUM_FIXTURES_PER_CHANNEL;
  static CRGB currentLeftColor, currentRightColor;

  fadeToBlackBy(colors, NUM_FIXTURES, FADE_TO_BLACK_PER_CYCLE_VALUE);

  for (uint8_t band = 0; band < NUM_FIXTURES_PER_CHANNEL; band++)
  {
    currentLeftBrightness = levelsL[band];
    currentRightBrightness = levelsR[band];
    hueIndex = band * HUE_MULTIPLIER;

#if USE_COLOR_PALETTES
    currentLeftColor = ColorFromPalette(gCurrentPalette, hueIndex, currentLeftBrightness, LINEARBLEND);
    currentRightColor = ColorFromPalette(gCurrentPalette, hueIndex, currentRightBrightness, LINEARBLEND);
    colors[NUM_FIXTURES_PER_CHANNEL_MINUS_ONE - band] += currentLeftColor;
    colors[band + NUM_FIXTURES_PER_CHANNEL] += currentRightColor;
#else
    colors[NUM_FIXTURES_PER_CHANNEL_MINUS_ONE - band] += CHSV(hueIndex, 255, currentLeftBrightness);
    colors[band + NUM_FIXTURES_PER_CHANNEL] += CHSV(hueIndex, 255, currentRightBrightness);
#endif
  }
#if BLUR_ANIMATION == true
  blur1d(colors, NUM_FIXTURES, BLUR_VALUE);
#endif
}
} // namespace AnimationGenerator