//void mode() {
//
//  //check_serial_input();
//
//#ifdef effect_fixed
//  effect = effect_fixed_num;
//#endif
//
//#ifdef demo_cycle
//  EVERY_N_SECONDS(10) {
//    effect++;
//    if (effect > num_modes) {
//      effect = 0;
//    }
//  }
//#endif
//
//  switch (effect) {
//    case 0:
//      //ambient_twelve();
//      fill_solid(leds, NUM_LEDS, CRGB::Black);
//      print_fft();
//      break;
//    case 1:
//      raw_audio_fft_left();
//      break;
//    case 2:
//      map_fft_left();
//      break;
//    case 3:
//      flex_fft_left();
//      break;
//    case 4:
//      radiate_left();
//      break;
//    default:
//      effect = 0;
//      break;
//  }
//
//}
//

