#include <macros.h>

// # define WAIT_FOR_FFT_AVAILABILITY

// ---------------------- SGTL5000 config -------------------------- //
#ifdef RN52_ANALOG_OUTPUT // analog audio input from SGTL5000
// # define AUDIO_IN AUDIO_INPUT_LINEIN
AudioInputI2S audioInput;

// AudioOutputI2S       audioOutput; // SGTL5000 headphones & line-out
// AudioConnection      patchCord1(audioInput, 0, audioOutput, 0);
// AudioConnection      patchCord2(audioInput, 1, audioOutput, 1);
#else // I2S audio input from RN52
AudioInputI2Sslave audioInput;
#endif // ifdef RN52_ANALOG_OUTPUT

extern struct AudioAnalyzeFFT1024 fftL;
extern struct AudioAnalyzeFFT1024 fftR;
const AudioConnection patchCord3(audioInput, 0, fftL, 0);
const AudioConnection patchCord4(audioInput, 1, fftR, 0);

#ifdef PLAY_TONE_SWEEP_ON_STARTUP
extern struct AudioSynthToneSweep tone_sweep;
const AudioConnection patchCord5(tone_sweep, 0, audioOutput, 0);
const AudioConnection patchCord6(tone_sweep, 0, audioOutput, 1);
#endif // ifdef PLAY_TONE_SWEEP_ON_STARTUP

extern struct AudioControlSGTL5000 SGTL5000;
