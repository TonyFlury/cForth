/*
 * memoryinternal.h
 *
 *  Created on: 4 Feb 2021
 *      Author: tony
 */

#ifndef SRC_INCLUDES_MEMORYINTERNAL_H_
#define SRC_INCLUDES_MEMORYINTERNAL_H_

typedef int32_t cell;

/* System Var Offsets */
#define DL 0 	/* The Last Entry in the dictionary */
#define HERE 1 /* The next new Entry in the dictionary */
#define SP_START 2 /* The start of the stack - grows down - equivalent to SP0 */
#define SP 3 /* Equivalent to SP */
#define RT_START 4 /* The start of the return stack - grows up - equivalent to RT0 */
#define RT 5 /* The top of the return stack  - equivalent to RT */
#define VARS 6 /* The start of the user variables section */
#define BUFFER 7 /* The start of the buffer section */

#define SYSVARSIZE 8 /* The size of the system var section */

/* User Vars offsets */
#define TIB 0 /* Start of the input buffer - TIB */
#define TIB_LEN 1 /* Length of TIB - TIB# */
#define IN 2 /* The offset in to the TIB of the next character - >IN */
#define BLK 3 /* The location of the block being loaded */

#define USERVARSIZE 4 /* The size of the User var section */

#endif /* SRC_INCLUDES_MEMORYINTERNAL_H_ */
