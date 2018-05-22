#include "BM64.h"

BM64::BM64() : uart(uart) {
  rxInterruptEnabled = false;
  rxInterruptPin     = 3;
  uart               = Serial1;
  uartBaud           = 115200; // guessed BM64 serial rate...
  bufferWritingIndex = 0;
  bufferReadingIndex = 0;
}

BM64::BM64(int     rxInterruptPinIn,
           Stream& uartin) : uart(uartin) {}

BM64::~BM64() {}

void BM64::enable() {
  uart.println("0x00");
}

void BM64::readSerial() {
  if (uart.available()) {
    rxBuffer[bufferWritingIndex++] = uart.read();

    if (bufferWritingIndex >= BLUETOOTH_SERIAL_BUFFER_LENGTH) {
      bufferWritingIndex = 0;
    }
  }
#ifdef DEBUG

  Serial.print("BM64> "); Serial.print(rxBuffer); Serial.println();
#endif // ifdef DEBUG
}

bool BM64::getInterruptStatus() const {
  return rxInterruptEnabled;
}

void BM64::enableRxInterrupt(int rxInterruptPin) {
  pinMode(rxInterruptPin, INPUT);

  // digitalPinToInterrupt(rxInterruptPin)
  // attachInterrupt(rxInterruptPin, readSerial, CHANGE);
  rxInterruptEnabled = true;
}

void BM64::disableRxInterrupt() {
  rxInterruptEnabled = false;
}
