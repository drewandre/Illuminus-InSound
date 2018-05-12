#include <led_effects.h>

void mode() {

#ifdef FIXED_LED_EFFECT
  effect = effect_fixed_num;
#endif

#ifdef DEMO_CYCLE
 EVERY_N_SECONDS(10) {
   effect++;
   if (effect > NUM_MODES) {
     effect = 0;
   }
 }
#endif

  switch (0) {
  // switch (effect) {
    case 0:
      //ambient_twelve();
      // fill_solid(leds, NUM_LEDS, CRGB::Black);
      // print_fft();
      break;
    case 1:
      // raw_audio_fftLeft();
      break;
    case 2:
      mapFFTLeft();
      break;
    case 3:
      // flex_fftLeft();
      break;
    case 4:
      // radiate_left();
      break;
    default:
      // effect = 0;
      break;
  }
}
