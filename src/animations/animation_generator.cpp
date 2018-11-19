#include "./animation_generator.h"
#include "../color_palettes/color_palette_manager.h"

/*======================*/
/*  external variables  */
CRGB colors[NUM_FIXTURES];

/*======================*/

int fadeToBlackValues[NUM_FIXTURES_PER_CHANNEL] = {FADE_TO_BLACK_VALUES};
int nscaleValues[NUM_FIXTURES_PER_CHANNEL] = {NSCALE_VALUES};

const int MAP_FFT_FIXTURE_VALUES[NUM_FIXTURES_PER_CHANNEL] = {2, 1, 1, 1, 1, 1, 2};
//   [ 0, 1, 2, 3 ],
//   [ 4, 5 ],
//   [ 6, 7 ],
//   [ 8, 9 ],
//   [ 10, 11 ],
//   [12],
//   [13]
// ];

namespace AnimationGenerator
{
void mirrorFFTLeft(void)
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

void mapFFTLeft(void)
{
  static float currentLeftBrightness;
  static uint8_t hueIndex, currentFixture;
  static uint8_t HUE_MULTIPLIER = 255 / NUM_FIXTURES_PER_CHANNEL;
  static CRGB currentLeftColor;

  currentFixture = 0;

  for (uint8_t band = 0; band < NUM_FIXTURES_PER_CHANNEL; band++)
  {
    currentLeftBrightness = levelsL[band];
    hueIndex = band * HUE_MULTIPLIER;

#if USE_COLOR_PALETTES
    currentLeftColor = ColorFromPalette(gCurrentPalette, hueIndex, currentLeftBrightness);
#else
    currentLeftColor = CHSV(hueIndex, 255, currentLeftBrightness);
#endif
    for (uint8_t i = 0; i < MAP_FFT_FIXTURE_VALUES[band]; i++)
    {
      colors[currentFixture] = currentLeftColor;
      currentFixture++;
    }
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

void customMappingForPeobody(void)
{
  // pod 1
  // colors[0] = colors[0];
  // colors[1] = colors[1];

  // CRGB c = colors[5];

  // colors[5] = colors[7];
  // colors[6] = colors[7];
  // colors[7] = colors[7];

  // // pod 2
  // colors[7] = colors[4];
  // colors[8] = c;

  // pod 3
  // colors[6] = colors[5];
}

} // namespace AnimationGenerator

/*
  // const int MAP_FFT_FIXTURE_VALUES[NUM_FIXTURES_PER_CHANNEL] = {2, 1, 1, 1, 1, 1, 2};
  static int customMappingValuesForPeobody[NUM_FIXTURES] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
  for (int i = 0; i < NUM_FIXTURES; i++)
  {
    colors[i] = colors[customMappingValuesForPeobody[i]];
  }
*/