#define FASTLED_INTERNAL
#include <FastLED.h>

// Gradient palette "bhw1_06_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_06.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 16 bytes of program space.

DEFINE_GRADIENT_PALETTE(bhw1_06_gp){
    0, 184, 1, 128,
    160, 1, 193, 182,
    219, 153, 227, 190,
    255, 255, 255, 255};

// Gradient palette "bhw1_purplered_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_purplered.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 8 bytes of program space.

DEFINE_GRADIENT_PALETTE(bhw1_purplered_gp){
    0, 255, 0, 0,
    255, 107, 1, 205};

// Gradient palette "bhw1_05_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_05.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 8 bytes of program space.

DEFINE_GRADIENT_PALETTE(bhw1_05_gp){
    0, 1, 221, 53,
    255, 73, 3, 178};

// Gradient palette "bhw1_04_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_04.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE(bhw1_04_gp){
    0, 229, 227, 1,
    15, 227, 101, 3,
    142, 40, 1, 80,
    198, 17, 1, 79,
    255, 0, 0, 45};

DEFINE_GRADIENT_PALETTE(red){
    0, 255, 0, 0,
    50, 255, 0, 0,
    100, 255, 0, 0,
    150, 255, 0, 0,
    200, 255, 0, 0,
    255, 255, 0, 0};

// Gradient palette "GMT_rainbow_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/gmt/tn/GMT_rainbow.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 1204 bytes of program space.

DEFINE_GRADIENT_PALETTE(rainbow){
    0, 0, 0, 0,
    36, 153, 0, 0,
    72, 204, 255, 0,
    108, 51, 255, 0,
    144, 0, 255, 102,
    180, 0, 255, 255,
    216, 0, 102, 255,
    230, 64, 0, 255};

// Gradient palette "GMT_seis_gp", originally from
//
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/gmt/tn/GMT_seis.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 40 bytes of program space.

DEFINE_GRADIENT_PALETTE(BI_gp){
    0,
    255,
    51,
    0,
    50,
    255,
    51,
    0,
    100,
    255,
    51,
    0,
    100,
    255,
    51,
    0,
    150,
    255,
    51,
    0,
    151,
    23,
    55,
    84,
    193,
    135,
    202,
    39,
    255,
    135,
    202,
    39,
};

DEFINE_GRADIENT_PALETTE(GMT_seis_gp){
    0, 88, 0, 0,
    28, 255, 0, 0,
    56, 255, 22, 0,
    85, 255, 104, 0,
    113, 255, 255, 0,
    141, 255, 255, 0,
    169, 17, 255, 1,
    198, 0, 223, 31,
    226, 0, 19, 255,
    255, 0, 0, 147};

// AMERICAN/FRENCH FLAG:
// Gradient palette "French_flag_smooth_gp", originally from
//
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ggr/tn/French_flag_smooth.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE(French_flag_smooth_gp){
    0, 0, 0, 255,
    63, 42, 55, 255,
    127, 255, 255, 255,
    191, 255, 55, 45,
    255, 255, 0, 0};

// Gradient palette "spectrum_rainbow_medium_gp", originally from
//
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ocal/tn/spectrum-rainbow-medium.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE(spectrum_rainbow_medium_gp){
    0, 255, 55, 45,
    42, 255, 136, 45,
    85, 255, 255, 45,
    127, 42, 255, 45,
    169, 42, 255, 255,
    212, 42, 55, 255,
    255, 255, 136, 255};

// Gradient palette "Split_Complementary_06_gp", originally from
//
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/vermillion/tn/Split_Complementary_06.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE(Split_Complementary_06_gp){
    0, 255, 18, 18,
    63, 91, 44, 95,
    127, 16, 82, 255,
    191, 2, 125, 55,
    255, 0, 178, 1};

// Gradient palette "Blue_Magenta_White_gp", originally from
//
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/basic/tn/Blue_Magenta_White.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE(Blue_Magenta_White_gp){
    0, 0, 0, 255,
    63, 42, 0, 255,
    127, 255, 0, 255,
    191, 255, 55, 255,
    255, 255, 255, 255};

// Gradient palette "Magenta_Yellow_Magenta_gp", originally from
//
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/basic/tn/Magenta_Yellow_Magenta.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE(Magenta_Yellow_Magenta_gp){
    0, 255, 0, 255,
    63, 255, 55, 45,
    127, 255, 255, 0,
    191, 255, 55, 45,
    255, 255, 0, 255};

