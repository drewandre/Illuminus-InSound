#include <env.h>

bool readFFT(float smoothing,
             bool  stereo,
             bool  calculateScaledFFT);

uint8_t averageFFTPortion(uint8_t *array,
                          uint16_t len,
                          uint16_t startIndex,
                          uint16_t endIndex);

extern uint16_t fftBins[NUM_BANDS];
extern uint8_t  levelsL[NUM_BANDS];
extern uint8_t  levelsR[NUM_BANDS];
extern uint8_t  scaledLevelsL[NUM_BANDS];
extern uint8_t  scaledLevelsR[NUM_BANDS];
