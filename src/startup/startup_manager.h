#include <macros.h>

float getFFTBins(void);
float FindE(uint8_t bands,
            uint8_t bins);

void  startup(void);
void  initSerial(void);
void  initInterrupts(void);
void  initEEPROM(void);
void  initRN52(void);
void  initBM64(void);
void  initWS2812B(void);
void  initNoise(void);
void  initSGTL5000(void);