// Gradient palette "Yellow_Red_Magenta_gp", originally from
//
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/basic/tn/Yellow_Red_Magenta.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE(Yellow_Red_Magenta_gp){
    0, 255, 255, 0,
    63, 255, 55, 0,
    127, 255, 0, 0,
    191, 255, 0, 45,
    255, 255, 0, 255};

// Gradient palette "rgi_15_gp", originally from
//
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ds/rgi/tn/rgi_15.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 36 bytes of program space.

DEFINE_GRADIENT_PALETTE(rgi_15_gp){
    0, 4, 1, 31,
    31, 55, 1, 16,
    63, 197, 3, 7,
    95, 59, 2, 17,
    127, 6, 2, 34,
    159, 39, 6, 33,
    191, 112, 13, 32,
    223, 56, 9, 35,
    255, 22, 6, 38};

// Gradient palette "Analogous_1_gp", originally from
//
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/red/tn/Analogous_1.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE(Analogous_1_gp){
    0, 3, 0, 255,
    63, 23, 0, 255,
    127, 67, 0, 255,
    191, 142, 0, 45,
    255, 255, 0, 0};

// Gradient palette "gr64_hult_gp", originally from
//
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/hult/tn/gr64_hult.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 32 bytes of program space.

DEFINE_GRADIENT_PALETTE(gr64_hult_gp){
    0, 1, 124, 109,
    66, 1, 93, 79,
    104, 52, 65, 1,
    130, 115, 127, 1,
    150, 52, 65, 1,
    201, 1, 86, 72,
    239, 0, 55, 45,
    255, 0, 55, 45};

// Gradient palette "Fuschia_7_gp", originally from
//
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ds/fuschia/tn/Fuschia-7.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE(Fuschia_7_gp){
    0, 43, 3, 153,
    63, 100, 4, 103,
    127, 188, 5, 66,
    191, 161, 11, 115,
    255, 135, 20, 182};

// Gradient palette "es_emerald_dragon_08_gp", originally from
//
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/emerald_dragon/tn/es_emerald_dragon_08.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 16 bytes of program space.

DEFINE_GRADIENT_PALETTE(es_emerald_dragon_08_gp){
    0, 97, 255, 1,
    101, 47, 133, 1,
    178, 13, 43, 1,
    255, 2, 10, 1};

// Gradient palette "Magenta_Evening_gp", originally from
//
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/atmospheric/tn/Magenta_Evening.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE(Magenta_Evening_gp){
    0, 71, 27, 39,
    31, 130, 11, 51,
    63, 213, 2, 64,
    70, 232, 1, 66,
    76, 252, 1, 69,
    108, 123, 2, 51,
    255, 46, 9, 35};

// Gradient palette "Pink_Purple_gp", originally from
//
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/atmospheric/tn/Pink_Purple.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 44 bytes of program space.

DEFINE_GRADIENT_PALETTE(Pink_Purple_gp){
    0, 19, 2, 39,
    25, 26, 4, 45,
    51, 33, 6, 52,
    76, 68, 62, 125,
    102, 118, 187, 240,
    109, 163, 215, 247,
    114, 217, 244, 255,
    122, 159, 149, 221,
    149, 113, 78, 188,
    183, 128, 57, 155,
    255, 146, 40, 123};

// Gradient palette "Sunset_Real_gp", originally from
//
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/atmospheric/tn/Sunset_Real.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE(Sunset_Real_gp){
    0, 120, 0, 0,
    22, 179, 22, 0,
    51, 255, 104, 0,
    85, 167, 22, 18,
    135, 100, 0, 103,
    198, 16, 0, 130,
    255, 0, 0, 160};

// Gradient palette "Blue_Cyan_Yellow_gp", originally from
//
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/basic/tn/Blue_Cyan_Yellow.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE(Blue_Cyan_Yellow_gp){
    0, 0, 0, 255,
    63, 0, 55, 255,
    127, 0, 255, 255,
    191, 42, 255, 45,
    255, 255, 255, 0};

// Gradient palette "es_pinksplash_12_gp", originally from
//
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/pink_splash/tn/es_pinksplash_12.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE(es_pinksplash_12_gp){
    0, 229, 1, 6,
    76, 215, 2, 42,
    102, 234, 9, 79,
    127, 252, 21, 130,
    178, 255, 39, 255,
    242, 247, 127, 242,
    255, 247, 127, 242};

// Single array of defined cpt-city color palettes.
// This will let us programmatically choose one based on
// a number, rather than having to activate each explicitly
// by name every time.
// Since it is const, this array could also be moved
// into PROGMEM to save SRAM, but for simplicity of illustration
// we'll keep it in a regular SRAM array.

