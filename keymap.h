#ifndef KEYMAP_H
#define KEYMAP_H

#define state_t bool
#define UP false        // LOW = 0 = FALSE = KEY UP
#define DOWN true       // HIGH = 1 = TRUE = KEY DOWN

int handle_keychange(uint8_t row, uint8_t col, state_t state);

/**
 * CUSTOM COMMANDS
 */
#define COMMAND_SHUTDOWN  0

#endif //KEYMAP_H
