#ifndef BM64_H
#define BM64_H

#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define DEBUG
#define BLUETOOTH_SERIAL_BUFFER_LENGTH 80

class BM64 {
public:

  BM64();
  BM64(int     rxInterruptPin,
       Stream& uartin);
  ~BM64();

  void enable();
  void enableRxInterrupt(int rxInterruptPin);
  void disableRxInterrupt();
  void readSerial();
  bool getInterruptStatus() const;

private:

  Stream& uart;

  bool rxInterruptEnabled;
  int rxInterruptPin;
  int uartBaud;
  char rxBuffer[BLUETOOTH_SERIAL_BUFFER_LENGTH];
  unsigned int bufferWritingIndex;
  unsigned int bufferReadingIndex;
};
#endif // ifndef BM64_H
