#ifndef KEYCODES_H
#define KEYCODES_H


#define K_NONE   0x0000
#define ______     (K_NONE)

/**
 * Modifier Masks
 * Use the first byte for modifiers. This allows for bit-shifting 
 * to combine modifiers without checking to see if the key
 * pressed was a modifier or regular key.
 */
#define K_MOD_LCTRL  0x0100
#define K_MOD_LSHIFT 0x0200
#define K_MOD_LALT   0x0400
#define K_MOD_LMETA  0x0800 // LEFT CMD
#define K_MOD_RCTRL  0x1000
#define K_MOD_RSHIFT 0x2000
#define K_MOD_RALT   0x4000
#define K_MOD_RMETA  0x8000 // Right CMD

#define K_A 0x0004 // Keyboard a and A
#define K_B 0x0005 // Keyboard b and B
#define K_C 0x0006 // Keyboard c and C
#define K_D 0x0007 // Keyboard d and D
#define K_E 0x0008 // Keyboard e and E
#define K_F 0x0009 // Keyboard f and F
#define K_G 0x000a // Keyboard g and G
#define K_H 0x000b // Keyboard h and H
#define K_I 0x000c // Keyboard i and I
#define K_J 0x000d // Keyboard j and J
#define K_K 0x000e // Keyboard k and K
#define K_L 0x000f // Keyboard l and L
#define K_M 0x0010 // Keyboard m and M
#define K_N 0x0011 // Keyboard n and N
#define K_O 0x0012 // Keyboard o and O
#define K_P 0x0013 // Keyboard p and P
#define K_Q 0x0014 // Keyboard q and Q
#define K_R 0x0015 // Keyboard r and R
#define K_S 0x0016 // Keyboard s and S
#define K_T 0x0017 // Keyboard t and T
#define K_U 0x0018 // Keyboard u and U
#define K_V 0x0019 // Keyboard v and V
#define K_W 0x001a // Keyboard w and W
#define K_X 0x001b // Keyboard x and X
#define K_Y 0x001c // Keyboard y and Y
#define K_Z 0x001d // Keyboard z and Z

#define K_1 0x001e // Keyboard 1 and !
#define K_2 0x001f // Keyboard 2 and @
#define K_3 0x0020 // Keyboard 3 and #
#define K_4 0x0021 // Keyboard 4 and $
#define K_5 0x0022 // Keyboard 5 and %
#define K_6 0x0023 // Keyboard 6 and ^
#define K_7 0x0024 // Keyboard 7 and &
#define K_8 0x0025 // Keyboard 8 and *
#define K_9 0x0026 // Keyboard 9 and (
#define K_0 0x0027 // Keyboard 0 and )

#define K_ENTER 0x0028 // Keyboard Return (ENTER)
#define K_ESC 0x0029 // Keyboard ESCAPE
#define K_BACKSPACE 0x002a // Keyboard DELETE (Backspace)
#define K_TAB 0x002b // Keyboard Tab
#define K_SPACE 0x002c // Keyboard Spacebar
#define K_MINUS 0x002d // Keyboard - and _
#define K_EQUAL 0x002e // Keyboard = and +
#define K_LEFTBRACE 0x002f // Keyboard [ and {
#define K_RIGHTBRACE 0x0030 // Keyboard ] and }
#define K_BACKSLASH 0x0031 // Keyboard \ and |
#define K_HASHTILDE 0x0032 // Keyboard Non-US # and ~
#define K_SEMICOLON 0x0033 // Keyboard ; and :
#define K_APOSTROPHE 0x0034 // Keyboard ' and "
#define K_GRAVE 0x0035 // Keyboard ` and ~
#define K_COMMA 0x0036 // Keyboard , and <
#define K_DOT 0x0037 // Keyboard . and >
#define K_SLASH 0x0038 // Keyboard / and ?
#define K_CAPSLOCK 0x0039 // Keyboard Caps Lock

#define K_F1 0x003a // Keyboard F1
#define K_F2 0x003b // Keyboard F2
#define K_F3 0x003c // Keyboard F3
#define K_F4 0x003d // Keyboard F4
#define K_F5 0x003e // Keyboard F5
#define K_F6 0x003f // Keyboard F6
#define K_F7 0x0040 // Keyboard F7
#define K_F8 0x0041 // Keyboard F8
#define K_F9 0x0042 // Keyboard F9
#define K_F10 0x0043 // Keyboard F10
#define K_F11 0x0044 // Keyboard F11
#define K_F12 0x0045 // Keyboard F12

#define K_SYSRQ 0x0046 // Keyboard Print Screen
#define K_SCROLLLOCK 0x0047 // Keyboard Scroll Lock
#define K_PAUSE 0x0048 // Keyboard Pause
#define K_INSERT 0x0049 // Keyboard Insert
#define K_HOME 0x004a // Keyboard Home
#define K_PAGEUP 0x004b // Keyboard Page Up
#define K_DELETE 0x004c // Keyboard Delete Forward
#define K_END 0x004d // Keyboard End
#define K_PAGEDOWN 0x004e // Keyboard Page Down
#define K_RIGHT 0x004f // Keyboard Right Arrow
#define K_LEFT 0x0050 // Keyboard Left Arrow
#define K_DOWN 0x0051 // Keyboard Down Arrow
#define K_UP 0x0052 // Keyboard Up Arrow

#define K_PROGRAM 0x0000    // Kinesis progm key
#define K_KEYPAD 0x0000     // Kinesis keypad key

// Kinesis Left Thumb Keys
#define K_SL1 (K_EQUAL)
#define K_SL2 (K_MOD_LCTRL)
#define K_SL3 (K_TAB)
#define K_SL4 (K_BACKSPACE)
#define K_SL5 (K_MOD_LALT)
#define K_SL6 (K_MOD_LMETA)

// Kinesis Right Thumb Keys
#define K_SR1 (K_MINUS)
#define K_SR2 (K_MOD_RALT)
#define K_SR3 (K_ENTER)
#define K_SR4 (K_SPACE)
#define K_SR5 (K_MOD_RCTRL)
#define K_SR6 (K_MOD_RMETA)

#endif //KEYCODES_H
