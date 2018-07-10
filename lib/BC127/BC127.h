#ifndef BC127_H
#define BC127_H

#include <Arduino.h>

#define BLUETOOTH_SERIAL_BUFFER_LENGTH 80

class BC127 {
public:

  enum connType { SPP, BLE, A2DP, HFP, AVRCP, PBAP, ANY };
  enum opResult { REMOTE_ERROR = -5, CONNECT_ERROR, INVALID_PARAM,
                  TIMEOUT_ERROR, MODULE_ERROR, DEFAULT_ERR, SUCCESS };
  enum audioCmds { PLAY, PAUSE, FORWARD, BACK, UP, DOWN, STOP };

  BC127(int             commandPin,
        int             gpioZeroIn,
        HardwareSerial *_serialPort,
        bool            echoSerial);

  ~BC127();

  void     enable(void);
  void     enterCommandMode(void);
  void     exitCommandMode(void);
  String   commandResult(int result);
  opResult disableGPIOControl(void);
  String   getGPIOConfig();
  opResult enableGPIOControl(void);
  opResult disableAdvertising(void);

  opResult setName(String name);
  opResult reset(void);
  opResult restore(void);
  opResult write(void);
  opResult inquiry(int timeout);
  opResult connect(char     index,
                   connType connection);
  opResult connect(String   address,
                   connType connection);

  // opResult getAddress(char    index,
  //                     String& address);
  opResult BLEDisable();
  opResult BLECentral();
  opResult BLEPeripheral();
  opResult BLEAdvertise();
  opResult BLENoAdvertise();
  opResult BLEScan(int timeout);
  opResult musicCommands(audioCmds command);

  // opResult addressQuery(String& address);
  opResult setClassicSink();
  opResult setClassicSource();

  String   stdGetParam(String command);
  opResult stdSetParam(String command,
                       String param);
  opResult stdCmd(String command);

  opResult connectionState();

  bool     factorySettings(String name);

private:

  BC127() {}

  HardwareSerial *_serialPort = &Serial1;
  int uartBaud                = 9600;

  String _addresses[5];
  char _numAddresses;

  bool echoSerial = true;
  int commandPin  = 3;

  // int gpioZeroIn = 1;

  char rxBuffer[BLUETOOTH_SERIAL_BUFFER_LENGTH];
  unsigned int bufferWritingIndex;
  unsigned int bufferReadingIndex;

  opResult knownStart();
};
#endif // ifndef BC127_H
