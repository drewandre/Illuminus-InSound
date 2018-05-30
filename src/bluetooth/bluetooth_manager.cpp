#include "./bluetooth_manager.h"

/*======================*/
/*  external variables  */
RN52 rn52(RN52_CMD_PIN, &RN52_SERIAL, ECHO_BT_MODULE);
BM64 bm64(BM64_UART_TX_IND, &BM64_SERIAL, ECHO_BT_MODULE);

/*======================*/

namespace BluetoothManager {
void initialize() {
#if DEBUG == true
  static unsigned long startTime = millis();
  Serial.print(
    "\n======================= INITIALIZING RN52 =======================\n");
#endif
  rn52.enable();
  attachInterrupt(digitalPinToInterrupt(RN52_GPI02_PIN), handleRN52Event,
                  FALLING);

#if DEBUG == true
  rn52.printVersion();
  rn52.printConfig();
#endif

#if BT_CHECK_IF_FACTORY_SETTINGS == true

  if (rn52.factorySettings(PRODUCT_NAME)) { // checks device name
#endif
  rn52.setDeviceName(PRODUCT_NAME);
  rn52.setDeviceType(BT_DEVICE_TYPE);       // sets device name loudspeaker?
  rn52.muteTones();
  rn52.setAnalogAudioOutput();
  rn52.setMaxSpeakerGain();
#if BT_CHECK_IF_FACTORY_SETTINGS == true
}

#endif
#if DEBUG == true
  Serial.print("GPIO pin #"); Serial.print(RN52_GPI02_PIN); Serial.println(
    " initialized as an RN52 event interrupt routine.");

  static unsigned long totalTime = millis() - startTime;
  Serial << "RN52 Initialized:\t" << totalTime << "ms" << "\n";
  Serial << "-----------------------------------------------------------------\n";
#endif
}

void handleRN52Event() {
  // rn52.printConnectionStatus();
  Serial.println(rn52.status(), HEX);
}

void printConfig() {
  rn52.printConfig();
}

String getVolume() {
  return rn52.getVolume();
}

void SPPTask() {
  rn52.readSerial();
}

void echo() {
  char *response = rn52.readSerial();

  if (response) {
    Serial.println(response);
  }
}
}
