/**
* \file kernel/main.c
* \brief The main function of kernel
* \author Artinel <artinel@proton.me>
* \version 0.0.1
* \date 2025-03-08
* \copyright GNU Public License V3
*/

#include<stdio.h>

int num = 2;

__attribute__ ((constructor)) void foo(void)
{
	printk("foo is running and printf is available at this point\n");
}

void kernel_main(void){
	printk("Number is : %d\n", num);
}
