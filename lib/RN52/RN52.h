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

  void enable();
  void readSerial();
  void sendCommand(String cmd);
  void echo(String command);

  void play(void);
  void nextTrack(void);
  void prevTrack(void);
  void volUp(void);
  void volDown(void);
  void answer(void);
  void hangup(void);

  void setDeviceName(String name);
  void setDeviceType(String type);

  void muteTones();

  void printStatus();
  void printVersion();

  void setAnalogAudioOutput();
  void setMaxSpeakerGain();

  bool factorySettings(String name);

  void testVariable(int var);

private:

  HardwareSerial *uart = &Serial1;
  int uartBaud         = 115200;

  bool echoSerial = true;
  int commandPin  = 3;
  char rxBuffer[BLUETOOTH_SERIAL_BUFFER_LENGTH];
  unsigned int bufferWritingIndex;
  unsigned int bufferReadingIndex;

  int testV;

  uint16_t status();
  void     enterCommandMode();
  void     endCommandMode();
};
#endif // ifndef RN52_H
