/**
* \file libk/string/strlen.c
* \brief Returns the length of a string
* \author Artinel <artinel@proton.me>
* \version 0.0.1
* \date 2025-03-08
* \copyright GNU Public License V3
*/

#include <string.h>
#include <stddef.h>

/**
* Returns the length of a string
*
* \param str The string that its size will be returned
*
* \return strlen returns the length of the string
*/

size_t strlen(const char* str){
        size_t len = 0;
        while(str[len]){
                len++;
        }

        return len;
}
