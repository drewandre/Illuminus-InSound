#include <macros.h>

float getFFTBins(void);
float FindE(uint8_t bands,
            uint8_t bins);

void  startup(void);
void  initSerial(void);
void  initInterrupts(void);
void  initEEPROM(void);
#if BM64 == true
void  initBM64(void);
#else // if BM64 == true
void  initRN52(void);
#endif // if BM64 == true
void  initWS2812B(void);
void  initNoise(void);
void  initSGTL5000(void);
