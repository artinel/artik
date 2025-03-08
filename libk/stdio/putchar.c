/**
* \file libk/stdio/putchar.c
* \brief Print a character on the screen
* \author Artinel <artinel@proton.me>
* \version 0.0.1
* \date 2025-03-08
* \copyright GNU Public License V3
*/

#include <stdio.h>
#include <kernel/tty.h>

/**
* Print a character on the screen.
*
* \param ic The character that will be printed on the screen
*
* \return putchar returns the printed character
*
* \bug putchar does not check if the input parameter is a valid character or not.
*
* \sa tty_putchar
*/

int putchar(int ic){
        char c = (char) ic;
        tty_putchar(c);
        return ic;
}
