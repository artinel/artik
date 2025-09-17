#ifndef __KERNEL_PIT_H_
#define __KERNEL_PIT_H_

#include <stdint.h>

#define PIT_COUNT_PER_SEC		18

void init_pit(void);
void pit_set_count(uint16_t c);
uint16_t pit_get_count(void);
void pit_set_callback(void (*callback)(void));
void pit_remove_callback(void);

#endif
