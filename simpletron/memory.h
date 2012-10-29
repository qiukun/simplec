#ifndef MEMORY_H
#define MEMORY_H

#define MEMORYSIZE 100

extern int memory[MEMORYSIZE];

/**
 * get_opcode:
 * @ins: A instruction
 * @returns: The operation code of the instruction
 *
 * Get the operation code from a instruction
 */
extern int get_opcode(int ins);

/**
 * get_oprand:
 * @ins: A instruction
 * @returns: The operand of the instruction
 * 
 * Get the operand from a instruction
 */
extern int get_oprand(int ins);

/**
 * get_ins:
 * @opcode: A operation code
 * @oprand: A operand
 *
 * Get the instruction from operation code and oprand.
 */
extern int get_ins(int opcode, int oprand);

#endif
