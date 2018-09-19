#include "BC127.h"

BC127::BC127(int             commandPinIn,
             int             gpioZeroIn,
             HardwareSerial *serial,
             bool            echoBC127,
             String deviceNameInput) {
  echoSerial = echoBC127;
  commandPin = commandPinIn;

  gpioZero         = gpioZeroIn;
  deviceName = deviceNameInput;
  _serialPort        = serial;
  bufferWritingIndex = 0;
  bufferReadingIndex = 0;
  _numAddresses      = -1;
}

BC127::~BC127() {}

void BC127::enable() {
  pinMode(commandPin, OUTPUT);
  pinMode(gpioZero, OUTPUT);
  // digitalWrite(gpioZero, HIGH); // HIGH: RESTORE BC127 ON STARTUP

  _serialPort->begin(uartBaud);
  enterCommandMode();
  // reset();

  disableGPIOControl();
  getGPIOConfig();
  resetPIO4();

  getName();

  setName(deviceName, false);
  setShortName(deviceName, false);
  
  setMaxNumOfReconnectionAttempts(255, false);
  // setUARTConfig();
  // getUARTConfig();

  disableiOSBatteryIndicator();
  disableAdvertisingOnStartup();
  enableConnectableAndDiscoverable();
  enableAutoConn(false);
  enableAutoData(false);
  getBLEConfig();
  enableHDAudio();
  
  write();
  reset();
}

// Issue the "RESTORE" command over the serial port to the BC127. This will
//  reset the device to factory default settings, which is a good thing to do
//  once in a while.
BC127::opResult BC127::restore()
{
  return stdCmd("RESTORE");
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