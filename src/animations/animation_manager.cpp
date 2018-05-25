#include "./animation_generator.h"
#if (DEBUG == true)
# include "../helpers/debug_functions.h"
#endif

#include <macros.h>

/*======================*/
/*  external variables  */
uint8_t currentAnimation;

/*======================*/

void animationManagerTask() {
#if FIXED_ANIMATION_INDEX == true
  currentAnimation = FIXED_ANIMATION_INDEX;
#endif

#if CYCLE_THROUGH_ANIMATIONS == true
  EVERY_N_SECONDS(SECONDS_PER_DEMO_ANIMATION) {
    currentAnimation++;

    if (currentAnimation > NUM_ANIMATIONS) currentAnimation = 0;
  }
#endif

#if (DEBUG == true) || (DEBUG_ANIMATIONS_ONLY == false)

  // debugging modes for bluetooth communication testing, audio sensitivity
  // adjustments, etc
  switch (currentAnimation) {
  case 0:

    // EVERY_N_SECONDS(5) {
    //   attemptToSendCommandToBM64();
    // }
    break;

  default:
    currentAnimation = 0;
    break;
  }

#else

  // LIVE or DEMO mode
  switch (currentAnimation) {
  case 0:
    mapFFTLeft();
    break;

  default:
    currentAnimation = 0;
    break;
  }
#endif
}
