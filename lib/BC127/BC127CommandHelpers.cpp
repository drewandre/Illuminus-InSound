#include "BC127.h"

String BC127::commandResult(int result) {
  if (result) {
    return "OK";
  } else {
    return "ERROR";
  }
  return "OK";
}

void BC127::enterCommandMode()
{
  // TODO: should first get BLE address that is currently connected to so that
  // exitCommandMode() knows which BLE address to connect to when entering data mode
  delay(420);
  _serialPort->print("$$$$\r");
  _serialPort->flush();
  delay(420);  
  // delay(420);
  // _serialPort->print("$$$$");
  // _serialPort->flush();
  // delay(420);  
  digitalWrite(commandPin, LOW); // LOW: ENTER COMMAND MODE
}

void BC127::exitCommandMode()
{
  digitalWrite(commandPin, HIGH); // HIGH: ENTER DATA MODE
}

BC127::opResult BC127::stdCmd(String command)
{
  static String buffer;
  static String EOL    = String("OK\r");
  buffer = "";

  _serialPort->print(command);
  _serialPort->print("\r");
  _serialPort->flush();

  while (!_serialPort->available()) ;
  buffer.concat(char(_serialPort->read()));

  while (!buffer.endsWith(EOL)) {
    if (_serialPort->available()) {
      buffer.concat(char(_serialPort->read()));

      // if (buffer.endsWith("OK")) {
      //   return SUCCESS;
      // } else {
      //   return MODULE_ERROR;
      // }
    }
  }
  return SUCCESS;
}

// Similar to the command function, let's do a set parameter genrealization.
BC127::opResult BC127::stdSetParam(String command, String param)
{
  static String buffer = "";
  static String EOL    = String("OK\r");
  buffer = "";

  _serialPort->print("SET ");
  _serialPort->print(command);
  _serialPort->print("=");
  _serialPort->print(param);
  _serialPort->print("\r");
  _serialPort->flush();
  while (!_serialPort->available()) ;

  buffer.concat(char(_serialPort->read()));

  while (!buffer.endsWith(EOL)) {
    if (_serialPort->available()) {
      buffer.concat(char(_serialPort->read()));
    }
    // if (buffer.endsWith(EOL)) {
    //   buffer = "";
    //   return SUCCESS;
    // }
  }

  return SUCCESS;
}

String BC127::stdGetParam(String command)
{
  static String param  = "";
  static String buffer = "";
  static String EOL    = String("OK\r");
  buffer = "";
  param = "";

  _serialPort->print("GET ");
  _serialPort->print(command);
  _serialPort->print("\r");
  _serialPort->flush();

  while (!_serialPort->available()) ;
  buffer.concat(char(_serialPort->read()));
  
  while (!buffer.endsWith(EOL)) {
    if (_serialPort->available()) {
      buffer.concat(char(_serialPort->read()));
    }
  }

  // if (buffer.startsWith("\r" + command)) {
  param = buffer.substring(command.length() + 1);
  param.trim();
  param.remove(param.length() - 3);

  // Serial.println("----------------");
  // Serial.println("buffer..."); Serial.print(buffer);
  // Serial.println("----------------");
  // } else {
  // param = "ERROR: " + buffer;
  // }
  // buffer = "";
  return param;
}

BC127::opResult BC127::write()
{
  static BC127::opResult result = stdCmd("WRITE");

#if DEBUG == true
  Serial.println("Writing settings to BC127..." + commandResult(result));
#endif
  return result;
}

// Create a known state for the module to start from. If a partial command is
//  already in the module's buffer, we can purge it by sending an EOL to the
//  the module. If not, we'll just get an error.
BC127::opResult BC127::knownStart()
{
  String EOL     = String("\n\r");
  String buffer2 = "";

  _serialPort->print("\r");

  // _serialPort->flush();

  // bool x = buffer2.endsWith('\r');
  // Serial.println(x);

  while (_serialPort->available() == 0) ;

  while (!(buffer2 == "ERROR 0x0012\n\r")) {
    if (_serialPort->available()) {
      buffer2.concat(char(_serialPort->read()));
    }
  }
  Serial.print("buffer2 ======= ");
  Serial.print(buffer2);

  // while (1) ;

  Serial.print("buffer2.endsWith(EOL) = ");
  Serial.print(buffer2.endsWith(EOL));
  Serial.println();

  // while (1) ;

  // if (buffer.startsWith("ERR")) {
  //   Serial.println("successfully purged");
  //   buffer = "";
  return SUCCESS;

  // } else {
  //   Serial.println("ehhh... successfully purged");
  //   Serial.print("buffer = ");
  //   Serial.print(buffer);
  //   Serial.println();
  //   buffer = "";
  //   return MODULE_ERROR;
  // }
}
