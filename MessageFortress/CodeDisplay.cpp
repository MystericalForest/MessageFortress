#include "CodeDisplay.h"

CodeDisplay::CodeDisplay(int btn1, int btn2, int btn3, int btn4, int btn5, int btn6, int btn7, int btn8, int clk, int dio)
  : _btn1(btn1), _btn2(btn2), _btn3(btn3), _btn4(btn4), _btn5(btn5), _btn6(btn6), _btn7(btn7), _btn8(btn8), _clk(clk), _dio(dio), _display(clk, dio),
    _startupActive(false), _startupCount(0), _lastStartupTime(0) {}

void CodeDisplay::begin() {
  pinMode(_btn1, INPUT_PULLUP);
  pinMode(_btn2, INPUT_PULLUP);
  pinMode(_btn3, INPUT_PULLUP);
  pinMode(_btn4, INPUT_PULLUP);
  pinMode(_btn5, INPUT_PULLUP);
  pinMode(_btn6, INPUT_PULLUP);
  pinMode(_btn7, INPUT_PULLUP);
  pinMode(_btn8, INPUT_PULLUP);
  _display.setBrightness(0x0f);
}

int CodeDisplay::readInputs() {
  int a = digitalRead(_btn1);
  int b = digitalRead(_btn2);
  int c = digitalRead(_btn3);
  int d = digitalRead(_btn4);
  int e = digitalRead(_btn5);
  int f = digitalRead(_btn6);
  int g = digitalRead(_btn7);
  int h = digitalRead(_btn8);
  return (h << 7) | (g << 6) | (f << 5) | (e << 4) | (d << 3) | (c << 2) | (b << 1) | a;
}

int CodeDisplay::getCode() {
  static const int codes[256] = {
    1000, 1001, 1002, 1003, 1004, 1005, 1006, 1007, 1008, 1009,
    1010, 1011, 1012, 1013, 1014, 1015, 1016, 1017, 1018, 1019,
    1020, 1021, 1022, 1023, 1024, 1025, 1026, 1027, 1028, 1029,
    1030, 1031, 1032, 1033, 1034, 1035, 1036, 1037, 1038, 1039,
    1040, 1041, 1042, 1043, 1044, 1045, 1046, 1047, 1048, 1049,
    1050, 1051, 1052, 1053, 1054, 1055, 1056, 1057, 1058, 1059,
    1060, 1061, 1062, 1063, 1064, 1065, 1066, 1067, 1068, 1069,
    1070, 1071, 1072, 1073, 1074, 1075, 1076, 1077, 1078, 1079,
    1080, 1081, 1082, 1083, 1084, 1085, 1086, 1087, 1088, 1089,
    1090, 1091, 1092, 1093, 1094, 1095, 1096, 1097, 1098, 1099,
    
    2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009,
    2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2019,
    2020, 2021, 2022, 2023, 2024, 2025, 2026, 2027, 2028, 2029,
    2030, 2031, 2032, 2033, 2034, 2035, 2036, 2037, 2038, 2039,
    2040, 2041, 2042, 2043, 2044, 2045, 2046, 2047, 2048, 2049,
    2050, 2051, 2052, 2053, 2054, 2055, 2056, 2057, 2058, 2059,
    2060, 2061, 2062, 2063, 2064, 2065, 2066, 2067, 2068, 2069,
    2070, 2071, 2072, 2073, 2074, 2075, 2076, 2077, 2078, 2079,
    2080, 2081, 2082, 2083, 2084, 2085, 2086, 2087, 2088, 2089,
    2090, 2091, 2092, 2093, 2094, 2095, 2096, 2097, 2098, 2099,
    
    3000, 3001, 3002, 3003, 3004, 3005, 3006, 3007, 3008, 3009,
    3010, 3011, 3012, 3013, 3014, 3015, 3016, 3017, 3018, 3019,
    3020, 3021, 3022, 3023, 3024, 3025, 3026, 3027, 3028, 3029,
    3030, 3031, 3032, 3033, 3034, 3035, 3036, 3037, 3038, 3039,
    3040, 3041, 3042, 3043, 3044, 3045, 3046, 3047, 3048, 3049,
    3050, 3051, 3052, 3053, 3054, 3055
  };
  
  int input = readInputs();
  if (input >= 0 && input <= 255) {
    return codes[input];
  }
  return 0000;
}

void CodeDisplay::update() {
  if (_startupActive) {
    updateStartup();
  } else {
    int code = getCode();
    _display.showNumberDec(code, false);
  }
}

void CodeDisplay::updateStartup() {
  unsigned long now = millis();
  if (now - _lastStartupTime >= 1000) {
    _startupCount++;
    if (_startupCount <= 10) {
      _display.showNumberDec(_startupCount, false);
      _lastStartupTime = now;
    } else {
      _startupActive = false;
    }
  }
}

void CodeDisplay::startStartup() {
  _startupActive = true;
  _startupCount = 0;
  _lastStartupTime = millis();
  _display.showNumberDec(1, false);
  _startupCount = 1;
}

void CodeDisplay::turnOff() {
  _display.setBrightness(0x00, false);
  _display.clear();
}

void CodeDisplay::turnOn() {
  _display.setBrightness(0x0f, true);
  startStartup();
}
