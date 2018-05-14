#include <Audio.h>
#include <FastLED.h>

using namespace std;
#include <iostream>
#include <stdint.h>


// ------------------- Environment config ------------------- //
#define DEBUG

// ---------------------- Debug config ---------------------- //
#ifdef DEBUG
  # define SWSERIAL_BAUD 115200 // RN52 must be at either 115200 or 9600 (if
// 9600 GPIO7 should be pulled low)
// #define PRINT_MCU_PERFORMANCE
  # define PRINT_RN52

// #define PRINT_FFT
// #define PRINT_MAPPED_FFT
// #define PLAY_TONE_SWEEP_ON_STARTUP
#endif // ifdef DEBUG

// -------------------- Palette config -------------------- //
#define PALETTE_VERSION 0x0001
#define PALETTE_VOLTAGE 5
#define PALETTE_AMPERAGE 2000

// ---------------------- BM64 config ---------------------- //
#define BM64_SERIAL Serial4 // RX4 (31) + TX4 (32)
#define BM64_SERIAL_BAUD 115200
#define BM64_UART_TX_IND -1
#define BLUETOOTH_SERIAL_BUFFER_LENGTH 80

// ---------------------- RN52 config ---------------------- //
#define RN52_ANALOG_OUTPUT

#define RN52_GPI02_PIN 8     // RN52 GPIO2 event notifier pin (default HIGH,
// HIGH -> LOW for 100ms on connected device event)
// #define CHECK_RN52_FACTORY_SETTINGS
#define HWSERIAL Serial1     // RX1 + TX1
#define HWSERIAL_BAUD 115200 // RN52 must be at either 115200 or 9600 (if 9600
// GPIO7 should be pulled low)
#define RN52_CMD_PIN 2       // In order to enter command mode,
// GPIO9/RN52_CMD_PIN must be pulled LOW
#define DEVICE_NAME "PALETTE"

// ---------------------- SGTL5000 config -------------------------- //
#ifdef RN52_ANALOG_OUTPUT // analog audio input from SGTL5000
const int AUDIO_IN = AUDIO_INPUT_LINEIN;
AudioInputI2S audioInput;

// AudioOutputI2S       audioOutput; // SGTL5000 headphones & line-out
// AudioConnection      patchCord1(audioInput, 0, audioOutput, 0);
// AudioConnection      patchCord2(audioInput, 1, audioOutput, 1);
#else // I2S audio input from RN52
AudioInputI2Sslave audioInput;
#endif // ifdef RN52_ANALOG_OUTPUT

AudioAnalyzeFFT1024 fftL;
AudioAnalyzeFFT1024 fftR;
AudioConnection     patchCord3(audioInput, 0, fftL, 0);
AudioConnection     patchCord4(audioInput, 1, fftR, 0);

#ifdef PLAY_TONE_SWEEP_ON_STARTUP
AudioSynthToneSweep tone_sweep;
AudioConnection     patchCord5(tone_sweep, 0, audioOutput, 0);
AudioConnection     patchCord6(tone_sweep, 0, audioOutput, 1);
#endif // ifdef PLAY_TONE_SWEEP_ON_STARTUP

AudioControlSGTL5000 SGTL5000;

// ---------------------- WS2812b config ---------------------- //
#define STRIP_TYPE WS2812B
#define DATA_PIN 3
#define NUM_LEDS 144

// #define NUM_LEDS_16 NUM_LEDS * 255; // delete multiplication in #define
static int c = NUM_LEDS * 0.5;
#define CENTER_LED_POS c

// #define HALF_POS_16 NUM_LEDS_16 * 0.5; // delete multiplication in #define
#define COLOR_ORDER GRB
#define LED_COLOR_CORRECTION TypicalLEDStrip
#define FFT_FIXED_SEGMENT_LENGTH NUM_LEDS / NUM_BANDS

// #define HUE_LENGTH floor(255 / NUM_BANDS - 1);
// #define PALETTE_INDEX_INCREMENT 248.0 / NUM_LEDS;
// #define PALETTE_INDEX_INCREMENT_twelve 4095 / NUM_LEDS;
CRGB leds[NUM_LEDS];

// -------------- Animation Controller config --------------- //
#define NUM_MODES 5
bool calculateScaledFFT  = false;
uint8_t currentAnimation = 0;

// --------------------- EEPROM config --------------------- //
// #define PALETTE_ADDRESS 0
// #define EFFECT_ADDRESS 1

// ----------------=----- FFT config -----=---------------- //
#define NUM_BANDS 32
#define MAX_BIN 511
uint16_t fftBins[NUM_BANDS];
uint8_t  levelsL[NUM_BANDS];
uint8_t  levelsR[NUM_BANDS];
uint8_t  scaledLevelsL[NUM_BANDS];
uint8_t  scaledLevelsR[NUM_BANDS];

// ------------------ color palette config ------------------ //
#define COLOR_PALETTE_SPEED 45 // speed for switching between palettes
extern const TProgmemRGBGradientPalettePtr gGradientPalettes[];
uint8_t gGradientPaletteCount; // TODO: should be initialzed
extern uint8_t gCurrentPaletteNumber;
extern uint8_t palette;
CRGBPalette16  gCurrentPalette(gGradientPalettes[gGradientPaletteCount]);
CRGBPalette16  gTargetPalette(gGradientPalettes[gGradientPaletteCount + 1]);
