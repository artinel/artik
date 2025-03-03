#include <kernel/tty.h>

void tty_init(){
        vga_init();
}

void tty_putchar(unsigned char c){
        vga_putchar(c);
}

void tty_write(const char* data, size_t size){
        vga_write(data, size);
}

void tty_set_bg(enum vga_color color){
        vga_set_bg(color);
}

void tty_set_fg(enum vga_color color){
        vga_set_fg(color);
}
