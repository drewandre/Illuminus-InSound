#include "./animation_generator.h"
#include "../color_palettes/color_palette_manager.h"

/*======================*/
/*  external variables  */
CRGB colors[NUM_FIXTURES];

/*======================*/

int fadeToBlackValues[NUM_FIXTURES_PER_CHANNEL] = {FADE_TO_BLACK_VALUES};
int nscaleValues[NUM_FIXTURES_PER_CHANNEL] = {NSCALE_VALUES};

namespace AnimationGenerator
{
void mapFFTMono(void)
{
  static float currentLeftBrightness;
  static uint8_t hueIndex;
  static uint8_t HUE_MULTIPLIER = 255 / NUM_FIXTURES_PER_CHANNEL;
  static CRGB currentLeftColor;

  for (uint8_t band = 0; band < NUM_FIXTURES_PER_CHANNEL; band++)
  {
    currentLeftBrightness = levelsL[band];
    hueIndex = band * HUE_MULTIPLIER;

#if USE_COLOR_PALETTES
    currentLeftColor = ColorFromPalette(gCurrentPalette, hueIndex, currentLeftBrightness);

    colors[NUM_FIXTURES_PER_CHANNEL_MINUS_ONE - band] = currentLeftColor;
    colors[NUM_FIXTURES_PER_CHANNEL + band] = currentLeftColor;

    // colors[band + NUM_FIXTURES_PER_CHANNEL] = ColorFromPalette(gCurrentPalette, 0, 255, LINEARBLEND);
    // colors[NUM_FIXTURES_PER_CHANNEL_MINUS_ONE - band] = CHSV(200, 255, 255);

#else
    currentLeftColor = CHSV(hueIndex, 255, currentLeftBrightness);
    colors[NUM_FIXTURES_PER_CHANNEL_MINUS_ONE - band] = currentLeftColor;
    colors[NUM_FIXTURES_PER_CHANNEL + band] = currentLeftColor;
#endif
  }
#if BLUR_ANIMATION == true
  blur1d(colors, NUM_FIXTURES, BLUR_VALUE);
#endif
}

void mapFFTStereo(void)
{
  static float currentLeftBrightness, currentRightBrightness;
  static uint8_t hueIndex;
  static uint8_t HUE_MULTIPLIER = 255 / NUM_FIXTURES_PER_CHANNEL;
  static CRGB currentLeftColor, currentRightColor;

  for (uint8_t band = 0; band < NUM_FIXTURES_PER_CHANNEL; band++)
  {
    currentLeftBrightness = levelsL[band];
    currentRightBrightness = levelsR[band];
    hueIndex = band * HUE_MULTIPLIER;

#if USE_COLOR_PALETTES
    currentLeftColor = ColorFromPalette(gCurrentPalette, hueIndex, currentLeftBrightness);
    currentRightColor = ColorFromPalette(gCurrentPalette, hueIndex, currentRightBrightness);

    colors[NUM_FIXTURES_PER_CHANNEL_MINUS_ONE - band] += currentLeftColor;
    colors[NUM_FIXTURES_PER_CHANNEL + band] += currentRightColor;

    // colors[band + NUM_FIXTURES_PER_CHANNEL] = ColorFromPalette(gCurrentPalette, 0, 255, LINEARBLEND);
    // colors[NUM_FIXTURES_PER_CHANNEL_MINUS_ONE - band] = CHSV(200, 255, 255);

#else
    currentLeftColor = CHSV(hueIndex, 255, currentLeftBrightness);
    currentRightColor = CHSV(hueIndex, 255, currentRightBrightness);

    colors[NUM_FIXTURES_PER_CHANNEL_MINUS_ONE - band] = currentLeftColor;
    colors[NUM_FIXTURES_PER_CHANNEL + band] = currentRightColor;
#endif
  }
#if BLUR_ANIMATION == true
  blur1d(colors, NUM_FIXTURES, BLUR_VALUE);
#endif
}

void fadeFixturesToBlack()
{
  for (uint8_t band = 0; band < NUM_FIXTURES_PER_CHANNEL; band++)
  {
    // colors[NUM_FIXTURES_PER_CHANNEL_MINUS_ONE - band].nscale8(nscaleValues[band]);

    // colors[NUM_FIXTURES_PER_CHANNEL_MINUS_ONE - band].fadeToBlackBy(10);
    // colors[band + NUM_FIXTURES_PER_CHANNEL].fadeToBlackBy(fadeToBlackValues[band]);
  }
}

void colorFade(void)
{
  static int i;
  EVERY_N_MILLISECONDS(20)
  {
    i++;
    if (i > 255)
      i = 0;
  }
  for (uint8_t band = 0; band < NUM_FIXTURES; band++)
  {
    colors[band] = CHSV(i - (band * 36), 255, MAX_BRIGHTNESS);
  }
  blur1d(colors, NUM_FIXTURES, 10);
}
} // namespace AnimationGenerator