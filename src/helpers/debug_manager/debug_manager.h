#ifndef DEBUG_MANAGER_H
#define DEBUG_MANAGER_H

#include "../../config/config.h"

namespace DebugManager
{
void printStartupInfo(uint8_t stage);
void printSystemPerformanceEveryNSeconds(int seconds);
void initializeSerial();
} // namespace DebugManager

#endif
