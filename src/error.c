/*
 * error.c
 *
 *  Created on: 2 Feb 2021
 *      Author: tony
 *
 * Functions and data to raise and manage error conditions
 *
 */

#include <stdio.h>
#include <string.h>

int error_raised;

int raise_error(char *message)
{
	fprintf(stderr, "%s\n", message );
	error_raised = -1;
	return -1;
}
