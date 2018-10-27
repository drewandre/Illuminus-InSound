#include "./dmx_manager.h"

#include <vector>
using std::vector;
vector<Sixbar> sixbar;

namespace DMXManager
{
void initialize()
{
  static unsigned long startTime = millis();
  Serial.print("\n======================= INITIALIZING DMX =======================\n");

  pinMode(DMX_RX_EN_PIN, OUTPUT);
  digitalWrite(DMX_RX_EN_PIN, HIGH);

  DmxSimple.usePin(DMX_TX_PIN);
  DmxSimple.maxChannel(DMX_MAX_CHANNELS);

  initializeFixtures();
  blackout();

  static unsigned long totalTime = millis() - startTime;
  Serial.print("Leds Initialized:\t");
  Serial.print(totalTime);
  Serial.print("ms");
  Serial.println();
  Serial.print("-----------------------------------------------------------------\n");
}

void initializeFixtures()
{
  static uint16_t startingDMXAddress;

  sixbar.reserve(NUM_FIXTURES);

  for (uint8_t i = 0; i < NUM_FIXTURES; i++)
  {
    startingDMXAddress = 1 + (i * 6);
    sixbar.push_back(Sixbar(startingDMXAddress));
  }
}

void displayAnimation()
{
  for (int i = 0; i < NUM_FIXTURES; i++)
  {
    sixbar[i].draw(colors[i]);
  }
  // sixbar[0].draw(colors[0]);
  // sixbar[0].draw(colors[6]);
}

void blackout()
{
  for (int i = 0; i < NUM_FIXTURES; i++)
  {
    sixbar[i].draw(CRGB::Black);
  }
}

} // namespace DMXManager