#include <env.h>

bool readFFT(float smoothing,
             bool  stereo,
             bool  calculateScaledFFT);

uint8_t averageFFTPortion(uint8_t *array,
                          uint16_t len,
                          uint16_t startIndex,
                          uint16_t endIndex);
