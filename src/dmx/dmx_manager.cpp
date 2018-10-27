#include "./dmx_manager.h"

namespace DMXManager
{
void initialize()
{
#if DEBUG == true
  static unsigned long startTime = millis();
  Serial.print("\n======================= INITIALIZING DMX =======================\n");
#endif

  /* The most common pin for DMX output is pin 3, which DmxSimple
  ** uses by default. If you need to change that, do it here. */
  pinMode(DMX_RX_EN_PIN, OUTPUT);
  digitalWrite(DMX_RX_EN_PIN, HIGH);
  DmxSimple.usePin(DMX_TX_PIN);

  /* DMX devices typically need to receive a complete set of channels
  ** even if you only need to adjust the first channel. You can
  ** easily change the number of channels sent here. If you don't
  ** do this, DmxSimple will set the maximum channel number to the
  ** highest channel you DmxSimple.write() to. */
  DmxSimple.maxChannel(DMX_MAX_CHANNELS);

#if DEBUG == true
  static unsigned long totalTime = millis() - startTime;
  Serial.print("Leds Initialized:\t");
  Serial.print(totalTime);
  Serial.print("ms");
  Serial.println();
  Serial.print("-----------------------------------------------------------------\n");
#endif
}
void show() {}
} // namespace DMXManager