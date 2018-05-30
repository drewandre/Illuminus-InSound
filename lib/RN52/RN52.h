#ifndef RN52_H
#define RN52_H

#include <Arduino.h>

#define BLUETOOTH_SERIAL_BUFFER_LENGTH 80

class RN52 {
public:

  RN52() {}

  RN52(int             commandPin,
       HardwareSerial *uart,
       bool            echoSerial);

  ~RN52();

  void     enable();
  char   * readSerial();
  String   sendCommand(String cmd);
  String   echo(String command);

  void     printConfig();
  void     printVersion();
  void     printGPIOConfig();
  void     printConnectionStatus();
  String   getVolume();
  uint16_t status();

  void     play(void);
  void     nextTrack(void);
  void     prevTrack(void);
  void     volUp(void);
  void     volDown(void);
  void     answer(void);
  void     hangup(void);

  void     setDeviceName(String name);
  void     setDeviceType(String type);

  void     muteTones();
  void     setAnalogAudioOutput();
  void     setMaxSpeakerGain();

  bool     factorySettings(String name);

private:

  HardwareSerial *uart = &Serial1;
  int uartBaud         = 115200;

  bool echoSerial = true;
  int commandPin  = 3;
  char rxBuffer[BLUETOOTH_SERIAL_BUFFER_LENGTH];
  unsigned int bufferWritingIndex;
  unsigned int bufferReadingIndex;

  void enterCommandMode();
  void endCommandMode();
};
#endif // ifndef RN52_H
