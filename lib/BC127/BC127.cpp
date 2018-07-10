#include "BC127.h"

#define TIMEOUT_DELAY 2000
#define BC127_GPIO_0 35
String DEVICE_NAME = "PALETTE";
#define DEBUG true

BC127::BC127(int             commandPinIn,
             int             gpioZeroIn,
             HardwareSerial *serial,
             bool            echoBC127) {
  echoSerial = echoBC127;
  commandPin = commandPinIn;

  // gpioZeroIn         = 35;
  _serialPort        = serial;
  bufferWritingIndex = 0;
  bufferReadingIndex = 0;
  _numAddresses      = -1;
}

BC127::~BC127() {}

void BC127::enable() {
  int result;

  pinMode(commandPin,   OUTPUT);
  pinMode(BC127_GPIO_0, INPUT);
  digitalWrite(BC127_GPIO_0, LOW);

  _serialPort->begin(uartBaud);

#if DEBUG == true
  Serial.println("Enabling BC127 hardware serial...OK");
#endif

  result = disableGPIOControl();
#if DEBUG == true
  Serial.println("Disabling GPIO control..." + commandResult(result));
#endif

  String res = getGPIOConfig();
#if DEBUG == true
  Serial.println("GPIO_CONFIG..." + res);
#endif

  result = disableAdvertising();
#if DEBUG == true
  Serial.println("Disabling advertising..." + commandResult(result));
#endif

  result = setName("PALETTE");
#if DEBUG == true
  Serial.println("Setting device name to " + DEVICE_NAME + "..." + commandResult(
                   result));
#endif

  write();
  reset();
}

String BC127::commandResult(int result) {
  if (result) {
    return "OK";
  } else {
    return "ERROR";
  }
  return "OK";
}

void BC127::enterCommandMode()
{
  // digitalWrite(commandPin, LOW);
  Serial.print("\n\nEntering command mode + LEDS SHOULD TURN ON...");

  // _serialPort->flush();
  delay(400);
  _serialPort->print("$$$$");
  delay(400);


  // delay(100);
  // _serialPort->print("$$$");
  // delay(1000);
  // _serialPort->print("SET ENABLE_LED=ON\r");
  stdCmd("SET ENABLE_LED=ON");
  Serial.println("And should be seeing status returned....");
  stdCmd("STATUS");
}

void BC127::exitCommandMode()
{
  // Serial.println("Driving command pin (" + String(
  //                  commandPin) + ") HIGH to enter data mode");
  // digitalWrite(commandPin, HIGH); // enter data mode

  Serial.print("\n\nEntering data mode on channel 14 + LEDS SHOULD TURN OFF...");
  _serialPort->print("SET ENABLE_LED=OFF\r");
  stdCmd("ENTER_DATA_MODE 14");
}

BC127::opResult BC127::enableGPIOControl()
{
  Serial.print("Enabling GPIO Control\r");
  return stdSetParam("GPIO_CONFIG", "ON 0 254");
}

BC127::opResult BC127::disableGPIOControl()
{
  // Serial.print("Disabling GPIO Control...");
  return stdSetParam("GPIO_CONFIG", "OFF 8");

  // return stdCmd("SET GPIO_CONFIG=OFF 8");
}

String BC127::getGPIOConfig()
{
  return stdGetParam("GPIO_CONFIG");
}

BC127::opResult BC127::disableAdvertising()
{
  return stdSetParam("BLE_CONFIG", "0 OFF 40 ON");
}

BC127::opResult BC127::stdCmd(String command)
{
  String buffer = "";
  String EOL    = String("\r");

  _serialPort->print(command);
  _serialPort->print("\r");
  _serialPort->flush();

  while (_serialPort->available() == 0) ;
  buffer.concat(char(_serialPort->read()));

  while (!buffer.endsWith(EOL)) {
    if (_serialPort->available()) {
      buffer.concat(char(_serialPort->read()));

      if (buffer.endsWith("OK")) {
        return SUCCESS;
      } else {
        return MODULE_ERROR;
      }
    }
  }
}

