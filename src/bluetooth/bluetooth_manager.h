#include <env.h>

void BM64RxInterrupt(void);

void readBM64Response(void);

bool RN52FactorySettings(void);
void readRN52Event(void);

void setRN52(String command,
             String value);
void printRN52(String command);
void enterCommandMode(void);
void exitCommandMode(void);
void readBM64(void);
