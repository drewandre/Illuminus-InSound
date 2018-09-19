#include "./bluetooth_manager.h"
#include "../animations/animation_manager.h"

/*======================*/
/*  external variables  */
BC127 bc127(BC127_CMD_PIN, BC127_GPIO_0_PIN, &BC127_SERIAL, ECHO_BT_MODULE, DEVICE_NAME);

/*======================*/

String SPPBuffer = "";

namespace BluetoothManager {
void initialize() {
#if DEBUG == true
  static unsigned long startTime = millis();
  Serial.print(
    "\n======================= INITIALIZING BC127 ======================\n");
#endif

  bc127.enable();

#if DEBUG == true
  static unsigned long totalTime = millis() - startTime;
  Serial << "BC127 Initialized:\t" << totalTime << "ms" << "\n";
  Serial << "-----------------------------------------------------------------\n";
#endif
}

void enableBLEAdvertising() {
  bc127.stdCmd("BT_STATE ON ON");
  static int result = bc127.stdSetParam("BLE_CONFIG", "0 ON 40 ON");

#if DEBUG == true
  Serial.println("Enabling advertising..." + bc127.commandResult(result));
#endif
}

void enterCommandMode() {
  bc127.enterCommandMode();
}

void exitCommandMode() {
  bc127.exitCommandMode();
}

void handleBC127ConnectionEvent() {
  Serial.println("CONNECTION MADE");
  // bc127.stdCmd("STATUS");
}

void handleBC127Event() {
  Serial.println("Something really crazy happened");
}

void handleSPPData(String SPPBuffer) {
  enum params { EFFECT_NUMBER, NAME };

  uint8_t index = SPPBuffer.indexOf(":");
  if (index == -1) {
    return;
  }

  uint8_t category = SPPBuffer.substring(0, index).toInt();
  String param = SPPBuffer.substring(index + 1);

  switch(category) {
    case EFFECT_NUMBER:
      static uint8_t animation = param.toInt();
      AnimationManager::changeAnimation(animation);
      printChange("Animation changed to " + param);
      break;
    case NAME:
      bc127.setName(param, false);
      bc127.setShortName(param, false);
      printChange("Name changed to " + param);
      break;
  default: printChange("Unknown command: " + SPPBuffer);
  }
}

void printChange(String str) {
#if DEBUG == true
  Serial.print(str + "\r");
#endif
}

void listenAndHandleSPPData() {
  if (BC127_SERIAL.available() > 0) {
    SPPBuffer.concat(char(BC127_SERIAL.read()));

    if (SPPBuffer.endsWith('\r')) {
      SPPBuffer = SPPBuffer.remove(SPPBuffer.length() - 1);
      handleSPPData(SPPBuffer);
      SPPBuffer = "";
    }
  }
}
} // end namespace
