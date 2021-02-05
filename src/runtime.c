/*
 * runtime.c
 *
 *  Created on: 3 Feb 2021
 *      Author: tony
 *
 *  The runtime: executes the p-code.
 *
 *
 *  All instructions are two cells wide (64 bits) - the first is the opcode and the 2nd is the data
 *
 *  The virtual machine has a single accumulator for mathematical results
 *
 *  Opcodes :
 *
 *  -------- data loading and storage ----------
 *  LoadFrom Address - Load the data from the address into the accumulator
 *  Load Data - Load the value into the accumulator
 *  StoreTo Address - Store the data from the Accumulator into the address
 *
 *  -------- Operations ----------------
 *  <OP>From Address - *Address <op> Acc
 *  <OP>Data - Data <op> Acc
 *
 *  <OP> = Add, Sub, Mul, Div, MOD, LT, EQ, GT, LTE, GTE, NE, AND, OR, XOR
 *
 *  Negation
 *
 *  NOT Address - Logical NOT of contents of address loaded into Accumulator
 *  NEG Addresss - Numeric Negation of contents of address loaded into Accumulator
 *
 *  --------- COntrol Flow ---------
 *  Branch Offset - Jump a given number of instructions forward or back
 *  CondBranch Offset - Jump a given number of instructions if Top of stack value is True
 *
 *  JUMP Address - Set the IP to the new address - pushes current IP to return stack
 *  RET - Pops an previous IP from the stack and sets the IP to that value.
 *  QUIT - Clears the Returns stack and sets IP to the last value on the stack
 *
 *  Encoding :
 *
 *  of the 32 bits on each instruction :
 *
 *  Top byte is always 01010101 0x55- this is a validation check
 *  2nd & 3rd byte is the instruction
 *  4th byte is Flag as to operator is Absolute Address, Relative Address or Data
 *  	Data move and Store
 *    	    2nd byte: 00000001 : 0x01
 *  	    3rd byte :
 *  				00000001 : Load 0x01
 *  				00000010 : Store 0x02
 *     Operations
 *          2nd byte 00000010 		0x02
 *          3rd byte
 *          		00000001 Add   0x01
 *          		00000010 Sub   0x02
 *          		00000100 Mul   0x04
 *          		00000101 Div   0x05
 *          		00000110 Mod   0x07
 *          		00001000 LT    0x08
 *          		00001001 GT	   0x09
 *          		00001010 LTE   0x0A
 *          		00001011 GTE   0x0B
 *          		00001100 EQ    0x0C
 *          		00001101 NE    0x0D
 *          		00010000 AND   0x10
 *          		00010010 OR	   0x12
 *          		00010011 XOR   0x13
 *          		00100000 NOT   0x20
 *          		00100001 NEG   0x21
 *
 *     Flow COntrol
 *          2nd byte 00000100 		0x04
 *			3rd byte
 *					 00000001		0x01 Branch Offset
 *					 00000010		0x02 Cond Branch Offset
 *					 00000100		0x04 JMP
 *					 00001000		0x08 RET
 *					 00010000		0x10 QUIT
 */

/* Need the memory offsets */
#include "includes/memoryinternal.h"


/* Code written for 32 bit cells */


/* Shift to move the relevant byte n to Low byte */
#define BYTE_SHIFT(n) (8*n)

/* BYTE MASKS */
#define BYTE_MASK(n) 0xFF << BYTE_SHIFT(n)

/* Confirm value of Byte n is equal to y */
#define BYTE_EQ(n, value) \
	( ((instruction & BYTE_MASK(n)) >> BYTE_SHIFT(n)) == value)

#define BYTE(n, value) \
	(value >> BYTE_SHIFT(n))

/* COnfirm the instruction is valid */
#define CHK_BYTE 0x55

#define CHECKVALID( instruction ) BYTE_EQ(3,CHK_BYTE)

/* Instruction groups */
#define DATA_MOVE_GROUP 0x01
#define OPERATION_GROUP 0x02
#define FLOW_CONTROL_GROUP 0x04

#define EQ_DATA_MOVE_GROUP(instruction) BYTE_EQ(2,DATA_MOVE_GROUP)
#define EQ_OPERATION_GROUP(instruction) BYTE_EQ(2,OPERATION_GROUP)
#define EQ_FLOW_CONTROL_GROUP(instruction) BYTE_EQ(2,FLOW_CONTROL_GROUP)

/* Data modes - byte 0 */
#define ABS_MODE 0x01
#define REL_MODE 0x02
#define DATA_MODE 0x04

#define EQ_ABS_MODE(instruction) BYTE_EQ(0, ABS_MODE)
#define EQ_REL_MODE(instruction) BYTE_EQ(0, REL_MODE)
#define EQ_DATA_MODE(instruction) BYTE_EQ(0, DATA_MODE)

/* Data move instructions - byte 1 */

#define LOAD 0x01
#define STO 0x02

/* Operations instructions - byte 1 */
#define ADD 0x01
#define SUB 0x02
#define MUL 0x04
#define DIV 0x05
#define MOD 0x07
#define LT 0x08
#define GT 0x09
#define LTE 0x0A
#define GTE 0x0B
#define EQ 0x0C
#define NE 0x0D
#define AND 0x10
#define OR 0x12
#define XOR 0x13
#define NOT 0x20
#define NEG 0x21

/* Flow Control - byte 1 */
#define BRANCH 0x01
#define COND 0x02
#define JMP 0x04
#define RET 0x08
#define QUIT 0x10
