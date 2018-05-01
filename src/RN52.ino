void echoRN52(String command) {
  buffer="";
  static bool wait_for_RN52 = true;
  unsigned long start_time;
  unsigned long end_time;

  while (HWSERIAL.available()==0);
  while(wait_for_RN52) {
    buffer.concat(char(HWSERIAL.read()));
    while (!buffer.endsWith("\r\n")) {
      if (HWSERIAL.available()) buffer.concat(char(HWSERIAL.read()));
    }
    start_time = millis();
    end_time = start_time;
    while((end_time - start_time) <= 20) {
      if (HWSERIAL.available() > 0) {
        wait_for_RN52 = true;
        break;
      }
      end_time = millis();
      wait_for_RN52 = false;
    }
  }
  wait_for_RN52 = true;
  Serial.print("RN52> "); Serial.print(command); Serial.print(": "); Serial.println(); Serial.println(buffer);
}


void printRN52(String command) {
  enterCommandMode();
  HWSERIAL.println(command);
#ifdef DEBUG
  echoRN52(command);
#endif
  exitCommandMode();
}

void enterCommandMode() {
  digitalWrite(RN52_CMD_PIN, LOW);
  HWSERIAL.find("CMD\r\n");
}

void exitCommandMode() {
  digitalWrite(RN52_CMD_PIN, HIGH);
  HWSERIAL.find("END\r\n");
}

bool RN52FactorySettings() {
  buffer="";
  enterCommandMode();
  HWSERIAL.println("GN"); // check RN52 device name
  while (HWSERIAL.available()==0);
  while (!buffer.endsWith("\r\n")) {
    if (HWSERIAL.available()) buffer.concat(char(HWSERIAL.read()));
  }

  exitCommandMode();
  return buffer.trim().equals(DEVICE_NAME);
}

void setRN52(String command, String value) {
  param="";
  param.concat(command);
  param.concat(",");
  param.concat(value);
  enterCommandMode();
  HWSERIAL.println(param);
#ifdef DEBUG
  echoRN52(param);
#endif
  exitCommandMode();
}
