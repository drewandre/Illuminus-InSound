#ifndef ANIMATION_GENERATOR_H
#define ANIMATION_GENERATOR_H

#include "../audio/audio_analyzer.h"

extern CRGB colors[NUM_FIXTURES];

namespace AnimationGenerator
{
void mirrorFFTLeft(void);
void mapFFTStereo(void);
void mapFFTLeft(void);
void fadeFixturesToBlack(void);
void colorFade(void);
} // namespace AnimationGenerator

#endif
