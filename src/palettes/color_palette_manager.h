#ifndef COLOR_PALETTE_MANAGER_H
#define COLOR_PALETTE_MANAGER_H

#include "./color_palette_list.h"

#include "../macros.h"

namespace ColorPaletteManager {
void changePalette(void);
void mapPalette(void);
void FillLEDsFromPaletteColors(void);
void FillLEDsFromPaletteColorsTwelve(void);
}

#endif
