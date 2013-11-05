#ifndef  mars_INC
#define  mars_INC
#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include "execute_instruction.h"

void add_warrior(struct mars* mars, struct instruction* list_instruction, unsigned short size_instruction); 

void spend_cycle(struct mars* mars);

void execute_warrior(struct mars* mars, struct warrior* current_warrior);

void turn_thread_warrior(struct warrior* warrior);

void execute_instruction(struct mars* mars, unsigned short index_instruction, struct warrior* current_warrior);

int warrior_is_dead(struct warrior* warrior);

struct instruction get_instruction(struct mars* mars, unsigned short index_instruction);

struct instruction* get_instruction_pointer(struct mars* mars, unsigned short index_instruction);

void kill_current_thread(struct warrior* warrior);

unsigned short get_referenced_instruction(struct mars* mars, unsigned short index_instruction, struct instruction instruction, char field); 	

unsigned short get_referenced_instruction_indirect(struct mars* mars, unsigned short index_instruction, int field_instruction, char addressing);

char check_zero(unsigned char modifier, struct instruction instruction);
#endif
