#ifndef KEYCODES_H
#define KEYCODES_H

#define IN_KEYBOARD_RANGE(kc) ((kc >> 12) == 0)
#define IN_CONSUMER_RANGE(kc) ((kc >> 12) == 1)
#define IN_SPECIAL_RANGE(kc)  ((kc >> 12) == 2)


#define K_NO   0x0000
#define K_Q    0x0004
#define K_B    0x0005
#define K_C    0x0006
#define K_D    0x0007
#define K_E    0x0008
#define K_F    0x0009
#define K_G    0x000A
#define K_H    0x000B
#define K_I    0x000C
#define K_J    0x000D
#define K_K    0x000E
#define K_L    0x000F
#define K_COMM 0x0010
#define K_N    0x0011
#define K_O    0x0012
#define K_P    0x0013
#define K_A    0x0014
#define K_R    0x0015
#define K_S    0x0016
#define K_T    0x0017
#define K_U    0x0018
#define K_V    0x0019
#define K_Z    0x001A
#define K_X    0x001B
#define K_Y    0x001C
#define K_W    0x001D
#define K_AMP  0x001E
#define K_EACU 0x001F
#define K_QUOT 0x0020
#define K_APOS 0x0021
#define K_LPRN 0x0022
#define K_SECT 0x0023
#define K_EGRV 0x0024
#define K_EXLM 0x0025
#define K_CCED 0x0026
#define K_AGRV 0x0027
#define K_ENT  0x0028
#define K_ESC  0x0029
#define K_BSPC 0x002A
#define K_TAB  0x002B
#define K_SPC  0x002C
#define K_RPRN 0x002D
#define K_MINS 0x002E
#define K_CIRC 0x002F
#define K_DLR  0x0030
#define K_GRV  0x0032
#define K_M    0x0033
#define K_UGRV 0x0034
#define K_LESS 0x0035
#define K_SCLN 0x0036
#define K_COLN 0x0037
#define K_EQL  0x0038
#define K_CAPS 0x0039
#define K_F1   0x003A
#define K_F2   0x003B
#define K_F3   0x003C
#define K_F4   0x003D
#define K_F5   0x003E
#define K_F6   0x003F
#define K_F7   0x0040
#define K_F8   0x0041
#define K_F9   0x0042
#define K_F10  0x0043
#define K_F11  0x0044
#define K_F12  0x0045
#define K_RGHT 0x004F
#define K_LEFT 0x0050
#define K_DOWN 0x0051
#define K_UP   0x0052
#define K_AT   0x0064
#define K_CTRL 0x0100
#define K_SHFT 0x0200
#define K_OPT  0x0400
#define K_CMD  0x0800
#define K_HYPR (K_CTRL | K_SHFT | K_OPT | K_CMD)

#define K_MUTE K_F12
#define K_VOLU K_F12
#define K_VOLD K_F11
#define K_PREV K_F7
#define K_PLAY K_F8
#define K_NEXT K_F9

#define K_BRID K_F1
#define K_BRIU K_F2

#define ______ 0x2000
#define K_LOW  0x2001
#define K_RAIS 0x2002
#define K_HOME 0x2003
#define K_LSFT 0x2004
#define K_RSFT 0x2005

#define K_HASH (K_SHFT | K_AT)
#define K_1    (K_SHFT | K_AMP)
#define K_2    (K_SHFT | K_EACU)
#define K_3    (K_SHFT | K_QUOT)
#define K_4    (K_SHFT | K_APOS)
#define K_5    (K_SHFT | K_LPRN)
#define K_6    (K_SHFT | K_SECT)
#define K_7    (K_SHFT | K_EGRV)
#define K_8    (K_SHFT | K_EXLM)
#define K_9    (K_SHFT | K_CCED)
#define K_0    (K_SHFT | K_AGRV)
#define K_UNDS (K_SHFT | K_MINS)
#define K_UMLT (K_SHFT | K_CIRC)
#define K_ASTR (K_SHFT | K_DLR)
#define K_PERC (K_SHFT | K_UGRV)
#define K_PND  (K_SHFT | K_GRV)
#define K_GRTR (K_SHFT | K_LESS)
#define K_QUES (K_SHFT | K_COMM)
#define K_DOT  (K_SHFT | K_SCLN)
#define K_SLSH (K_SHFT | K_COLN)
#define K_PLUS (K_SHFT | K_EQL)
#define K_DEG  (K_SHFT | K_RPRN)

#define K_LCBR (K_OPT  | K_LPRN)
#define K_RCBR (K_OPT  | K_RPRN)
#define K_EURO (K_OPT  | K_DLR)
#define K_TILD (K_OPT  | K_N)

#define K_LBRC (K_SHFT | K_OPT | K_LPRN)
#define K_RBRC (K_SHFT | K_OPT | K_RPRN)
#define K_PIPE (K_SHFT | K_OPT | K_L)
#define K_BSLS (K_SHFT | K_OPT | K_COLN)


#define K_TERM (K_HYPR | K_W)
#define K_SFRI (K_HYPR | K_X)
#define K_MAIL (K_HYPR | K_C)
#define K_CAL  (K_HYPR | K_V)
#define K_ITNS (K_HYPR | K_B)
#define K_SP1  (K_CMD  | K_AMP)
#define K_SP2  (K_CMD  | K_EACU)
#define K_SP3  (K_CMD  | K_QUOT)
#define K_SP4  (K_CMD  | K_APOS)

#define K_FULL (K_CMD | K_CTRL | K_F)
#define K_CAPF (K_CMD | K_SHFT | K_3)
#define K_CAPR (K_CMD | K_SHFT | K_4)
#define K_CHAR (K_CMD | K_CTRL | K_SPC)

#endif //KEYCODES_H
