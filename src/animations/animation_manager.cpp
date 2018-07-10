#include "../bluetooth/bluetooth_manager.h"
#include "./animation_generator.h"

#if (DEBUG == true)
# include "../helpers/debug_manager/debug_manager.h"
#endif

#include "../macros.h"

/*======================*/
/*  external variables  */
uint8_t currentAnimation;
bool    calculateScaledFFT;

/*======================*/

namespace AnimationManager {
void runTask() {
#if FIXED_ANIMATION_INDEX == true
  currentAnimation = FIXED_ANIMATION_INDEX;
#endif

#if CYCLE_THROUGH_ANIMATIONS == true
  EVERY_N_SECONDS(SECONDS_PER_DEMO_ANIMATION) {
    currentAnimation++;

    if (currentAnimation > NUM_ANIMATIONS) currentAnimation = 0;
  }
#endif

  switch (currentAnimation) {
  case 0:
    AnimationGenerator::mapFFTLeft();
    break;

  case 1:

    // AnimationGenerator::mapFFTLeft();
    break;

  default:
    currentAnimation = 0;
    break;
  }
}
}
