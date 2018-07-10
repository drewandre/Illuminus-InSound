#ifndef DEBUG_MANAGER_H
#define DEBUG_MANAGER_H

#include "../../macros.h"

namespace DebugManager {
void printStartupInfo(uint8_t stage);
void printSystemPerformanceEveryNSeconds(int seconds);
void initializeSerial();
}

#endif
