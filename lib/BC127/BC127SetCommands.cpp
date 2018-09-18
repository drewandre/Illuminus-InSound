#include "BC127.h"

BC127::opResult BC127::enableGPIOControl()
{
  static BC127::opResult result = stdSetParam("GPIO_CONFIG", "ON 0");
#if DEBUG == true
  static String summary = "Enabling GPIO control..." + commandResult(result) + "\r";
  Serial.print(summary);
#endif
  return result;
}

BC127::opResult BC127::disableGPIOControl()
{
  static BC127::opResult result = stdSetParam("GPIO_CONFIG", "OFF 8");
#if DEBUG == true
  static String summary = "Disabling GPIO control..." + commandResult(result) + "\r";
  Serial.print(summary);
#endif
  return result;

  // return stdSetParam("GPIO_CONFIG", "OFF 080");
  // return stdCmd("SET GPIO_CONFIG=OFF 8");
}

BC127::opResult BC127::enableAutoData(bool shouldReboot)
{
  static BC127::opResult result = stdSetParam("AUTO_DATA", AUTO_DATA);

#if DEBUG == true
  static String summary = "Enabling auto data mode on SPP and BLE connections..." + commandResult(result) + "\r";
  Serial.print(summary);
#endif

  if (shouldReboot) {
    reset();
  }

  return result;
}

BC127::opResult BC127::enableAutoConn(bool shouldReboot)
{
  static BC127::opResult result = stdSetParam("AUTOCONN", AUTOCONN);

#if DEBUG == true
  static String summary = "Enabling auto connection on startup..." + commandResult(result) + "\r";
  Serial.print(summary);
#endif

  if (shouldReboot) {
    reset();
  }

  return result;
}

BC127::opResult BC127::enableHDAudio()
{
  static BC127::opResult result = stdSetParam("CODEC", "3");

#if DEBUG == true
  static String summary = "Enabling HD audio streaming..." + commandResult(result) + "\r";
  Serial.print(summary);
#endif
  return result;
}

BC127::opResult BC127::disableAdvertisingOnStartup()
{
  static BC127::opResult result = stdSetParam("BT_STATE_CONFIG", "0 0");

#if DEBUG == true
  static String summary = "Disabling advertising on startup..." + commandResult(result) + "\r";
  Serial.print(summary);
#endif
  return result;
}


BC127::opResult BC127::disableiOSBatteryIndicator()
{
  static BC127::opResult result = stdSetParam("ENABLE_BATT_IND", "OFF");
#if DEBUG == true
  static String summary = "Disabling iOS battery indicator..." + commandResult(result) + "\r";
  Serial.print(summary);
#endif
  return result;
}

BC127::opResult BC127::disableAdvertising()
{
  static BC127::opResult result = stdSetParam("BLE_CONFIG", "0 OFF 40 ON");

#if DEBUG == true
  static String summary = "Disabling advertising..." + commandResult(result) + "\r";
  Serial.print(summary);
#endif
  return result;
}

BC127::opResult BC127::setName(String name, bool shouldReboot)
{
  // enterCommandMode();

  static BC127::opResult result = stdSetParam("NAME", name);

#if DEBUG == true
  static String summary = "Setting device name to " + String(name) + "..." + commandResult(result) + "\r";
  Serial.print(summary);
#endif

  if (shouldReboot) {
    reset();
  } else {
    // stdCmd("ENTER_DATA_MODE 14");
    // exitCommandMode();
  }

  return result;
}

BC127::opResult BC127::setShortName(String name, bool shouldReboot)
{
  static BC127::opResult result = stdSetParam("NAME_SHORT", name);

#if DEBUG == true
  static String summary = "Setting device short name to " + String(name) + "..." + commandResult(result) + "\r";
  Serial.print(summary);
#endif

  if (shouldReboot) {
    reset();
  }

  return result;
}

BC127::opResult BC127::setMaxNumOfReconnectionAttempts(int maxNum, bool shouldReboot)
{
  static BC127::opResult result = stdSetParam("MAX_REC", maxNum);

#if DEBUG == true
  static String summary = "Setting max number of reconnect attempts to " + String(maxNum) + "..." + commandResult(result) + "\r";
  Serial.print(summary);
#endif

  if (shouldReboot) {
    reset();
  }

  return result;
}

BC127::opResult BC127::setUARTConfig()
{
  static BC127::opResult result = stdSetParam("UART_CONFIG", "9600 OFF 0");

#if DEBUG == true
  static String summary = "Setting UART baudrate to 9600 and enabling flow control..." + commandResult(result) + "\r";
  Serial.print(summary);
#endif
  return result;
}
