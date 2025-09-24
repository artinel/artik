#ifndef __IO_PORTS_H_
#define __IO_PORTS_H_

/* PIC Ports */
#define PIC_MASTER_CMD		0x20
#define PIC_MASTER_DATA		0x21
#define PIC_SLAVE_CMD		0xA0
#define PIC_SLAVE_DATA		0xA1

/* PIT Ports */
#define PIT_CHNL_0		0x40
#define PIT_CHNL_1		0x41
#define PIT_CHNL_2		0x42
#define PIT_MODE		0x43

/* PS2 Keyboard Ports */
#define PS2_KB_DATA		0x60
#define PS2_KB_STATUS		0x64
#define PS2_KB_CMD		0x64

#endif
