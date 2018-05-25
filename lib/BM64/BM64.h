#ifndef BM64_H
#define BM64_H

#include <Arduino.h>

#define BLUETOOTH_SERIAL_BUFFER_LENGTH 80

class BM64 {
public:

  BM64() {}

  BM64(int             rxInterruptPin,
       HardwareSerial *uart,
       bool            echoSerial);

  ~BM64();

  void enable();

  void sendCommand(String command);
  void readSerial();
  void echo(String command);

  void enableRxInterrupt(int rxInterruptPin);
  void disableRxInterrupt();
  bool getInterruptStatus() const;

private:

  HardwareSerial *uart = &Serial1;
  int uartBaud         = 115200;

  bool echoSerial         = true;
  bool rxInterruptEnabled = true;
  int rxInterruptPin      = 3;
  char rxBuffer[BLUETOOTH_SERIAL_BUFFER_LENGTH];
  unsigned int bufferWritingIndex;
  unsigned int bufferReadingIndex;
};
#endif // ifndef BM64_H
