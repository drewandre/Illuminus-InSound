#ifndef DMX_MANAGER_H
#define DMX_MANAGER_H

#include "../config/config.h"
#include "Sixbar.h"

extern CRGB leftChannelFixtures[NUM_FIXTURES_PER_CHANNEL];
extern CRGB rightChannelFixtures[NUM_FIXTURES_PER_CHANNEL];

namespace DMXManager
{
void initialize(void);
void initializeFixtures(void);
void blackOut(void);
void testCRGB(const CRGB &rgb);
void show(void);
} // namespace DMXManager

#endif
