#ifndef ANIMATION_GENERATOR_H
#define ANIMATION_GENERATOR_H

#include "../leds/led_manager.h"

#include "../audio/audio_analyzer.h"

using namespace AudioAnalyzer;
using namespace LedManager;

namespace AnimationGenerator {
void mapFFTMono();
void flexFFTStereo();
void fractionalFlexFFTStereo();
void radiateStereo();
void rainbow();
}

#endif
