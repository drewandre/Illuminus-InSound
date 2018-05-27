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

#if DEBUG == true
  rn52.printVersion();
  rn52.printStatus();
      #endif

#if BT_CHECK_IF_FACTORY_SETTINGS == true

  if (rn52.factorySettings(DEVICE_NAME)) { // checks device name
#endif
  rn52.setDeviceName(DEVICE_NAME);
  rn52.setDeviceType(BT_DEVICE_TYPE);      // sets device name loudspeaker?
  rn52.muteTones();
  rn52.setAnalogAudioOutput();
  rn52.setMaxSpeakerGain();
#if BT_CHECK_IF_FACTORY_SETTINGS == true
}

#endif
#if DEBUG == true
  static unsigned long totalTime = millis() - startTime;
  Serial << "RN52 Initialized:\t" << totalTime << "ms" << "\n\n";
  Serial << "-----------------------------------------------------------------\n";
#endif
}

void printConfig() {
  rn52.printStatus();
}

void testVar(int var) {
  rn52.testVariable(var);
}
}
