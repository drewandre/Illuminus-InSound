#include <macros.h>

// # define WAIT_FOR_FFT_AVAILABILITY

// ---------------------- SGTL5000 config -------------------------- //
#if RN52_ANALOG_OUTPUT == true // analog audio input from SGTL5000
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

extern const AudioControlSGTL5000 SGTL5000;
