#ifndef ANIMATION_MANAGER_H
#define ANIMATION_MANAGER_H

#include "../config/config.h"

extern uint8_t currentAnimation;

namespace AnimationManager
{
void runTask(void);
void changeAnimation(uint8_t animationId);
} // namespace AnimationManager

#endif
