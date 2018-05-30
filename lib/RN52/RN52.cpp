#include "RN52.h"

RN52::RN52(int commandPinIn, HardwareSerial *serial, bool echoRN52) {
  echoSerial         = echoRN52;
  commandPin         = commandPinIn;
  uart               = serial;
  bufferWritingIndex = 0;
  bufferReadingIndex = 0;
}

RN52::~RN52() {}

void RN52::enable() {
  pinMode(commandPin, OUTPUT);
  digitalWrite(commandPin, HIGH); // exit data mode
  uart->begin(uartBaud);
}

void RN52::enterCommandMode() {
  digitalWrite(commandPin, LOW);
  uart->find("CMD\r\n");
}

void RN52::endCommandMode() {
  digitalWrite(commandPin, HIGH);
  uart->find("END\r\n");
}

void RN52::setDeviceName(String name) {
  String x = "SN,";

  x.concat(name);
  sendCommand(x);
}

// http://bluetooth-pentest.narod.ru/software/bluetooth_class_of_device-service_generator.html
void RN52::setDeviceType(String type) {
  String x = "SC,";

  x.concat(type);
  sendCommand(x);
}

void RN52::muteTones() {
  sendCommand("ST,00");
}

String RN52::sendCommand(String cmd) {
  enterCommandMode();
  uart->println(cmd);

  String response = echo(cmd);

  endCommandMode();

  return response;
}

char * RN52::readSerial() {
  if (uart->available()) {
    rxBuffer[bufferWritingIndex++] = uart->read();

    if (bufferWritingIndex >= BLUETOOTH_SERIAL_BUFFER_LENGTH) {
      bufferWritingIndex = 0;
    }

    if (echoSerial) {
      Serial.print("RN52 > "); Serial.print(rxBuffer); Serial.println();
    }
    return rxBuffer;
  }
  return 0;
}

String RN52::echo(String command) {
  String buffer = "";

  static bool   wait_for_RN52 = true;
  unsigned long startTime;
  unsigned long end_time;

  while (uart->available() == 0) ;

  while (wait_for_RN52) {
    buffer.concat(char(uart->read()));

    while (!buffer.endsWith("\r\n")) {
      if (uart->available()) buffer.concat(char(uart->read()));
    }
    startTime = millis();
    end_time  = startTime;

    while ((end_time - startTime) <= 20) {
      if (uart->available() > 0) {
        wait_for_RN52 = true;
        break;
      }
      end_time      = millis();
      wait_for_RN52 = false;
    }
  }
  wait_for_RN52 = true;

  if ((command != "D") && (command != "V")) {
    Serial.print("RN52 >\t");
    Serial.print(command);
    Serial.print("\t");
    Serial.print(buffer);
  } else {
    Serial.print(buffer);
  }
  return buffer;
}

// byte 0
// BIT_0 iAP
// BIT_1 SPP
// BIT_2 A2DP
// BIT_3 HFP/HSP
const uint16_t STATUS_iAP  = bit(0);
const uint16_t STATUS_SPP  = bit(1);
const uint16_t STATUS_A2DP = bit(2);

// byte 1, don't care for now
// 0-3 con status
// 4 HFP audio level
// 5 HFP mic level

uint16_t RN52::status() {
  char buf[32];

  uint16_t stat;
  byte     bytes;

  enterCommandMode();

  // wait for CMD
  uart->println("Q");

  // read byte
  bytes      = uart->readBytesUntil('\n', buf, 31);
  buf[bytes] = 0; // NUL terminate
  stat       = strtol(buf, NULL, 16);
  endCommandMode();

  return stat;
}

void RN52::play() {
  sendCommand("AP");
}

void RN52::volUp() {
  sendCommand("AV+");
}

void RN52::volDown() {
  sendCommand("AV-");
}

void RN52::nextTrack() {
  sendCommand("AT+");
}

void RN52::prevTrack() {
  sendCommand("AT-");
}

void RN52::answer() {
  sendCommand("C");
}

void RN52::hangup() {
  sendCommand("E");
}

void RN52::printConfig() {
  sendCommand("D");
}

void RN52::printVersion() {
  sendCommand("V");
}

void RN52::setAnalogAudioOutput() {
  sendCommand("S|,00"); // "S|,0102" for digital?
}

void RN52::setMaxSpeakerGain() {
  sendCommand("SS,0x09");
}

void RN52::printGPIOConfig() {
  sendCommand("I@");
}

void RN52::printConnectionStatus() {
  sendCommand("Q");
}

String RN52::getVolume() {
  return sendCommand("Y,0");
}

bool RN52::factorySettings(String name) {
  String buffer = "";

  enterCommandMode();
  uart->println("GN"); // check RN52 device name

  while (uart->available() == 0) ;

  while (!buffer.endsWith("\r\n")) {
    if (uart->available()) buffer.concat(char(uart->read()));
  }

  endCommandMode();
  return buffer.trim().equals(name);
}
