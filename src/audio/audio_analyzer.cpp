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
  static unsigned long startTime = millis();
  Serial.print("\n================== INITIALIZING MSGEQ7 ==================\n");

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

  static unsigned long totalTime = millis() - startTime;

  Serial.print("Audio Initialized:\t");
  Serial.print(totalTime);
  Serial.print("ms");
  Serial.println();
  Serial.print("-----------------------------------------------------------------\n");
  Serial.println();
}

void readFFTStereo(float smoothing,
                   bool calculateScaledFFT,
                   bool print)
{
  static float currentLeftAmp, currentRightAmp;
  static float previousLeftAmp, previousRightAmp;

  // static float mappedLeftAmp, mappedRightAmp;
  // static float leftFactor, rightFactor;
  // static float leftVolume, rightVolume;

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
    if (print)
    {
      Serial.print(levelsL[band]);
      Serial.print("\t");
    }

    previousRightAmp = levelsR[band];
    currentRightAmp = analogRead(AUDIO_RIGHT_PIN);
    currentRightAmp = constrain(currentRightAmp, FILTER_MIN, FILTER_MAX);
    currentRightAmp = map(currentRightAmp, FILTER_MIN, FILTER_MAX, 0, 255);
    levelsR[band] = previousRightAmp + (currentRightAmp - previousRightAmp) * SMOOTHING;

    digitalWrite(MSGEQ7_STROBE_PIN, HIGH);
    delayMicroseconds(1);
  }
  if (print)
  {
    Serial.println();
  }
}
} // namespace AudioAnalyzer
