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
    EVERY_N_MILLISECONDS(AUDIO_FRAMES_PER_SECOND)
    {
      AudioAnalyzer::readFFTStereo(false);
    }
    AnimationGenerator::mapFFTStereo();
    AnimationGenerator::fadeFixturesToBlack();
    break;
  case 1:
    EVERY_N_MILLISECONDS(AUDIO_FRAMES_PER_SECOND)
    {
      AudioAnalyzer::readFFTLeft();
    }
    AnimationGenerator::mirrorFFTLeft();
    AnimationGenerator::fadeFixturesToBlack();
    break;
  case 2:
    EVERY_N_MILLISECONDS(AUDIO_FRAMES_PER_SECOND)
    {
      AudioAnalyzer::readFFTLeft();
    }
    AnimationGenerator::mapFFTLeft();
    AnimationGenerator::fadeFixturesToBlack();
    AnimationGenerator::customMappingForPeobody();
    break;
  case 3:
    AnimationGenerator::colorFade();
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
