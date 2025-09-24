#ifndef __KERNEL_PIT_H_
#define __KERNEL_PIT_H_

#include <stdint.h>

#define PIT_COUNT_PER_SEC		18

void init_pit(void);
void pit_set_count(uint32_t c);
uint32_t pit_get_count(void);
void pit_set_callback(void (*callback)(void));
void pit_remove_callback(void);
void pit_start(void);
void pit_stop(void);

#endif
