#ifndef ANIMATION_MANAGER_H
#define ANIMATION_MANAGER_H

#include <macros.h>

extern bool calculateScaledFFT;
extern uint8_t currentAnimation;

namespace AnimationManager {
void runTask(void);
}

#endif
