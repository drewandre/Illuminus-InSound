#ifndef RN52_H
#define RN52_H

#include <Arduino.h>

#define DEBUG_BT true
#define BLUETOOTH_SERIAL_BUFFER_LENGTH 80

class RN52 {
public:

  RN52(int             commandPin,
       HardwareSerial *uart);
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

private:

  HardwareSerial *uart;

  int commandPin;
  int uartBaud;
  char rxBuffer[BLUETOOTH_SERIAL_BUFFER_LENGTH];
  unsigned int bufferWritingIndex;
  unsigned int bufferReadingIndex;

  uint16_t status();
  void     enterCommandMode();
  void     endCommandMode();
};
#endif // ifndef RN52_H
