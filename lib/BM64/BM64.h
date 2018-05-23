#ifndef BM64_H
#define BM64_H

#include <Arduino.h>

#define DEBUG
#define BLUETOOTH_SERIAL_BUFFER_LENGTH 80

class BM64 {
public:

  BM64(int             rxInterruptPin,
       HardwareSerial *uart);
  ~BM64();

  void enable();

  void sendCommand(String command);
  void readSerial();
  void echo(String command);

  void enableRxInterrupt(int rxInterruptPin);
  void disableRxInterrupt();
  bool getInterruptStatus() const;

private:

  HardwareSerial *uart;
  int uartBaud;

  bool rxInterruptEnabled;
  int rxInterruptPin;
  char rxBuffer[BLUETOOTH_SERIAL_BUFFER_LENGTH];
  unsigned int bufferWritingIndex;
  unsigned int bufferReadingIndex;
};
#endif // ifndef BM64_H
