#include "./audio_analyzer.h"

/*======================*/
/*  external variables  */
float levelsL[NUM_BANDS];
float levelsR[NUM_BANDS];
float scaledLevelsL[NUM_BANDS];
float scaledLevelsR[NUM_BANDS];

/*======================*/

float smoothing[NUM_FIXTURES_PER_CHANNEL] = {SMOOTHING_ARR};

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

void readFFTStereo(void)
{
  static float currentLeftAmp, currentRightAmp;
  static float previousLeftAmp, previousRightAmp;
#if MONO_SUM_LOWEST_BIN == true
  static float monoBassSum;
#endif

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
    currentLeftAmp = map(currentLeftAmp, FILTER_MIN, FILTER_MAX, 0, AUDIO_BAND_MAX_AMPLITUDE);
    levelsL[band] = previousLeftAmp + (currentLeftAmp - previousLeftAmp) * smoothing[band];
#if PRINT_FFT
    Serial.print(levelsL[band]);
    Serial.print("\t");
#endif

    previousRightAmp = levelsR[band];
    currentRightAmp = analogRead(AUDIO_RIGHT_PIN);
    currentRightAmp = constrain(currentRightAmp, FILTER_MIN, FILTER_MAX);
    currentRightAmp = map(currentRightAmp, FILTER_MIN, FILTER_MAX, 0, AUDIO_BAND_MAX_AMPLITUDE);
    levelsR[band] = previousRightAmp + (currentRightAmp - previousRightAmp) * smoothing[band];

    digitalWrite(MSGEQ7_STROBE_PIN, HIGH);
    delayMicroseconds(1);
  }
#if MONO_SUM_LOWEST_BIN == true
  monoBassSum = (levelsL[0] + levelsR[0]) * 0.5;
  levelsL[0] = monoBassSum;
  levelsR[0] = monoBassSum;
#endif
#if PRINT_FFT
  Serial.println();
#endif
}

void readFFTMono(void)
{
  static float currentLeftAmp, previousLeftAmp;

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
    currentLeftAmp = map(currentLeftAmp, FILTER_MIN, FILTER_MAX, 0, AUDIO_BAND_MAX_AMPLITUDE);
    levelsL[band] = previousLeftAmp + (currentLeftAmp - previousLeftAmp) * smoothing[band];
#if PRINT_FFT
    Serial.print(levelsL[band]);
    Serial.print("\t");
#endif

    digitalWrite(MSGEQ7_STROBE_PIN, HIGH);
    delayMicroseconds(1);
  }
#if PRINT_FFT
  Serial.println();
#endif
}

} // namespace AudioAnalyzer
