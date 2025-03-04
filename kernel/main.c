#include <stdio.h>
#include <string.h>
#include <kernel/tty.h>

#define MY_NAME "Artinel"
#define ADDR 0xB8000

void kernel_main(void){
	printk("Hello My name is %s and i am %x years old\n", MY_NAME, ADDR);	
}
