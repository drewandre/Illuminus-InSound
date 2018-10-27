#include "./animation_generator.h"

#if DEBUG == true
#include "../helpers/debug_manager/debug_manager.h"
#endif

#include "../config/config.h"

/*======================*/
/*  external variables  */
uint8_t currentAnimation = 0;
bool calculateScaledFFT;

/*======================*/

namespace AnimationManager
{
void runTask()
{
#if FIXED_ANIMATION == true
  currentAnimation = FIXED_ANIMATION_INDEX;
#endif

  switch (currentAnimation)
  {
  case 0:
    AnimationGenerator::mapFFTMono();
    break;
  default:
    currentAnimation = 0;
    break;
  }
}

void changeAnimation(uint8_t animationId)
{
  currentAnimation = animationId;
}
} // namespace AnimationManager
