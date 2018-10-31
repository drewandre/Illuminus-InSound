#include "../dmx/dmx_manager.h"

#include "./color_palette_list.h"

/*======================*/
/*  external variables  */
const TProgmemRGBGradientPalettePtr gGradientPalettes[] = {
    bhw1_06_gp,
    bhw1_04_gp,
    rainbow,
    rainbow,
    rgi_13_gp, // nice really orange
    red,
    bhw1_purplered_gp,
    bhw1_05_gp,
    winter_gp}; // cool

const uint8_t gGradientPaletteCount = sizeof(gGradientPalettes) /
                                      sizeof(TProgmemRGBGradientPalettePtr);

uint8_t gCurrentPaletteNumber = 0;

CRGBPalette16 gCurrentPalette(
    gGradientPalettes[gGradientPaletteCount]);

CRGBPalette16 gTargetPalette(
    gGradientPalettes[gGradientPaletteCount + 1]);

/* ====================== */

namespace ColorPaletteManager
{
void initialize(void)
{
  gCurrentPalette = rainbow;
}
void runTask(void)
{
#if CHANGE_PALATTE_PERIODICALLY == true
  EVERY_N_SECONDS(CHANGE_PALETTE_EVERY_N_SECONDS)
  {
    // Serial.println(gCurrentPaletteNumber);
    gCurrentPaletteNumber = addmod8(gCurrentPaletteNumber,
                                    1,
                                    gGradientPaletteCount);
    gTargetPalette = gGradientPalettes[gCurrentPaletteNumber];
  }
#endif // ifdef change_palette_periodically

  EVERY_N_MILLISECONDS(COLOR_PALETTE_BLEND_UPDATE_SPEED_MILLISECONDS)
  {
    nblendPaletteTowardPalette(gCurrentPalette,
                               gTargetPalette,
                               COLOR_PALETTE_SPEED);
  }
}
} // namespace ColorPaletteManager
