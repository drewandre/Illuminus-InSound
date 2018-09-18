#include "BC127.h"

String BC127::getName()
{
  static String result = stdGetParam("NAME");

#if DEBUG == true
  static String summary = "NAME > " + result + "\r";
  Serial.print(summary);
#endif
  return result;
}

String BC127::getGPIOConfig()
{
  static String result = stdGetParam("GPIO_CONFIG");

#if DEBUG == true
  static String summary = "GPIO_CONFIG > " + result + "\r";
  Serial.print(summary);
#endif
  return result;
}

String BC127::getUARTConfig()
{
  static String result = stdGetParam("UART_CONFIG");

#if DEBUG == true
  static String summary = "UART_CONFIG > " + result + "\r";
  Serial.print(summary);
#endif
  return result;
}

String BC127::getBLEConfig()
{
  static String result = stdGetParam("BLE_CONFIG");

#if DEBUG == true
  static String summary = "BLE_CONFIG > " + result + "\r";
  Serial.print(summary);
#endif
  return result;
}