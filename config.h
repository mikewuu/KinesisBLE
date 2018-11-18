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
#define VBAT_PIN        A7
#define USB_PIN         A6

#define SPI_SS_PIN      27

#define LED_CAPS_PIN    29
#define LED_NUM_PIN     28
#define LED_SCR_PIN     26
#define LED_KEY_PIN     25  

#define ROW_PINS { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }
#define COL_PINS { 4, 3, 2, 16, 15, 7, 11}

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
#define USB_FULL_MIN_MV 4978 


#endif
