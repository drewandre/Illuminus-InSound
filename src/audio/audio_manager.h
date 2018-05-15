// #include <Audio.h>

//
// #include <env.h>

// // ---------------------- SGTL5000 config -------------------------- //
// #ifdef RN52_ANALOG_OUTPUT // analog audio input from SGTL5000
// int AUDIO_IN = AUDIO_INPUT_LINEIN;
// AudioInputI2S audioInput;
//
// // AudioOutputI2S       audioOutput; // SGTL5000 headphones & line-out
// // AudioConnection      patchCord1(audioInput, 0, audioOutput, 0);
// // AudioConnection      patchCord2(audioInput, 1, audioOutput, 1);
// #else // I2S audio input from RN52
// AudioInputI2Sslave audioInput;
// #endif // ifdef RN52_ANALOG_OUTPUT
//
// AudioAnalyzeFFT1024 fftL;
// AudioAnalyzeFFT1024 fftR;
// AudioConnection     patchCord3(audioInput, 0, fftL, 0);
// AudioConnection     patchCord4(audioInput, 1, fftR, 0);
//
// #ifdef PLAY_TONE_SWEEP_ON_STARTUP
// AudioSynthToneSweep tone_sweep;
// AudioConnection     patchCord5(tone_sweep, 0, audioOutput, 0);
// AudioConnection     patchCord6(tone_sweep, 0, audioOutput, 1);
// #endif // ifdef PLAY_TONE_SWEEP_ON_STARTUP
//
// AudioControlSGTL5000 SGTL5000;
