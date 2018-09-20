#ifndef AUDIO_ANALYZER_H
#define AUDIO_ANALYZER_H

#include "../macros.h"

extern AudioAnalyzeFFT1024 fftL;
extern AudioAnalyzeFFT1024 fftR;

extern uint16_t fftBins[NUM_BANDS];
extern float  levelsL[NUM_BANDS];
extern float  levelsR[NUM_BANDS];
extern float  scaledLevelsL[NUM_BANDS];
extern float  scaledLevelsR[NUM_BANDS];

namespace AudioAnalyzer {
void    initializeFFT(void);
float   getFFTBins(void);
float   FindE(int bands,
              int bins);
bool    readFFT(float smoothing,
                bool  stereo,
                bool  calculateScaledFFT);
uint8_t averageFFTPortion(uint8_t *array,
                          uint16_t len,
                          uint16_t startIndex,
                          uint16_t endIndex);
}

#endif
