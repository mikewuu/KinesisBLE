#ifndef BLUETOOTH_H
#define BLUETOOTH_H

void send_report_keyboard();
void register_keydown(uint16_t keycode);
void register_keyup(uint16_t keycode);
void init_bluetooth();
bool is_bluetooth_connected();
void clear_bluetooth_bonds();

#endif //BLUETOOTH_H
