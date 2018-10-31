#ifndef COLOR_PALETTE_MANAGER_H
#define COLOR_PALETTE_MANAGER_H

#include "../config/config.h"

extern const TProgmemRGBGradientPalettePtr gGradientPalettes[];

extern const uint8_t gGradientPaletteCount;
extern uint8_t gCurrentPaletteNumber;
extern uint8_t palette;
extern CRGBPalette16 gCurrentPalette;
extern CRGBPalette16 gTargetPalette;

namespace ColorPaletteManager
{
void initialize(void);
void runTask(void);
} // namespace ColorPaletteManager

#endif
