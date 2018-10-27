#include "./animation_generator.h"

#include "../debug/debug_manager.h"
#include "../config/config.h"

/*======================*/
/*  external variables  */
uint8_t currentAnimation = 0;

/*======================*/

namespace AnimationManager
{
void runTask(void)
{
#if FIXED_ANIMATION == true
  currentAnimation = FIXED_ANIMATION_INDEX;
#endif

  switch (currentAnimation)
  {
  case 0:
    AnimationGenerator::mapFFTStereo();
    break;
  case 1:
    AnimationGenerator::flexFFTStereo();
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