// This list of color palettes acts as a "playlist"; you can
// add or delete, or re-arrange as you wish.
// const TProgmemRGBGradientPalettePtr gGradientPalettes[] = {
//  French_flag_smooth_gp,
//  spectrum_rainbow_medium_gp,
//  Split_Complementary_06_gp,
//  Blue_Magenta_White_gp,
//  Magenta_Yellow_Magenta_gp,
//  Yellow_Red_Magenta_gp,
//  rgi_15_gp,
//  Analogous_1_gp,
//  gr64_hult_gp,
//  Fuschia_7_gp,
//  es_emerald_dragon_08_gp,
//  Magenta_Evening_gp,
//  Pink_Purple_gp,
//  Sunset_Real_gp,
//  Blue_Cyan_Yellow_gp,
//  es_pinksplash_12_gp
// };

// Gradient palette "bhw1_three_gp", originally from
//
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_three.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 32 bytes of program space.

DEFINE_GRADIENT_PALETTE(bhw1_three_gp){
    0, 255, 255, 255,
    45, 7, 12, 255,
    112, 227, 1, 127,
    112, 227, 1, 127,
    140, 255, 255, 255,
    155, 227, 1, 127,
    196, 45, 1, 99,
    255, 255, 255, 255};

// Gradient palette "Accent_05_gp", originally from
//
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/cb/qual/tn/Accent_05.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 40 bytes of program space.

DEFINE_GRADIENT_PALETTE(Accent_05_gp){
    0, 41, 151, 44,
    51, 41, 151, 44,
    51, 118, 109, 160,
    102, 118, 109, 160,
    102, 249, 136, 51,
    153, 249, 136, 51,
    153, 255, 255, 71,
    204, 255, 255, 71,
    204, 4, 38, 100,
    255, 4, 38, 100};

// Gradient palette "rainbow_gp", originally from
//
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ds9/tn/rainbow.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 24 bytes of program space.

DEFINE_GRADIENT_PALETTE(rainbow_gp){
    0, 255, 0, 255,
    51, 0, 0, 255,
    102, 0, 255, 255,
    153, 0, 255, 0,
    204, 255, 255, 0,
    255, 255, 0, 0};

// Gradient palette "rgi_13_gp", originally from
//
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ds/rgi/tn/rgi_13.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 12 bytes of program space.

DEFINE_GRADIENT_PALETTE(rgi_13_gp){
    0, 133, 46, 2,
    127, 130, 14, 4,
    255, 128, 1, 8};

// Gradient palette "Fire_1_gp", originally from
//
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ds/icons/tn/Fire-1.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 12 bytes of program space.

DEFINE_GRADIENT_PALETTE(Fire_1_gp){
    0, 255, 0, 0,
    127, 255, 55, 0,
    255, 255, 255, 0};

// Gradient palette "Fuschia_8_gp", originally from
//
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ds/fuschia/tn/Fuschia-8.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 12 bytes of program space.

DEFINE_GRADIENT_PALETTE(Fuschia_8_gp){
    0, 44, 4, 214,
    127, 123, 1, 233,
    255, 255, 0, 255};

// Gradient palette "GMT_sealand_gp", originally from
//
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/gmt/tn/GMT_sealand.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 80 bytes of program space.

DEFINE_GRADIENT_PALETTE(GMT_sealand_gp){
    0, 53, 33, 255,
    14, 23, 33, 255,
    28, 23, 68, 255,
    42, 23, 115, 255,
    56, 23, 178, 255,
    70, 23, 255, 255,
    84, 23, 255, 170,
    99, 23, 255, 103,
    113, 23, 255, 56,
    127, 23, 255, 25,
    141, 53, 255, 25,
    155, 100, 255, 25,
    170, 167, 255, 25,
    170, 255, 255, 87,
    184, 255, 193, 87,
    198, 255, 141, 87,
    212, 255, 99, 87,
    226, 255, 115, 135,
    240, 255, 135, 182,
    255, 255, 156, 223};

// Gradient palette "GMT_seafloor_gp", originally from
//
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/gmt/tn/GMT_seafloor.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 88 bytes of program space.

DEFINE_GRADIENT_PALETTE(GMT_seafloor_gp){
    0, 25, 0, 109,
    10, 28, 0, 119,
    21, 32, 0, 127,
    31, 35, 0, 140,
    42, 27, 1, 145,
    53, 20, 1, 151,
    74, 14, 4, 156,
    84, 9, 9, 164,
    95, 5, 15, 170,
    106, 2, 24, 176,
    116, 1, 35, 182,
    138, 1, 49, 188,
    148, 0, 66, 197,
    159, 1, 79, 203,
    170, 3, 93, 210,
    180, 10, 109, 216,
    191, 24, 128, 223,
    212, 43, 149, 230,
    223, 72, 173, 240,
    233, 112, 197, 247,
    244, 163, 225, 255,
    255, 220, 248, 255};

