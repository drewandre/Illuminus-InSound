#ifndef DMX_MANAGER_H
#define DMX_MANAGER_H

#include "../config/config.h"
#include "Sixbar.h"

#include "../animations/animation_generator.h"

namespace DMXManager
{
void initialize(void);
void initializeFixtures(void);
void blackout(void);
void displayAnimation(void);
} // namespace DMXManager

#endif
