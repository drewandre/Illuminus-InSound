#include "./audio_manager.h"

/*======================*/
/*  external variables  */
#if RN52_ANALOG_OUTPUT == true // analog audio input from SGTL5000
AudioInputI2S audioInput;

// AudioOutputI2S       audioOutput; // SGTL5000 headphones & line-out
// AudioConnection      patchCord1(audioInput, 0, audioOutput, 0);
// AudioConnection      patchCord2(audioInput, 1, audioOutput, 1);
#else // I2S audio input from RN52
AudioInputI2Sslave audioInput;
#endif // ifdef RN52_ANALOG_OUTPUT

AudioControlSGTL5000 SGTL5000;

/*======================*/

namespace AudioManager {
void initialize() {
#if DEBUG == true
  static unsigned long startTime = millis();

  Serial <<
    "\n===================== INITIALIZING SGTL5000 =====================\n";
#endif

  AudioMemory(20);

  SGTL5000.enable();
  SGTL5000.inputSelect(AUDIO_INPUT_LINEIN);
  SGTL5000.lineInLevel(15);
  SGTL5000.volume(0.5);

#if DEBUG == true
  static unsigned long totalTime = millis() - startTime;

  Serial << "Audio Initialized:\t" << totalTime << "ms" << endl;
  Serial << "-----------------------------------------------------------------\n";
#endif
}
}
