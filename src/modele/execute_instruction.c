#include "execute_instruction.h"

void execute_DAT(struct mars* mars, unsigned short index_instruction, struct warrior* current_warrior, struct instruction instruction)
{
	//Even DAT <50, <60 will decrement the addresses in addition to killing the process.
	get_referenced_instruction(mars, index_instruction, instruction, FIELD_A);
	get_referenced_instruction(mars, index_instruction, instruction, FIELD_B);
	kill_current_thread(current_warrior);
}

void execute_SPL(struct mars* mars, unsigned short index_instruction, struct warrior* current_warrior, struct instruction instruction)
{
	unsigned short index_new_thread = get_referenced_instruction(mars, index_instruction, instruction, FIELD_A);
	if(instruction.addressing_a == ADDR_IMMEDIATE)
	{
		index_new_thread = index_instruction;
	}
	current_warrior->size_position_thread++;
	current_warrior->position_thread = realloc(current_warrior->position_thread, current_warrior->size_position_thread);	
	current_warrior->position_thread[current_warrior->size_position_thread - 1] = index_new_thread;
}

void execute_MOV(struct mars* mars, unsigned short index_instruction, struct warrior* current_warrior, struct instruction instruction)
{
	unsigned short index_origine = get_referenced_instruction(mars, index_instruction, instruction, FIELD_A);
	unsigned short index_destination = get_referenced_instruction(mars, index_instruction, instruction, FIELD_B);
	struct instruction* destination = get_instruction_pointer(mars, index_destination);
	struct instruction* origine = get_instruction_pointer(mars, index_origine);
	if(instruction.addressing_a == ADDR_IMMEDIATE)
	{
		origine = &instruction;
	}
	if(instruction.addressing_b == ADDR_IMMEDIATE)
	{
		destination = get_instruction_pointer(mars, index_instruction);
	}
	switch(instruction.modifier_action)
	{
		case MODIFIER_AB:
			destination->field_b = origine->field_a;
			break;
		case MODIFIER_BA:
			destination->field_a = origine->field_b;
			break;
		case MODIFIER_F:
			destination->field_a = origine->field_a;
			destination->field_b = origine->field_b;
			break;
		case MODIFIER_X:
			destination->field_a = origine->field_b;
			destination->field_b = origine->field_a;
			break;
		case MODIFIER_I:
			*destination = *origine;
			break;
		case MODIFIER_A:
			destination->field_a = origine->field_a;
			break;
		case MODIFIER_B:
			destination->field_b = origine->field_b;
			break;
	};
}

void execute_JMP(struct mars* mars, unsigned short index_instruction, struct warrior* current_warrior, struct instruction instruction)
{
	unsigned short index_next = get_referenced_instruction(mars, index_instruction, instruction, FIELD_A);
	if(instruction.addressing_a == ADDR_IMMEDIATE)
	{
		index_next = index_instruction;
	}
	current_warrior->position_thread[current_warrior->next_thread] = index_next;	
	current_warrior->has_change_current_thread = 1;
}

void execute_ADD(struct mars* mars, unsigned short index_instruction, struct warrior* current_warrior, struct instruction instruction)
{
	execute_arithmetique_operation(mars, index_instruction, current_warrior, instruction, NULL, &arithmetique_add);
}

void execute_SUB(struct mars* mars, unsigned short index_instruction, struct warrior* current_warrior, struct instruction instruction)
{
	execute_arithmetique_operation(mars, index_instruction, current_warrior, instruction, NULL, &arithmetique_sub);
}

void execute_MUL(struct mars* mars, unsigned short index_instruction, struct warrior* current_warrior, struct instruction instruction)
{
	execute_arithmetique_operation(mars, index_instruction, current_warrior, instruction, NULL, &arithmetique_mul);
}

void execute_DIV(struct mars* mars, unsigned short index_instruction, struct warrior* current_warrior, struct instruction instruction)
{
	char check_zero = 0;	
	execute_arithmetique_operation(mars, index_instruction, current_warrior, instruction, &check_zero, &arithmetique_div);
	if(check_zero != 0)
	{
		kill_current_thread(current_warrior);
	}
}

void execute_MOD(struct mars* mars, unsigned short index_instruction, struct warrior* current_warrior, struct instruction instruction)
{
	char check_zero = 0;	
	execute_arithmetique_operation(mars, index_instruction, current_warrior, instruction, &check_zero, &arithmetique_mod);
	if(check_zero != 0)
	{
		kill_current_thread(current_warrior);
	}
}

short arithmetique_add(short origine, short destination, struct mars* mars)
{
	return (origine + destination) % mars->size_memory;
}

short arithmetique_sub(short origine, short destination, struct mars* mars)
{
	return (destination - origine) % mars->size_memory;
}

short arithmetique_mul(short origine, short destination, struct mars* mars)
{
	return (destination * origine) % mars->size_memory;
}

short arithmetique_div(short origine, short destination, struct mars* mars)
{
	return (destination / origine) % mars->size_memory;
}

short arithmetique_mod(short origine, short destination, struct mars* mars)
{
	return (destination % origine) % mars->size_memory;
}

void execute_arithmetique_operation(struct mars* mars, unsigned short index_instruction, struct warrior* current_warrior, struct instruction instruction, char* check_zero_flag, short (*arithmetique_function)(short, short, struct mars*) )
{
	unsigned short index_origine = get_referenced_instruction(mars, index_instruction, instruction, FIELD_A);
	unsigned short index_destination = get_referenced_instruction(mars, index_instruction, instruction, FIELD_B);
	struct instruction* destination = get_instruction_pointer(mars, index_destination);
	struct instruction* origine = get_instruction_pointer(mars, index_origine);
	if(instruction.addressing_a == ADDR_IMMEDIATE)
	{
		origine = &instruction;
	}
	if(instruction.addressing_b == ADDR_IMMEDIATE)
	{
		destination = get_instruction_pointer(mars, index_instruction);
	}
	if(check_zero_flag != NULL)
	{
		*check_zero_flag = check_zero(instruction.modifier_action, *origine);
		if(*check_zero_flag == 1)
		{
			return;
		}
	}
	switch(instruction.modifier_action)
	{
		case MODIFIER_AB:
			destination->field_b = arithmetique_function(origine->field_a, destination->field_b, mars);
			break;
		case MODIFIER_BA:
			destination->field_a = arithmetique_function(origine->field_b, destination->field_a, mars);
			break;
		case MODIFIER_F:
			destination->field_a = arithmetique_function(origine->field_a, destination->field_a, mars);
			destination->field_b = arithmetique_function(origine->field_b, destination->field_b, mars);
			break;
		case MODIFIER_X:
			destination->field_a = arithmetique_function(origine->field_b, destination->field_a, mars);
			destination->field_b = arithmetique_function(origine->field_a, destination->field_b, mars);
			break;
		case MODIFIER_A:
			destination->field_a = arithmetique_function(origine->field_a, destination->field_a, mars);
			break;
		case MODIFIER_B:
			destination->field_b = arithmetique_function(origine->field_b, destination->field_b, mars);
			break;
	};
}
