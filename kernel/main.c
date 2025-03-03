#include <kernel/tty.h>

void kernel_main(void){
        tty_init();
        tty_set_bg(VGA_COLOR_WHITE);
        tty_set_fg(VGA_COLOR_RED);
        tty_write("HELLO", 5);
}
