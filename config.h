#ifndef CONFIG_H
#define CONFIG_H


/**
 * DEBUG MODE
 */
//#define DEBUG

/**
 * Serial Baudrate
 * 
 * If you're printing out to serial when debugging and things
 * are all jumbled, make sure you've set the serial monitor 
 * baudrate to the same as the one below.
 */
#define USB_BAUDRATE 115200

/**
 * Pin Numbers
 */
#define VBAT_PIN        A6    // Previously A7 (unused)
#define USB_PIN         A7    // labelled AREF, Previously A6

#define SPI_SS_PIN      5

#define LED_CAPS_PIN    A3    // Previously 8
#define LED_NUM_PIN     A4    // Previously 
#define LED_SCR_PIN     9     // Previously 26
#define LED_KEY_PIN     6     // Previously 25

#define ROW_PINS { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }
#define COL_PINS { A2, A1, A0, 13, 12, 11, 10}

/**
 * Keyboard Matrix
 */
#define ROWS 15
#define COLS 7

/**
 * Debounce Loops
 * 
 * Run through the loop 'x' times, to 'debounce' keys. ie. make sure a key
 * is pressed for the duration of at least 'x' loops until we 
 * recognize it. 
 */
#define DEBOUNCING_DELAY 2

/**
 * Sleep Timer
 * 
 * Minutes until deep-sleep. Keyboard will wake up on any keypress.
 */
 #define MINS_BEFORE_SHUTDOWN 15

 /**
  * Battery Indicator Timer
  * 
  * How many minutes to show the battery level until the LED(s) turn off.
  */
#define MINS_SHOW_BATTERY_LED 3

/**
 * USB Charging Voltage
 * 
 * If we read a usb voltage above this, we'll assume the battery is 
 * full. The voltage is lower when charging.
 * 
 */
#define USB_FULL_MIN_MV 4990 

/**
 * Rest Timer
 * 
 * Flash LED(s) after WORK_INTERVAL_MINS of work to indicate
 * that it's time to take a break. Must take a break for at 
 * least REST_INTERVAL_SECS to reset the timer.
 */
#define REST_TIMER
#define WORK_INTERVAL_MINS    20
#define REST_INTERVAL_SECS    60
#define WORK_TIMEOUT_MINS     20
//#define REST_AUTO_BREAKS

#endif
