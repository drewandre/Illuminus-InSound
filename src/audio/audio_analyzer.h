#ifndef AUDIO_ANALYZER_H
#define AUDIO_ANALYZER_H

#include "../macros.h"

extern AudioAnalyzeFFT1024 fftL;
extern AudioAnalyzeFFT1024 fftR;

extern uint16_t fftBins[NUM_BANDS];
extern uint8_t  levelsL[NUM_BANDS];
extern uint8_t  levelsR[NUM_BANDS];
extern uint8_t  scaledLevelsL[NUM_BANDS];
extern uint8_t  scaledLevelsR[NUM_BANDS];

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