// Gradient palette "GMT_cool_gp", originally from
//
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/gmt/tn/GMT_cool.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 8 bytes of program space.

DEFINE_GRADIENT_PALETTE(GMT_cool_gp){
    0, 0, 255, 255,
    255, 255, 0, 255};

// Gradient palette "Tropical_Colors_gp", originally from
//
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ggr/tn/Tropical_Colors.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 116 bytes of program space.

// Gradient palette "Yellow_Orange_gp", originally from
//
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ggr/tn/Yellow_Orange.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE(Yellow_Orange_gp){
    0, 255, 199, 0,
    34, 255, 121, 0,
    144, 255, 63, 0,
    241, 222, 51, 1,
    255, 194, 39, 1};

// Gradient palette "summer_gp", originally from
// // http://soliton.vm.bytemark.co.uk/pub/cpt-city/h5/tn/summer.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 64 bytes of program space.

DEFINE_GRADIENT_PALETTE(summer_gp){
    0, 0, 55, 25,
    17, 1, 62, 25,
    33, 1, 72, 25,
    51, 3, 82, 25,
    68, 8, 92, 25,
    84, 14, 104, 25,
    102, 23, 115, 25,
    119, 35, 127, 25,
    135, 48, 141, 25,
    153, 67, 156, 25,
    170, 88, 169, 25,
    186, 112, 186, 25,
    204, 142, 201, 25,
    221, 175, 217, 25,
    237, 210, 235, 25,
    255, 255, 255, 25};

// Gradient palette "spring_gp", originally from
// // http://soliton.vm.bytemark.co.uk/pub/cpt-city/h5/tn/spring.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 64 bytes of program space.

DEFINE_GRADIENT_PALETTE(spring_gp){
    0, 255, 0, 255,
    17, 255, 1, 212,
    33, 255, 2, 178,
    51, 255, 7, 145,
    68, 255, 13, 115,
    84, 255, 22, 92,
    102, 255, 33, 71,
    119, 255, 47, 52,
    135, 255, 62, 37,
    153, 255, 82, 25,
    170, 255, 104, 15,
    186, 255, 127, 9,
    204, 255, 156, 4,
    221, 255, 186, 1,
    237, 255, 217, 1,
    255, 255, 255, 0};

// Gradient palette "winter_gp", originally from
// // http://soliton.vm.bytemark.co.uk/pub/cpt-city/h5/tn/winter.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 8 bytes of program space.

DEFINE_GRADIENT_PALETTE(winter_gp){
    0, 0, 0, 255,
    255, 0, 255, 44};

// Gradient palette "cbcYlOrRd_gp", originally from
//
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/jjg/cbcont/seq/tn/cbcYlOrRd.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 40 bytes of program space.

// Gradient palette "cbcReds_gp", originally from
//
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/jjg/cbcont/seq/tn/cbcReds.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 40 bytes of program space.

DEFINE_GRADIENT_PALETTE(cbcReds_gp){
    0, 255, 233, 219,
    28, 252, 213, 186,
    56, 249, 159, 115,
    84, 247, 99, 54,
    113, 247, 54, 21,
    141, 229, 21, 6,
    170, 175, 4, 1,
    198, 109, 1, 1,
    226, 47, 1, 1,
    255, 24, 0, 1};

// Gradient palette "cbcGreens_gp", originally from
//
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/jjg/cbcont/seq/tn/cbcGreens.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 40 bytes of program space.

DEFINE_GRADIENT_PALETTE(cbcGreens_gp){
    0, 234, 248, 230,
    28, 213, 241, 207,
    56, 161, 221, 153,
    84, 103, 193, 98,
    113, 51, 159, 52,
    141, 17, 124, 28,
    170, 3, 85, 14,
    198, 1, 52, 5,
    226, 0, 24, 1,
    255, 0, 13, 1};

// Gradient palette "cbcSpectral_gp", originally from
//
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/jjg/cbcont/div/tn/cbcSpectral.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 92 bytes of program space.

