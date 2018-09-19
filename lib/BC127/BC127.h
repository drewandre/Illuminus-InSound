#ifndef BC127_H
#define BC127_H

#include <Arduino.h>

#define TIMEOUT_DELAY 2000
#define AUTOCONN "0"
#define AUTO_DATA "ON ON" // "ON ON" for auto connection to first BLE profile
#define BT_STATE "ON ON" // "ON ON" for auto connection to first BLE profile
#define BLUETOOTH_SERIAL_BUFFER_LENGTH 80
#define DEVICE_NAME "PALETTE"
#define DEBUG true

class BC127 {
public:

  enum connType { SPP, BLE, A2DP, HFP, AVRCP, PBAP, ANY };
  enum opResult { REMOTE_ERROR = -5, CONNECT_ERROR, INVALID_PARAM,
                  TIMEOUT_ERROR, MODULE_ERROR, DEFAULT_ERR, SUCCESS };
  enum audioCmds { PLAY, PAUSE, FORWARD, BACK, UP, DOWN, STOP };

  BC127(int             commandPin,
        int             gpioZero,
        HardwareSerial *_serialPort,
        bool            echoSerial,
        String deviceName);

  ~BC127();

  void     enable(void);

  void     enterCommandMode(void);
  void     exitCommandMode(void);

  String   commandResult(int result);

  opResult disableGPIOControl(void);
  String   getGPIOConfig(void);
  String   getBLEConfig(void);
  String   getUARTConfig(void);
  opResult   resetPIO4(void);
  String getName();
  
  opResult enableGPIOControl(void);
  opResult disableAdvertising(void);
  opResult disableAdvertisingOnStartup(void);
  opResult enableConnectableAndDiscoverable(void);
  opResult disableiOSBatteryIndicator(void);
  opResult enableAutoData(bool shouldReboot);
  opResult enableAutoConn(bool shouldReboot);
  opResult enableHDAudio(void);

  opResult setName(String name, bool shouldReboot);
  opResult setShortName(String name, bool shouldReboot);
  opResult setMaxNumOfReconnectionAttempts(int maxNum, bool shouldReboot);
  opResult setUARTConfig(void);

  opResult reset(void);
  opResult restore(void);
  opResult write(void);
  opResult inquiry(int timeout);
  opResult connect(char     index,
                   connType connection);

  // opResult getAddress(char    index,
  //                     String& address);

  opResult BLEScan(int timeout);
  opResult musicCommands(audioCmds command);

  // opResult addressQuery(String& address);
  opResult setClassicSink(void);
  opResult setClassicSource(void);

  String   stdGetParam(String command);
  opResult stdSetParam(String command,
                       String param);
  opResult stdCmd(String command);

  opResult connectionState(void);

  bool     factorySettings(String name);

private:

  BC127() {}

  HardwareSerial *_serialPort = &Serial1;
  int uartBaud                = 9600;

  String _addresses[5];
  char _numAddresses;

  bool echoSerial = true;
  int commandPin  = 3;
  int gpioZero = 1;
  String deviceName = "DEVICE_NAME";

  char rxBuffer[BLUETOOTH_SERIAL_BUFFER_LENGTH];
  unsigned int bufferWritingIndex;
  unsigned int bufferReadingIndex;

  opResult knownStart();
};
#endif // ifndef BC127_H
