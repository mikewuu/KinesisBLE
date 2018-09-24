#ifndef KEYMAP_H
#define KEYMAP_H

#define state_t bool
#define UP false        // LOW = 0 = FALSE = KEY UP
#define DOWN true       // HIGH = 1 = TRUE = KEY DOWN

void handle_keychange(uint8_t row, uint8_t col, state_t state);

#endif //KEYMAP_H
