#ifndef ANIMATION_GENERATOR_H
#define ANIMATION_GENERATOR_H

#include "../audio/audio_analyzer.h"

extern CRGB colors[NUM_FIXTURES];

namespace AnimationGenerator
{
void mapFFTMono(void);
void mapFFTStereo(void);
void fadeFixturesToBlack(void);
void colorFade(void);
} // namespace AnimationGenerator

#endif