DEFINE_GRADIENT_PALETTE(cbcSpectral_gp){
    0, 73, 1, 8,
    11, 73, 1, 8,
    23, 112, 2, 10,
    34, 159, 11, 13,
    46, 190, 23, 11,
    57, 227, 39, 9,
    69, 239, 70, 14,
    81, 249, 109, 22,
    92, 252, 147, 37,
    104, 252, 191, 55,
    115, 252, 223, 85,
    127, 255, 255, 123,
    139, 222, 244, 95,
    150, 194, 233, 69,
    162, 135, 209, 77,
    173, 90, 186, 84,
    185, 49, 162, 84,
    197, 23, 139, 85,
    208, 10, 97, 102,
    220, 3, 63, 120,
    231, 9, 38, 100,
    243, 19, 19, 82,
    255, 19, 19, 82};

// Gradient palette "Spectral_gp", originally from
//
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/jjg/polarity/tn/Spectral.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 40 bytes of program space.

DEFINE_GRADIENT_PALETTE(Spectral_gp){
    0, 73, 1, 8,
    31, 159, 11, 13,
    63, 227, 39, 9,
    95, 249, 109, 22,
    127, 252, 191, 55,
    127, 194, 233, 69,
    159, 90, 186, 84,
    191, 23, 139, 85,
    223, 3, 63, 120,
    255, 19, 19, 82};

// Gradient palette "srtYlOrRd04_gp", originally from
//
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/jjg/serrate/seq/tn/srtYlOrRd04.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 32 bytes of program space.

DEFINE_GRADIENT_PALETTE(srtYlOrRd04_gp){
    0, 252, 156, 19,
    63, 255, 255, 103,
    63, 249, 69, 6,
    127, 252, 156, 19,
    127, 217, 10, 1,
    191, 249, 69, 6,
    191, 117, 0, 2,
    255, 217, 10, 1};

// Gradient palette "earth_gp", originally from
// // http://soliton.vm.bytemark.co.uk/pub/cpt-city/gist/tn/earth.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 960 bytes of program space.

// Gradient palette "wr_gp", originally from
// // http://soliton.vm.bytemark.co.uk/pub/cpt-city/esdb/tn/wr.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 32 bytes of program space.

DEFINE_GRADIENT_PALETTE(wr_gp){
    0, 255, 255, 255,
    63, 255, 255, 255,
    63, 210, 255, 255,
    127, 210, 255, 255,
    127, 101, 255, 255,
    191, 101, 255, 255,
    191, 42, 117, 255,
    255, 42, 117, 255};

// Gradient palette "dr_gp", originally from
// // http://soliton.vm.bytemark.co.uk/pub/cpt-city/esdb/tn/dr.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 24 bytes of program space.

DEFINE_GRADIENT_PALETTE(dr_gp){
    0, 255, 255, 255,
    84, 255, 255, 255,
    84, 177, 187, 180,
    170, 177, 187, 180,
    170, 90, 105, 93,
    255, 90, 105, 93};

// Gradient palette "slopese_gp", originally from
//
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/esdb/tn/slopese.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 32 bytes of program space.

DEFINE_GRADIENT_PALETTE(slopese_gp){
    0, 255, 255, 105,
    63, 255, 255, 105,
    63, 171, 156, 105,
    127, 171, 156, 105,
    127, 142, 55, 12,
    191, 142, 55, 12,
    191, 11, 0, 0,
    255, 11, 0, 0};

// Gradient palette "bhw1_bluee_gp", originally from
//
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_bluee.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 12 bytes of program space.

// Gradient palette "bhw1_hello_gp", originally from
//
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_hello.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 32 bytes of program space.

DEFINE_GRADIENT_PALETTE(bhw1_hello_gp){
    0, 237, 156, 197,
    35, 244, 189, 230,
    56, 255, 255, 255,
    79, 244, 189, 230,
    109, 237, 156, 197,
    160, 121, 255, 255,
    196, 255, 255, 255,
    255, 121, 255, 255};

// Gradient palette "bhw2_36_gp", originally from
//
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw2/tn/bhw2_36.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 12 bytes of program space.

// Gradient palette "bhw2_35_gp", originally from
//
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw2/tn/bhw2_35.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

// Gradient palette "bhw2_thanks_gp", originally from
//
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw2/tn/bhw2_thanks.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 36 bytes of program space.

// Gradient palette "bhw3_16_gp", originally from
//
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw3/tn/bhw3_16.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

// DEFINE_GRADIENT_PALETTE( bhw3_16_gp ) {
//    0, 115,203,252,
//   38,  21, 38, 34,
//   63, 104,133,133,
//   94, 255,255,255,
//  130,  66, 90, 85,
//  191,  10, 40, 53,
//  255,   2,  6,  4};
