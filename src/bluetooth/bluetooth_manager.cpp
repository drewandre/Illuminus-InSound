#include "./bluetooth_manager.h"

/*======================*/
/*  external variables  */
BC127 bc127(BC127_CMD_PIN, BC127_GPIO_0_PIN, &BC127_SERIAL, ECHO_BT_MODULE);

/*======================*/

String SPPBuffer = "";

namespace BluetoothManager {
void initialize() {
  pinMode(BC127_GPIO_0_PIN, INPUT);
  pinMode(BC127_GPIO_4_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(
                    BC127_GPIO_0_PIN), handleBC127ConnectionEvent,
                  CHANGE);

  attachInterrupt(digitalPinToInterrupt(
                    BC127_GPIO_4_PIN), handleBC127Event,
                  CHANGE);

#if DEBUG == true
  static unsigned long startTime = millis();
  Serial.print(
    "\n========================= INITIALIZING BC127 =========================\n");
#endif

  bc127.enable();

#if DEBUG == true
  static unsigned long totalTime = millis() - startTime;
  Serial << "BC127 Initialized:\t" << totalTime << "ms" << "\n";
  Serial << "-----------------------------------------------------------------\n";
#endif
}

void enableBLEAdvertising() {
#if DEBUG == true
  Serial << "Enabling advertising..." << endl;
#endif
  bc127.stdSetParam("BLE_CONFIG", "0 ON 40 ON");
}

void enterCommandMode() {
  bc127.enterCommandMode();
}

void exitCommandMode() {
  bc127.exitCommandMode();
}

void handleBC127ConnectionEvent() {
  Serial.println("CONNECTION MADE");
  bc127.stdCmd("STATUS");
}

void handleBC127Event() {
  Serial.println("Something really crazy happened");
}

void listenAndHandleSPPData() {
  if (BC127_SERIAL.available() > 0) {
    SPPBuffer.concat(char(BC127_SERIAL.read()));

    if (SPPBuffer.endsWith('\r')) {
      SPPBuffer = SPPBuffer.remove(SPPBuffer.length() - 1);
    #if DEBUG == true
      Serial << SPPBuffer << endl;
    #endif

      SPPBuffer = "";
    }
  }
}
} // end namespace
