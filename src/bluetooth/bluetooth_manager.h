#ifndef BLUETOOTH_MANAGER_H
#define BLUETOOTH_MANAGER_H

#include <macros.h>

extern RN52 rn52;
extern BM64 bm64;

namespace BluetoothManager {
void initialize(void);
void printConfig(void);
void testVar(int var);
}

#endif
