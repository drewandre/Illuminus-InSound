#include "BC127.h"

BC127::opResult BC127::enableConnectableAndDiscoverable()
{
  static BC127::opResult result = stdCmd("BT_STATE ON ON");

#if DEBUG == true
  static String summary = "Setting connectable and discoverable to true..." + commandResult(result) + "\r";
  Serial.print(summary);
#endif
  return result;
}

BC127::opResult BC127::resetPIO4()
{
  static BC127::opResult result = stdCmd("PIO 4 OFF");

#if DEBUG == true
  static String summary = "Resetting PIO 4..." + commandResult(result) + "\r";
  Serial.print(summary);
#endif
  return result;
}
