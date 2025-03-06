/**
* \file kernel/tty.c
* \brief The general TTY implementation
* \author Artinel <artinel@proton.me> 
* \version 0.0.1
* \date 2025-03-06
* \copyright GNU Public License V3
*/

#include <kernel/tty.h>
#include <kernel/vga.h>

/**
* Initialize the TTY.
* 
* \sa vga_init
*/

void tty_init(){
        vga_init();
}

/**
* Print a character on the screen.
*
* \param c The character that will be printed on the screen
*
* \sa vga_putchar
*/

void tty_putchar(unsigned char c){
        vga_putchar(c);
}

/**
* Print a string on the screen.
*
* \param data The string that will be printed on the screen
* \param size Size of the string
*
* \sa vga_write
*/

void tty_write(const char* data, size_t size){
        vga_write(data, size);
}

/**
* Set background color for TTY.
*
* \param color Background color
*
* \sa vga_set_bg vga_color
*/

void tty_set_bg(enum vga_color color){
        vga_set_bg(color);
}

/**
* Set foreground color for TTY.
*
* \param color Foreground color
*
* \sa vga_set_fg vga_color
*/

void tty_set_fg(enum vga_color color){
        vga_set_fg(color);
}
