#ifndef __IO_PS2_KEYBOARD_H_
#define __IO_PS2_KEYBOARD_H_

void init_ps2_keyboard();
void ps2_keyboard_get_raw(void (*callback)(uint8_t, bool));
void ps2_keyboard_get_char(void (*callback)(uint8_t));

#endif
