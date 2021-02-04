/*
 ============================================================================
 Name        : cForth.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "includes/memorymap.h"

int main(void) {
	int ret;
	ret = create_memory_map( 50000 /* memory allocation in bytes */
								);
	if (ret != 0)
		exit(-1);
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	return 0;
}
