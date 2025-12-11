#include "CodeDisplay.h"
#include "config.h"

CodeDisplay::CodeDisplay(int btn1, int btn2, int btn3, int btn4, int btn5, int btn6, int btn7, int btn8, int clk, int dio)
  : _btn1(btn1), _btn2(btn2), _btn3(btn3), _btn4(btn4), _btn5(btn5), _btn6(btn6), _btn7(btn7), _btn8(btn8), _clk(clk), _dio(dio), _display(clk, dio),
    _state(OFF), _startupCount(0), _lastStartupTime(0) {}

void CodeDisplay::begin() {
  pinMode(_btn1, INPUT_PULLUP);
  pinMode(_btn2, INPUT_PULLUP);
  pinMode(_btn3, INPUT_PULLUP);
  pinMode(_btn4, INPUT_PULLUP);
  pinMode(_btn5, INPUT_PULLUP);
  pinMode(_btn6, INPUT_PULLUP);
  pinMode(_btn7, INPUT_PULLUP);
  pinMode(_btn8, INPUT_PULLUP);
  setState(OFF);
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
    6585, 2748, 1554, 9697, 1840, 2604, 3391, 4844, 6963, 3952,
    9357, 3635, 7343, 9461,	7148,	8824,	2607,	5597,	5297, 5923,
    4485, 5449, 2947, 5083, 7616, 1280, 9717, 3072, 5313, 2122,
    6908, 2348, 4015, 4300, 6479, 4779, 2954, 1065, 1826, 1637,
    9729, 6418, 2221, 1681, 8391, 9702, 5114, 3454, 4934, 5535,
    8249, 7743, 6476, 1150, 4471, 3480, 3077, 1442, 1200, 2588,
    1943, 5099, 7000, 6101, 2929, 4173, 1924, 3218, 5787, 5848,
    4915, 3787, 2516, 3473, 8376, 8321, 8288, 7467, 8926, 9557,
    5883, 9160, 1665, 7701, 1245, 9219, 2131, 2812, 5068, 6882,
    1199, 8051, 3644, 9083, 9043, 6017, 7761, 6643, 9279, 2505,
 
    1317, 2025, 3082, 7143, 7728, 9528, 4889, 3437, 7778, 4507,
    9962, 8960, 3034, 6708, 6427, 1286, 8509, 6697, 7666, 1765,
    9890, 5384, 5653, 5797, 8813, 7379, 6677, 8117, 3698, 8647,
    7254, 7091, 9690, 1301, 8411, 6644, 2230, 8533, 3899, 5661, 
    1396, 6482, 8227, 4083, 2983, 2553, 3957, 7053, 9340, 7826, 
    6931, 9500, 3140, 1994, 3229, 1783, 4225, 3885, 6269, 1432,  
    8511, 5173, 2171, 2140, 8208, 5539, 8065, 6126, 8650, 5560,  
    4281, 3826, 8039, 4558, 2433, 8808, 6505, 8054, 7022, 8761, 
    3044, 3832, 4520, 5755, 6783, 4354, 8781, 9250, 6332, 5729, 
    5904, 4710, 7972, 1304, 6424, 3986, 7881, 8832, 1975, 1048,

    3086, 2691, 2016, 4163, 5519, 7176, 4238, 5798, 4197, 5045, 
    7430, 3212, 2966, 1033, 9013, 9539, 6721, 2375, 8635, 6884, 
    1136, 6592, 7201, 7243, 3214, 2344, 1649, 3927, 3357, 3283,
    9896, 6920, 3089, 2335, 4223, 4255, 8126, 8906, 5742, 7106, 
    9497, 2109, 8075, 9472, 9409, 5719, 3067, 6085, 3800, 9029, 
    5538, 3700, 7014, 5237, 3643, 2345
  };
  
  int input = readInputs();
  if (input >= 0 && input <= 255) {
    return codes[input];
  }
  return 0000;
}

