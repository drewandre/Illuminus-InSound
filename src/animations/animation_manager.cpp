#include "./animation_generator.h"

#include <macros.h>

/*======================*/
/*  external variables  */
uint8_t currentAnimation;

/*======================*/

void animationManagerTask() {
#ifdef FIXED_ANIMATION_INDEX
  currentAnimation = FIXED_ANIMATION_INDEX;
#endif // ifdef FIXED_LED_EFFECT

#ifdef DEMO_CYCLE
  EVERY_N_SECONDS(SECONDS_PER_DEMO_ANIMATION) {
    currentAnimation++;

    if (currentAnimation > NUM_ANIMATIONS) currentAnimation = 0;
  }
#endif // ifdef DEMO_CYCLE

  switch (currentAnimation) {
  case 0:
    readFFTTest();

    // readBM64();

    // ambient_twelve();
    // fill_solid(leds, NUM_LEDS, CRGB::Black);
    // print_fft();
    break;

  case 1:

    // ambient_twelve();
    // fill_solid(leds, NUM_LEDS, CRGB::Black);
    // print_fft();
    break;

  case 2:

    // raw_audio_fftLeft();
    break;

  case 3:
    mapFFTLeft();
    break;

  case 4:

    // flex_fftLeft();
    break;

  case 5:

    // radiate_left();
    break;

  default:

    // effect = 0;
    break;
  }
}
