#include "./debug_manager.h"
#include "../../audio/audio_analyzer.h"

namespace DebugManager
{
void initializeSerial()
{
  Serial.begin(SWSERIAL_BAUD);
  if (WAIT_FOR_SERIAL == true)
  {
    while (!Serial)
      ;
  }
}

void printStartupInfo(uint8_t stage)
{
  switch (stage)
  {
  case 0:
    static unsigned long startTime = millis();
    Serial.println();
    Serial.print(DEVICE_NAME);
    Serial.print(" ");
    Serial.print(PRODUCT_VERSION);
    Serial.println();

    Serial.print(PRODUCT_SHORT_DESCRIPTION);
    Serial.println();

    Serial.print("Designed by Drew André in Boston, MA - ");
    Serial.print(CURRENT_DATE);
    Serial.println();

    Serial.print("www.drew-andre.com");
    Serial.println();

    break;

  case 1:
    static unsigned long totalTime = millis() - startTime;
    Serial.println();
    Serial.print(DEVICE_NAME);
    Serial.print(" configured in ");
    Serial.print(totalTime);
    Serial.print("ms\n");
    Serial.print("\n================= ");
    Serial.print(DEVICE_NAME);
    Serial.print(" MAIN APPLICATION LOOP =================\n");
    break;
  }
}

void printSystemPerformanceEveryNSeconds(int seconds)
{
  static long loops = 0;

  loops++;

  Serial.println();

  // print MCU speed
  Serial.print("CPU speed (approx):\t\t");
  Serial.print(loops);
  Serial.print("/second");
  Serial.println();
  loops = 0;
}
} // namespace DebugManager