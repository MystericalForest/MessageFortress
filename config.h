#ifndef CONFIG_H
#define CONFIG_H

// ===== PIN DEFINITIONER =====
// LED pins (PWM pins anbefales)
#define CODE_LED_1_PIN      2
#define CODE_LED_2_PIN      3
#define LOCK_LED_1_PIN      4
#define LOCK_LED_2_PIN      5

// Status LED pins
#define STATUS_RED_PIN      8
#define STATUS_GREEN_PIN    7
#define CONNECTION_PIN      9

// Button pins
#define BUTTON_1_PIN        22
#define BUTTON_2_PIN        23
#define BUTTON_3_PIN        24
#define BUTTON_4_PIN        25
#define BUTTON_5_PIN        26
#define BUTTON_6_PIN        27
#define BUTTON_7_PIN        28
#define BUTTON_8_PIN        29

// Display pins (TM1637)
#define DISPLAY_CLK_PIN     10
#define DISPLAY_DIO_PIN     11

// ===== TIMING KONSTANTER =====
#define SWITCH_DELAY        5000    // Skift mellem låst/kode visning (ms)
#define FADE_DELAY          15      // LED fade hastighed (ms)
#define BLINK_INTERVAL      500     // Status LED blink interval (ms)

// ===== LED FADE INDSTILLINGER =====
#define BRIGHTNESS_MIN      64      // Minimum lysstyrke
#define BRIGHTNESS_MAX      255     // Maximum lysstyrke
#define FADE_STEP           2       // Fade step størrelse

// ===== DISPLAY INDSTILLINGER =====
#define DISPLAY_BRIGHTNESS  0x0f    // Display lysstyrke (0x00-0x0f)

// ===== ADGANGSKODE =====
#define ACCESS_CODE         253672  // Adgangskode for at låse systemet op

// ===== KODE KONFIGURATION =====
// Alle 256 koder for 8-button kombinationer (0-255)
// Koder genereret systematisk for escaperoom brug

// Kode array - indeks matcher button kombination
const int CODES[256] = {
  1000, 1001, 1002, 1003, 1004, 1005, 1006, 1007, 1008, 1009,  // 0-9
  1010, 1011, 1012, 1013, 1014, 1015, 1016, 1017, 1018, 1019,  // 10-19
  1020, 1021, 1022, 1023, 1024, 1025, 1026, 1027, 1028, 1029,  // 20-29
  1030, 1031, 1032, 1033, 1034, 1035, 1036, 1037, 1038, 1039,  // 30-39
  1040, 1041, 1042, 1043, 1044, 1045, 1046, 1047, 1048, 1049,  // 40-49
  1050, 1051, 1052, 1053, 1054, 1055, 1056, 1057, 1058, 1059,  // 50-59
  1060, 1061, 1062, 1063, 1064, 1065, 1066, 1067, 1068, 1069,  // 60-69
  1070, 1071, 1072, 1073, 1074, 1075, 1076, 1077, 1078, 1079,  // 70-79
  1080, 1081, 1082, 1083, 1084, 1085, 1086, 1087, 1088, 1089,  // 80-89
  1090, 1091, 1092, 1093, 1094, 1095, 1096, 1097, 1098, 1099,  // 90-99
  
  2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009,  // 100-109
  2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2019,  // 110-119
  2020, 2021, 2022, 2023, 2024, 2025, 2026, 2027, 2028, 2029,  // 120-129
  2030, 2031, 2032, 2033, 2034, 2035, 2036, 2037, 2038, 2039,  // 130-139
  2040, 2041, 2042, 2043, 2044, 2045, 2046, 2047, 2048, 2049,  // 140-149
  2050, 2051, 2052, 2053, 2054, 2055, 2056, 2057, 2058, 2059,  // 150-159
  2060, 2061, 2062, 2063, 2064, 2065, 2066, 2067, 2068, 2069,  // 160-169
  2070, 2071, 2072, 2073, 2074, 2075, 2076, 2077, 2078, 2079,  // 170-179
  2080, 2081, 2082, 2083, 2084, 2085, 2086, 2087, 2088, 2089,  // 180-189
  2090, 2091, 2092, 2093, 2094, 2095, 2096, 2097, 2098, 2099,  // 190-199
  
  3000, 3001, 3002, 3003, 3004, 3005, 3006, 3007, 3008, 3009,  // 200-209
  3010, 3011, 3012, 3013, 3014, 3015, 3016, 3017, 3018, 3019,  // 210-219
  3020, 3021, 3022, 3023, 3024, 3025, 3026, 3027, 3028, 3029,  // 220-229
  3030, 3031, 3032, 3033, 3034, 3035, 3036, 3037, 3038, 3039,  // 230-239
  3040, 3041, 3042, 3043, 3044, 3045, 3046, 3047, 3048, 3049,  // 240-249
  3050, 3051, 3052, 3053, 3054, 9999                           // 250-255
};

#endif