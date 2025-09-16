#include <kernel/pic.h>
#include <io/ports.h>
#include <io/iox.h>

void pic_remap(uint8_t master_offset, uint8_t slave_offset) {
	 /* Start initialization sequence (in cascade mode) */	
	outb(PIC_MASTER_CMD, ICW1_INIT | ICW1_ICW4);
	io_wait();

	outb(PIC_SLAVE_CMD, ICW1_INIT | ICW1_ICW4);
	io_wait();

	/* ICW2 : Master PIC vector offset */
	outb(PIC_MASTER_DATA, master_offset);
	io_wait();

	/* ICW2 : Slave PIC vector offset */
	outb(PIC_SLAVE_DATA, slave_offset);
	io_wait();

	/* ICW3 : Tell master that there is a slave PIC in IRQ2 */
	outb(PIC_MASTER_DATA, 1 << CASCADE_IRQ);
	io_wait();

	/* ICW3 : Tell slave PIC its cascade identity (0000 00010) */
	outb(PIC_SLAVE_DATA, 2);
	io_wait();

	/* ICW4 : have the PICs use 8086 mode (and not 8080 mode) */
	outb(PIC_MASTER_DATA, ICW4_8086);
	io_wait();
	outb(PIC_SLAVE_DATA, ICW4_8086);
	io_wait();

	/* Unmask both PICs */
	outb(PIC_MASTER_DATA, 0);
	outb(PIC_SLAVE_DATA, 0);
}

void pic_disable(void) {
	outb(PIC_MASTER_DATA, 0xFF);
	outb(PIC_SLAVE_DATA, 0xFF);
}

void pic_send_eoi(uint8_t irq) {
	if (irq >= 8) {
		outb(PIC_SLAVE_CMD, PIC_EOI);
	}

	outb(PIC_MASTER_CMD, PIC_EOI);
}
