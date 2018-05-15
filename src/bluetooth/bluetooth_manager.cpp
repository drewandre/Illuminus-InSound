// #include <env.h>

//
// #include <bluetooth_manager.h>
//
// int rxBuffer[BLUETOOTH_SERIAL_BUFFER_LENGTH];
// unsigned int bufferWritingIndex = 0;
// unsigned int bufferReadingIndex = 0;
//
// void BM64RxInterrupt() {
// #ifdef DEBUG
//   cout << "BM64RxInterrupt triggered!";
// #endif // ifdef DEBUG
//
//   if (BM64_SERIAL.available()) {
//     rxBuffer[bufferWritingIndex++] = BM64_SERIAL.read();
//
//     if (bufferWritingIndex >= BLUETOOTH_SERIAL_BUFFER_LENGTH) {
//       bufferWritingIndex = 0;
//     }
//   }
// #ifdef DEBUG
//   cout << "BM64> " << rxBuffer << endl;
// #endif // ifdef DEBUG
// }
//
// void readBM64Response() {
//   static char rxByte;
//
//   while (bufferReadingIndex != bufferWritingIndex) {
//     rxByte = rxBuffer[bufferReadingIndex++];
//     cout << rxByte;
//
//     if (bufferReadingIndex >= BLUETOOTH_SERIAL_BUFFER_LENGTH) {
//       bufferReadingIndex = 0;
//     }
//   }
// }
//
// void echoRN52(string command) {
//   //   string buffer               = "";
//   //   static bool   wait_for_RN52 = true;
//   //   unsigned long startTime;
//   //   unsigned long end_time;
//   //
//   //   while (HWSERIAL.available() == 0) ;
//   //
//   //   while (wait_for_RN52) {
//   //     buffer.concat(char(HWSERIAL.read()));
//   //
//   //     while (!buffer.endsWith("\r\n")) {
//   //       if (HWSERIAL.available()) buffer.concat(char(HWSERIAL.read()));
//   //     }
//   //     startTime = millis();
//   //     end_time  = startTime;
//   //
//   //     while ((end_time - startTime) <= 20) {
//   //       if (HWSERIAL.available() > 0) {
//   //         wait_for_RN52 = true;
//   //         break;
//   //       }
//   //       end_time      = millis();
//   //       wait_for_RN52 = false;
//   //     }
//   //   }
//   //   wait_for_RN52 = true;
//   //   cout << "RN52> " << command << ": " << endl << buffer << endl;
// }
//
// void printRN52(char command) {
//   enterCommandMode();
//
//   HWSERIAL.println(command);
// #ifdef DEBUG
//
//   // echoRN52(command);
// #endif // ifdef DEBUG
//   exitCommandMode();
// }
//
// void enterCommandMode() {
//   digitalWrite(RN52_CMD_PIN, LOW);
//   HWSERIAL.find("CMD\r\n");
// }
//
// void exitCommandMode() {
//   digitalWrite(RN52_CMD_PIN, HIGH);
//   HWSERIAL.find("END\r\n");
// }
//
// // bool RN52FactorySettings() {
// // buffer = "";
// // enterCommandMode();
// // HWSERIAL.println("GN"); // check RN52 device name
// //
// // while (HWSERIAL.available() == 0) ;
// //
// // while (!buffer.endsWith("\r\n")) {
// //   if (HWSERIAL.available()) buffer.concat(char(HWSERIAL.read()));
// // }
// //
// // exitCommandMode();
// // return buffer.trim().equals(DEVICE_NAME);
// // }
//
// // void setRN52(String command, String value) {
// //   param = "";
// //   param.concat(command);
// //   param.concat(",");
// //   param.concat(value);
// //   enterCommandMode();
// //   HWSERIAL.println(param);
// // #ifdef DEBUG
// //   echoRN52(param);
// // #endif // ifdef DEBUG
// //   exitCommandMode();
// // }
