#ifndef KEYMAP_H
#define KEYMAP_H

#define state_t bool
#define UP false
#define DOWN true

void handle_keychange(uint8_t row, uint8_t col, state_t state);

#endif //KEYMAP_H