// Similar to the command function, let's do a set parameter genrealization.
BC127::opResult BC127::stdSetParam(String command, String param)
{
  String buffer = "";
  String EOL    = String("\r");

  _serialPort->print("SET ");
  _serialPort->print(command);
  _serialPort->print("=");
  _serialPort->print(param);
  _serialPort->print("\r");
  _serialPort->flush();

  while (_serialPort->available() == 0) ;
  buffer.concat(char(_serialPort->read()));

  while (!buffer.endsWith(EOL)) {
    if (_serialPort->available()) buffer.concat(char(_serialPort->read()));

    if (buffer.endsWith("OK")) {
      buffer = "";
      return SUCCESS;
    }
  }
  return TIMEOUT_ERROR;
}

String BC127::stdGetParam(String command)
{
  String param  = "";
  String buffer = "";
  String EOL    = String("OK");

  _serialPort->print("GET ");
  _serialPort->print(command);
  _serialPort->print("\r");
  _serialPort->flush();

  while (_serialPort->available() == 0) ;
  buffer.concat(char(_serialPort->read()));

  while (!buffer.endsWith("OK")) {
    if (_serialPort->available()) {
      buffer.concat(char(_serialPort->read()));
    }
  }

  if (buffer.startsWith("\r" + command)) {
    param = buffer.substring(command.length() + 2);
    param.trim();
    param.remove(param.length() - 3);
  } else {
    param = "ERROR: " + buffer;
  }
  buffer = "";
  return param;
}

BC127::opResult BC127::setName(String name)
{
  return stdSetParam("NAME", name);
}

// The BLE role of the device is important: it can be either Central,
// Peripheral,
//   or disabled. We've provided one function for each of these. Note that to
//   get a change of mode to "take", a write/reset cycle is required.
BC127::opResult BC127::BLEDisable()
{
  return stdSetParam("BLE_ROLE", "0");
}

BC127::opResult BC127::BLECentral()
{
  return stdSetParam("BLE_ROLE", "2");
}

BC127::opResult BC127::BLEPeripheral()
{
  return stdSetParam("BLE_ROLE", "1");
}

// Issue the "RESTORE" command over the serial port to the BC127. This will
//  reset the device to factory default settings, which is a good thing to do
//  once in a while.
BC127::opResult BC127::restore()
{
  return stdCmd("RESTORE");
}

// Issue the "WRITE" command over the serial port to the BC127. This will
//  save the current settings to NVM, so they will be applied after a reset
//  or power cycle.
BC127::opResult BC127::write()
{
  BC127::opResult result = stdCmd("WRITE");
#if DEBUG == true
  Serial.println("Writing settings to BC127..." + commandResult(result));
#endif
  return result;
}

BC127::opResult BC127::reset()
{
  String buffer = "";
  String EOL    = String("Ready\r");

  // knownStart(); // Clear the serial buffer in the module and the Arduino.

  _serialPort->print("RESET");
  _serialPort->print("\r");
  _serialPort->flush();

  while (_serialPort->available() == 0) ;
  buffer.concat(char(_serialPort->read()));

  while (!buffer.endsWith(EOL)) {
    if (_serialPort->available()) {
      buffer.concat(char(_serialPort->read()));
    }
  }

  BC127::opResult result = SUCCESS;

#if DEBUG == true
  Serial.println("Resetting BC127..." + commandResult(result));
#endif
  return result;
}

// Create a known state for the module to start from. If a partial command is
//  already in the module's buffer, we can purge it by sending an EOL to the
//  the module. If not, we'll just get an error.
BC127::opResult BC127::knownStart()
{
  String EOL     = String("\n\r");
  String buffer2 = "";

  _serialPort->print("\r");

  // _serialPort->flush();

  // bool x = buffer2.endsWith('\r');
  // Serial.println(x);

  while (_serialPort->available() == 0) ;

  while (!(buffer2 == "ERROR 0x0012\n\r")) {
    if (_serialPort->available()) {
      buffer2.concat(char(_serialPort->read()));
    }
  }
  Serial.print("buffer2 ======= ");
  Serial.print(buffer2);

  // while (1) ;

  Serial.print("buffer2.endsWith(EOL) = ");
  Serial.print(buffer2.endsWith(EOL));
  Serial.println();

  // Serial.println("here4");

  // while (1) ;

  // if (buffer.startsWith("ERR")) {
  //   Serial.println("successfully purged");
  //   buffer = "";
  return SUCCESS;

  // } else {
  //   Serial.println("ehhh... successfully purged");
  //   Serial.print("buffer = ");
  //   Serial.print(buffer);
  //   Serial.println();
  //   buffer = "";
  //   return MODULE_ERROR;
  // }
}
