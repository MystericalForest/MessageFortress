#ifndef CONFIG_H
#define CONFIG_H

/**
 * CONFIG.H - Konfigurationsfil for Message Fortress
 * 
 * Indeholder alle pin definitioner, timing konstanter og
 * system konfigurationer for escaperoom krypterings-devicen.
 */

// ===== PIN DEFINITIONER =====

// LED pins (PWM pins anbefales)
#define CODE_LED_1_PIN      2
#define CODE_LED_2_PIN      3
#define LOCK_LED_1_PIN      4
#define LOCK_LED_2_PIN      5

// Status LED pins
#define STATUS_RED_PIN      8
#define STATUS_GREEN_PIN    7
#define KEY_PIN             12
#define CONNECTION_PIN      9

// Button pins (8 knapper)
#define BUTTON_1_PIN        42
#define BUTTON_2_PIN        43
#define BUTTON_3_PIN        44
#define BUTTON_4_PIN        45
#define BUTTON_5_PIN        46
#define BUTTON_6_PIN        47
#define BUTTON_7_PIN        48
#define BUTTON_8_PIN        49

// Display pins (TM1637)
#define DISPLAY_CLK_PIN     10
#define DISPLAY_DIO_PIN     11

// ===== TIMING KONSTANTER =====
#define SWITCH_DELAY        5000    // Skift mellem låst/kode visning (ms)
#define FADE_DELAY          15      // LED fade hastighed (ms)
#define BLINK_INTERVAL      500     // Status LED blink interval (ms)

// ===== STARTUP ANIMATION TIMING =====
#define LCD_STARTUP_DELAY   750     // LCD startup animation interval (ms)
#define CODE_STARTUP_DELAY  500     // CodeDisplay startup animation interval (ms)

// ===== LED FADE INDSTILLINGER =====
#define BRIGHTNESS_MIN      64      // Minimum lysstyrke
#define BRIGHTNESS_MAX      255     // Maximum lysstyrke
#define FADE_STEP           2       // Fade step størrelse

// ===== DISPLAY INDSTILLINGER =====
#define DISPLAY_BRIGHTNESS  0x0f    // Display lysstyrke (0x00-0x0f)

// ===== ADGANGSKODE =====
#define ACCESS_CODE         "324373"  // Adgangskode til hovedsystem

#endif