void CodeDisplay::update() {
  switch (_state) {
    case OFF:
      // Vis blanke segmenter
      {
        uint8_t blank[] = {0x00, 0x00, 0x00, 0x00};
        _display.setSegments(blank);
      }
      break;
      
    case STARTUP:
      updateStartup();
      break;
      
    case ON:
      {
        int code = getCode();
        _display.showNumberDec(code, false);
      }
      break;
  }
}

void CodeDisplay::updateStartup() {
  unsigned long now = millis();
  if (now - _lastStartupTime >= CODE_STARTUP_DELAY) {  // 500ms mellem steps
    _startupCount++;
    
    // 25-step segment animation pattern
    uint8_t patterns[][4] = {
      // Første ciffer
      {0x01, 0x00, 0x00, 0x00},  // 1: Digit 1 Top
      {0x02, 0x00, 0x00, 0x00},  // 2: Digit 1 Top-right
      {0x04, 0x00, 0x00, 0x00},  // 3: Digit 1 Bottom-right
      {0x08, 0x00, 0x00, 0x00},  // 4: Digit 1 Bottom
      {0x10, 0x00, 0x00, 0x00},  // 5: Digit 1 Bottom-left
      {0x20, 0x00, 0x00, 0x00},  // 6: Digit 1 Top-left
      // Andet ciffer
      {0x00, 0x01, 0x00, 0x00},  // 7: digit 2 top
      {0x00, 0x02, 0x00, 0x00},  // 8: Digit 2 Top-right
      {0x00, 0x04, 0x00, 0x00},  // 9: Digit 2 Bottom-right
      {0x00, 0x08, 0x00, 0x00},  // 10: Digit 2 Bottom
      {0x00, 0x10, 0x00, 0x00},  // 11: Digit 2 Bottom-left
      {0x00, 0x20, 0x00, 0x00},  // 12: Digit 2 Top-left
      // Tredje ciffer
      {0x00, 0x00, 0x01, 0x00},  // 13: Digit 3 Top
      {0x00, 0x00, 0x02, 0x00},  // 14: Digit 3 Top-right
      {0x00, 0x00, 0x04, 0x00},  // 15: Digit 3 Bottom-right
      {0x00, 0x00, 0x08, 0x00},  // 16: Digit 3 Bottom
      {0x00, 0x00, 0x10, 0x00},  // 17: Digit 3 Bottom-left
      {0x00, 0x00, 0x20, 0x00},  // 18: Digit 3 Top-left
      // Fjerde ciffer
      {0x00, 0x00, 0x00, 0x01},  // 19: digit 4 top
      {0x00, 0x00, 0x00, 0x02},  // 20: Digit 4 Top-right
      {0x00, 0x00, 0x00, 0x04},  // 21: Digit 4 Bottom-right
      {0x00, 0x00, 0x00, 0x08},  // 22: Digit 4 Bottom
      {0x00, 0x00, 0x00, 0x10},  // 23: Digit 4 Bottom-left
      {0x00, 0x00, 0x00, 0x20},  // 24: Digit 4 Top-left
      
      // Afslut  og finale 
      {0x3F, 0x3F, 0x3F, 0x3F},  // 25: Alle digits fulde
      {0x00, 0x00, 0x00, 0x00},  // 26: Blank
      {0x3F, 0x3F, 0x3F, 0x3F}   // 27: Alle fulde igen - klar til drift
    };
    
    if (_startupCount <= 27) {
      _display.setSegments(patterns[_startupCount - 1]);
      _lastStartupTime = now;
    } else {
      setState(OFF);  // Gå til OFF efter startup
    }
  }
}

void CodeDisplay::setState(DisplayState newState) {
  _state = newState;
  
  switch (_state) {
    case OFF:
      {
        uint8_t blank[] = {0x00, 0x00, 0x00, 0x00};
        _display.setSegments(blank);
        _display.setBrightness(0x00, false);
      }
      break;
      
    case STARTUP:
      _display.setBrightness(0x0f, true);
      _startupCount = 0;
      _lastStartupTime = millis();
      break;
      
    case ON:
      _display.setBrightness(0x0f, true);
      break;
  }
}

CodeDisplay::DisplayState CodeDisplay::getState() {
  return _state;
}
