#include "BM64.h"

BM64::BM64(int rxInterruptPin, HardwareSerial *serial) {
  rxInterruptEnabled = false;
  rxInterruptPin     = 3;
  uart               = serial;
  uartBaud           = 115200;
  bufferWritingIndex = 0;
  bufferReadingIndex = 0;
}

BM64::~BM64() {}

void BM64::enable() {
  pinMode(rxInterruptPin, INPUT);
  uart->begin(uartBaud);
}

void BM64::sendCommand(String command) {
  uart->println(command);
  echo(command);
}

void BM64::echo(String command) {
  String buffer               = "";
  static bool   wait_for_BM64 = true;
  unsigned long startTime;
  unsigned long end_time;

  while (uart->available() == 0) ;

  while (wait_for_BM64) {
    buffer.concat(char(uart->read()));

    while (!buffer.endsWith("\r\n")) {
      if (uart->available()) buffer.concat(char(uart->read()));
    }
    startTime = millis();
    end_time  = startTime;

    while ((end_time - startTime) <= 20) {
      if (uart->available() > 0) {
        wait_for_BM64 = true;
        break;
      }
      end_time      = millis();
      wait_for_BM64 = false;
    }
  }
  wait_for_BM64 = true;
  Serial.print("BM64> "); Serial.print(command); Serial.print(": ");
  Serial.println(); Serial.print(buffer); Serial.println();
}

void BM64::readSerial() {
  if (uart->available()) {
    rxBuffer[bufferWritingIndex++] = uart->read();

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
