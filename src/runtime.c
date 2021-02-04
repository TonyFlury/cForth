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
 *  of the 64 bits on each instruction :
 *
 *  Top byte is always 01010101 0x55- this is a validation check
 *  2nd & 3rd byte is the instruction
 *  4th byte is Flag as to operator is Address or Data
 *  	Data move and Store
 *    	    2nd byte: 00000001 : 0x01
 *  	    3rd byte :
 *  				00000001 : Load 0x1
 *  				00000010 : Store 0x2
 *     Operations
 *          2nd byte 00000010 		0x02
 *          3rd byte 00000001 Add   0x01
 *          3rd byte 00000010 Sub   0x02
 *          3rd byte 00000100 Mul   0x04
 *          3rd byte 00000101 Div   0x05
 *          3rd byte 00000110 Mod   0x07
 *          3rd byte 00001000 LT    0x08
 *          3rd byte 00001001 GT	0x09
 *          3rd byte 00001010 LTE   0x0A
 *          3rd byte 00001011 GTE   0x0B
 *          3rd byte 00001100 EQ    0x0C
 *          3rd byte 00001101 NE    0x0D
 *          3rd byte 00010000 AND   0x10
 *          3rd byte 00010010 OR	0x12
 *          3rd byte 00010011 XOR	0x13
 *          3rd byte 00100000 NOT	0x20
 *          3rd byte 00100001 NEG	0x20
 *
 */


