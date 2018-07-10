#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include "./audio_analyzer.h"

#include "../macros.h"

#if BC127_ANALOG_OUTPUT == true // analog audio input from SGTL5000
extern AudioInputI2S audioInput;

// AudioOutputI2S       audioOutput; // SGTL5000 headphones & line-out
// AudioConnection      patchCord1(audioInput, 0, audioOutput, 0);
// AudioConnection      patchCord2(audioInput, 1, audioOutput, 1);
#else // I2S audio input from BC127
extern AudioInputI2Sslave audioInput;
#endif // ifdef BC127_ANALOG_OUTPUT

extern AudioAnalyzeFFT1024 fftL;
extern AudioAnalyzeFFT1024 fftR;
const AudioConnection patchCord3(audioInput, 0, fftL, 0);
const AudioConnection patchCord4(audioInput, 1, fftR, 0);

extern AudioControlSGTL5000 SGTL5000;

namespace AudioManager {
void initialize(void);
void initializeFFT(void);
}

#endif
