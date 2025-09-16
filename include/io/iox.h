#ifndef __IO_IOX_H_
#define __IO_IOX_H_

#include <stdint.h>

void outb(uint16_t port, uint8_t data);
uint8_t inb(uint16_t port);
void io_wait(void);

#endif
