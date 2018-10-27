#include "./audio_analyzer.h"

/*======================*/
/*  external variables  */
float levelsL[NUM_BANDS];
float levelsR[NUM_BANDS];
float scaledLevelsL[NUM_BANDS];
float scaledLevelsR[NUM_BANDS];

/*======================*/

namespace AudioAnalyzer
{

void initialize()
{
#if DEBUG == true
  static unsigned long startTime = millis();
  Serial.print("\n================== INITIALIZING MSGEQ7 ==================\n");
#endif

  analogReference(DEFAULT);
  pinMode(MSGEQ7_RESET_PIN, OUTPUT);
  pinMode(MSGEQ7_STROBE_PIN, OUTPUT);
  pinMode(AUDIO_LEFT_PIN, INPUT);
  pinMode(AUDIO_RIGHT_PIN, INPUT);
  digitalWrite(MSGEQ7_RESET_PIN, LOW);
  digitalWrite(MSGEQ7_STROBE_PIN, LOW);
  // Reset MSGEQ7
  digitalWrite(MSGEQ7_RESET_PIN, HIGH);
  delay(1);
  digitalWrite(MSGEQ7_RESET_PIN, LOW);
  digitalWrite(MSGEQ7_STROBE_PIN, HIGH);
  delay(1);

#if DEBUG == true
  static unsigned long totalTime = millis() - startTime;

  Serial.print("Audio Initialized:\t");
  Serial.print(totalTime);
  Serial.print("ms");
  Serial.println();
  Serial.print("-----------------------------------------------------------------\n");
  Serial.println();
#endif
}

void readFFTStereo(float smoothing,
                   bool calculateScaledFFT,
                   bool print)
{
  static float previousLeftAmp, previousRightAmp, mappedLeftAmp,
      mappedRightAmp;
  static float leftVolume, rightVolume, currentLeftAmp, currentRightAmp,
      leftFactor, rightFactor;

  digitalWrite(MSGEQ7_RESET_PIN, HIGH);
  digitalWrite(MSGEQ7_RESET_PIN, LOW);
  delayMicroseconds(1);

  for (uint8_t band = 0; band < NUM_BANDS; band++)
  {
    digitalWrite(MSGEQ7_STROBE_PIN, LOW);
    delayMicroseconds(36);

    previousLeftAmp = levelsL[band];
    currentLeftAmp = analogRead(AUDIO_LEFT_PIN);
    currentLeftAmp = constrain(currentLeftAmp, FILTER_MIN, FILTER_MAX);
    currentLeftAmp = map(currentLeftAmp, FILTER_MIN, FILTER_MAX, 0, 255);
    levelsL[band] = previousLeftAmp + (currentLeftAmp - previousLeftAmp) * SMOOTHING;
    Serial.print(currentLeftAmp);
    Serial.print("\t");

    previousRightAmp = levelsR[band];
    currentRightAmp = analogRead(AUDIO_RIGHT_PIN);
    currentRightAmp = constrain(currentRightAmp, FILTER_MIN, FILTER_MAX);
    currentRightAmp = map(currentRightAmp, FILTER_MIN, FILTER_MAX, 0, 255);
    levelsR[band] = previousRightAmp + (currentRightAmp - previousRightAmp) * SMOOTHING;

    digitalWrite(MSGEQ7_STROBE_PIN, HIGH);
    delayMicroseconds(1);
  }
  Serial.println();
}

uint8_t averageFFTPortion(uint8_t *array,
                          uint16_t len,
                          uint16_t startIndex,
                          uint16_t endIndex)
{
  static uint16_t sum, portion;

  sum = 0;
  portion = endIndex - startIndex;

  for (uint16_t i = startIndex; i < endIndex; i++)
  {
    sum += array[i];
  }
  return sum / portion;
}
} // namespace AudioAnalyzer
