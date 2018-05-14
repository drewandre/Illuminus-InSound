#include <FastLED.h>
#include <env.h>

void changePalette() {
#ifdef change_palette_periodically
  EVERY_N_SECONDS(10) {
    gCurrentPaletteNumber = addmod8(gCurrentPaletteNumber,
                                    1,
                                    gGradientPaletteCount);
    gTargetPalette        = gGradientPalettes[gCurrentPaletteNumber];
  }
#endif // ifdef change_palette_periodically

  EVERY_N_MILLISECONDS(10) {
    nblendPaletteTowardPalette(gCurrentPalette,
                               gTargetPalette,
                               COLOR_PALETTE_SPEED);
  }
}
