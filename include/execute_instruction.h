#ifndef  execute_instruction_INC
#define  execute_instruction_INC
#include "mars.h"
#include "header.h"

void execute_DAT(struct mars* mars, unsigned short index_instruction, struct warrior* current_warrior, struct instruction instruction);
void execute_SPL(struct mars* mars, unsigned short index_instruction, struct warrior* current_warrior, struct instruction instruction);
void execute_MOV(struct mars* mars, unsigned short index_instruction, struct warrior* current_warrior, struct instruction instruction);
void execute_JMP(struct mars* mars, unsigned short index_instruction, struct warrior* current_warrior, struct instruction instruction);
void execute_ADD(struct mars* mars, unsigned short index_instruction, struct warrior* current_warrior, struct instruction instruction);
void execute_SUB(struct mars* mars, unsigned short index_instruction, struct warrior* current_warrior, struct instruction instruction);
void execute_MUL(struct mars* mars, unsigned short index_instruction, struct warrior* current_warrior, struct instruction instruction);
void execute_DIV(struct mars* mars, unsigned short index_instruction, struct warrior* current_warrior, struct instruction instruction);
void execute_MOD(struct mars* mars, unsigned short index_instruction, struct warrior* current_warrior, struct instruction instruction);

void execute_arithmetique_operation(struct mars* mars, unsigned short index_instruction, struct warrior* current_warrior, struct instruction instruction, char* check_zero_flag, short (*arithmetique_function)(short, short, struct mars*) );
short arithmetique_add(short origine, short destination, struct mars* mars);
short arithmetique_sub(short origine, short destination, struct mars* mars);
short arithmetique_mul(short origine, short destination, struct mars* mars);
short arithmetique_div(short origine, short destination, struct mars* mars);
short arithmetique_mod(short origine, short destination, struct mars* mars);
#endif
