/*
 * memorymap.c
 *
 *  Created on: 2 Feb 2021
 *      Author: tony
 *
 *  Manage the overall memory map and allocations within that
 *
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


#include "includes/memorymap.h"
#include "includes/memoryinternal.h"
#include "includes/error.h"

/* Data definitions and functions to create the base memory map */

cell *memory;


int create_memory_map(size_t total_size)
{
	size_t total_bytes;

	total_bytes = total_size * sizeof(cell);

	memory = (cell *)malloc(total_bytes);
	memset(memory, 0, total_bytes);
	if (memory == NULL)
		return raise_error("Unable to allocate initial memory map");

	return 0;
}
