#ifndef BLUETOOTH_MANAGER_H
#define BLUETOOTH_MANAGER_H

#include "../macros.h"

extern BC127 bc127;

namespace BluetoothManager {
void initialize(void);
void enterCommandMode(void);
void exitCommandMode(void);
void disableGPIOControl(void);
void handleBC127ConnectionEvent(void);
void handleBC127Event(void);
void listenAndHandleSPPData(void);
void handleSPPData(String SPPBuffer);
void enableBLEAdvertising(void);
void printChange(String str);
}

#endif
