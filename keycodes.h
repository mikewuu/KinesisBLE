#ifndef KEYCODES_H
#define KEYCODES_H

#define K_NONE  0x0000
#define ______  (K_NONE)

/**
 * Modifier Masks
 * Use the first byte for modifiers. This allows for bit-shifting 
 * to combine modifiers without checking to see if the key
 * pressed was a modifier or regular key.
 */
#define K_LCTL  0x0100
#define K_LSFT  0x0200
#define K_LALT  0x0400
#define K_LCMD  0x0800 // LEFT CMD
#define K_RCTL  0x1000
#define K_RSFT  0x2000
#define K_RALT  0x4000
#define K_RCMD  0x8000 // Right CMD

#define K____A 0x0004 // Keyboard a and A
#define K____B 0x0005 // Keyboard b and B
#define K____C 0x0006 // Keyboard c and C
#define K____D 0x0007 // Keyboard d and D
#define K____E 0x0008 // Keyboard e and E
#define K____F 0x0009 // Keyboard f and F
#define K____G 0x000a // Keyboard g and G
#define K____H 0x000b // Keyboard h and H
#define K____I 0x000c // Keyboard i and I
#define K____J 0x000d // Keyboard j and J
#define K____K 0x000e // Keyboard k and K
#define K____L 0x000f // Keyboard l and L
#define K____M 0x0010 // Keyboard m and M
#define K____N 0x0011 // Keyboard n and N
#define K____O 0x0012 // Keyboard o and O
#define K____P 0x0013 // Keyboard p and P
#define K____Q 0x0014 // Keyboard q and Q
#define K____R 0x0015 // Keyboard r and R
#define K____S 0x0016 // Keyboard s and S
#define K____T 0x0017 // Keyboard t and T
#define K____U 0x0018 // Keyboard u and U
#define K____V 0x0019 // Keyboard v and V
#define K____W 0x001a // Keyboard w and W
#define K____X 0x001b // Keyboard x and X
#define K____Y 0x001c // Keyboard y and Y
#define K____Z 0x001d // Keyboard z and Z

#define K____1 0x001e // Keyboard 1 and !
#define K____2 0x001f // Keyboard 2 and @
#define K____3 0x0020 // Keyboard 3 and #
#define K____4 0x0021 // Keyboard 4 and $
#define K____5 0x0022 // Keyboard 5 and %
#define K____6 0x0023 // Keyboard 6 and ^
#define K____7 0x0024 // Keyboard 7 and &
#define K____8 0x0025 // Keyboard 8 and *
#define K____9 0x0026 // Keyboard 9 and (
#define K____0 0x0027 // Keyboard 0 and )

#define K_ENTR 0x0028 // Keyboard Return (ENTER)
#define K_ESCP 0x0029 // Keyboard ESCAPE
#define K_BSPC 0x002a // Keyboard DELETE (Backspace)
#define K__TAB 0x002b // Keyboard Tab
#define K_SPCE 0x002c // Keyboard Spacebar
#define K_MINS 0x002d // Keyboard - and _
#define K_EQUL 0x002e // Keyboard = and +
#define K_LBRC 0x002f // Keyboard [ and {
#define K_RBRC 0x0030 // Keyboard ] and }
#define K_BSLH 0x0031 // Keyboard \ and |
#define K_TILD 0x0032 // Keyboard Non-US # and ~
#define K_SCLN 0x0033 // Keyboard ; and :
#define K_APST 0x0034 // Keyboard ' and "
#define K_GRVE 0x0035 // Keyboard ` and ~
#define K_CMMA 0x0036 // Keyboard , and <
#define K__DOT 0x0037 // Keyboard . and >
#define K_SLSH 0x0038 // Keyboard / and ?
#define K_CLCK 0x0039 // Keyboard Caps Lock

#define K___F1 0x003a // Keyboard F1
#define K___F2 0x003b // Keyboard F2
#define K___F3 0x003c // Keyboard F3
#define K___F4 0x003d // Keyboard F4
#define K___F5 0x003e // Keyboard F5
#define K___F6 0x003f // Keyboard F6
#define K___F7 0x0040 // Keyboard F7
#define K___F8 0x0041 // Keyboard F8
#define K___F9 0x0042 // Keyboard F9
#define K__F10 0x0043 // Keyboard F10
#define K__F11 0x0044 // Keyboard F11
#define K__F12 0x0045 // Keyboard F12

#define K_PRSC 0x0046 // Keyboard Print Screen
#define K_SLCK 0x0047 // Keyboard Scroll Lock
#define K_PAUS 0x0048 // Keyboard Pause
#define K_INST 0x0049 // Keyboard Insert
#define K_HOME 0x004a // Keyboard Home
#define K_PGUP 0x004b // Keyboard Page Up
#define K_DLTE 0x004c // Keyboard Delete Forward
#define K__END 0x004d // Keyboard End
#define K_PGDN 0x004e // Keyboard Page Down
#define K_RGHT 0x004f // Keyboard Right Arrow
#define K_LEFT 0x0050 // Keyboard Left Arrow
#define K_DOWN 0x0051 // Keyboard Down Arrow
#define K___UP 0x0052 // Keyboard Up Arrow

#define K_PGRM 0x0000    // Kinesis progm key
#define K_KYPD 0x0000     // Kinesis keypad key

// Kinesis Left Thumb Keys
#define K__SL1 (K_EQUL)
#define K__SL2 (K_LCTL)
#define K__SL3 (K_RAISE)  // default: Delete Key
#define K__SL4 (K_BSPC)
#define K__SL5 (K_LALT)
#define K__SL6 (K_LCMD)

// Kinesis Right Thumb Keys
#define K__SR1 (K_MINS)
#define K__SR2 (K_RALT)
#define K__SR3 (K_ENTR)
#define K__SR4 (K_SPCE)
#define K__SR5 (K_RCTL)
#define K__SR6 (K_RCMD)

// Layer Keys
#define K_RAISE 0x9001

#endif //KEYCODES_H
