#ifndef AUDIO_ANALYZER_H
#define AUDIO_ANALYZER_H

#include "../config/config.h"

extern float levelsL[NUM_BANDS];
extern float levelsR[NUM_BANDS];
extern float levelsMono[NUM_BANDS];
extern float scaledLevelsL[NUM_BANDS];
extern float scaledLevelsR[NUM_BANDS];

namespace AudioAnalyzer
{
void initialize(void);
void readFFTStereo(bool createMonoArray);
void readFFTLeft(void);
} // namespace AudioAnalyzer

#endif
