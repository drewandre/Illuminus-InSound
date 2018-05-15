#include <Audio.h>

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

// ---------------------- SGTL5000 config -------------------------- //
#ifdef RN52_ANALOG_OUTPUT // analog audio input from SGTL5000
int AUDIO_IN = AUDIO_INPUT_LINEIN;
extern AudioInputI2S audioInput;

// AudioOutputI2S       audioOutput; // SGTL5000 headphones & line-out
// AudioConnection      patchCord1(audioInput, 0, audioOutput, 0);
// AudioConnection      patchCord2(audioInput, 1, audioOutput, 1);
#else // I2S audio input from RN52
extern AudioInputI2Sslave audioInput;
#endif // ifdef RN52_ANALOG_OUTPUT

extern AudioAnalyzeFFT1024 fftL;
extern AudioAnalyzeFFT1024 fftR;
AudioConnection patchCord3(audioInput, 0, fftL, 0);
AudioConnection patchCord4(audioInput, 1, fftR, 0);

#ifdef PLAY_TONE_SWEEP_ON_STARTUP
extern AudioSynthToneSweep tone_sweep;
extern AudioConnection     patchCord5(tone_sweep, 0, audioOutput, 0);
extern AudioConnection     patchCord6(tone_sweep, 0, audioOutput, 1);
#endif // ifdef PLAY_TONE_SWEEP_ON_STARTUP

AudioControlSGTL5000 SGTL5000;
