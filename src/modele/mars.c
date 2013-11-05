#include "mars.h"

void add_warrior(struct mars* mars, struct instruction* list_instruction, unsigned short size_instruction)
{
	if(size_instruction >= mars->size_memory)
	{
		return;
	}
	//choose random index and put the warrior in the memory
	//check if there is enough space
	unsigned short new_index = rand() % mars->size_memory;
	//check if it's a good index
	//create a warrior and realloc a_warrior
	if(mars->a_warrior == NULL)
	{
		mars->a_warrior = malloc(sizeof(struct warrior));
	}
	else
	{
		mars->a_warrior = realloc(mars->a_warrior, mars->size_a_warrior + 1);
	}
	mars->size_a_warrior++;
	//puts the warrion in memory
	struct instruction* current_instruction = NULL;
	for(int i = 0; i < size_instruction; i++)
	{
		current_instruction = get_instruction_pointer(mars, new_index + i);
		*current_instruction = list_instruction[i];	
	}
	//create warrior
	struct warrior* current_warrior = &(mars->a_warrior[mars->size_a_warrior - 1]);	
	current_warrior->position_thread = malloc(sizeof(unsigned short));
	current_warrior->position_thread[0] = new_index;
	current_warrior->size_position_thread = 1;
	current_warrior->next_thread = 0;
	current_warrior->size_warrior = size_instruction;
}

void spend_cycle(struct mars* mars)
{
	for(int i = 0; i < mars->size_a_warrior; i++)
	{
		if(warrior_is_dead(&(mars->a_warrior[i])) == 0)
		{
			execute_warrior(mars, &(mars->a_warrior[i]));
		}
	}
	mars->current_cycle++;
}

void execute_warrior(struct mars* mars, struct warrior* current_warrior)
{
	if(current_warrior->next_thread < 0)
	{
		return;
	}
	unsigned short index_instruction = current_warrior->position_thread[current_warrior->next_thread];
	current_warrior->has_change_current_thread = 0;
	execute_instruction(mars, index_instruction, current_warrior);
	//if the index of instruction has change, that's because something modify it lik a JMP instruction
	if(current_warrior->has_change_current_thread == 0)
	{
		current_warrior->position_thread[current_warrior->next_thread]++;
	}
	turn_thread_warrior(current_warrior);	
}

void turn_thread_warrior(struct warrior* warrior)
{
	if(warrior->size_position_thread > 0)
	{
		warrior->next_thread = (warrior->next_thread + 1) % warrior->size_position_thread;	
	}
}

void execute_instruction(struct mars* mars, unsigned short index_instruction, struct warrior* current_warrior)
{
	struct instruction instruction = get_instruction(mars, index_instruction);
	switch(instruction.action)
	{
		case DAT:
			execute_DAT(mars, index_instruction, current_warrior, instruction);
		break;
		case MOV :
			execute_MOV(mars, index_instruction, current_warrior, instruction);
		break;
		case ADD:
			execute_ADD(mars, index_instruction, current_warrior, instruction);
		break;
		case SUB:
			execute_SUB(mars, index_instruction, current_warrior, instruction);
		break;
		case MUL:
			execute_MUL(mars, index_instruction, current_warrior, instruction);
		break;
		case DIV:
			execute_DIV(mars, index_instruction, current_warrior, instruction);
		break;
		case MOD:
			execute_MOD(mars, index_instruction, current_warrior, instruction);
		break;
		case JMP:
			execute_JMP(mars, index_instruction, current_warrior, instruction);
		break;
		case JMZ:
		break;
		case JMN:
		break;
		case DJN:
		break;
		case SPL:
			execute_SPL(mars, index_instruction, current_warrior, instruction);
		break;
		case CMP:
		break;
		case SEQ:
		break;
		case SNE:
		break;
		case SLT:
		break;
		case LDP:
		break;
		case STP:
		break;
		case NOP:
		break;
	};
}

int warrior_is_dead(struct warrior* warrior)
{
	//If it doesn't have a thread anymore
	return (warrior->size_position_thread == 0);
}

struct instruction get_instruction(struct mars* mars, unsigned short index_instruction)
{
	return *get_instruction_pointer(mars, index_instruction);
}

struct instruction* get_instruction_pointer(struct mars* mars, unsigned short index_instruction)
{
	index_instruction = index_instruction % mars->size_memory;
	return &(mars->memory[index_instruction]);
}

void kill_current_thread(struct warrior* warrior)
{
	for(int i = warrior->next_thread; i < warrior->size_position_thread - 2; i++)
	{
		warrior->position_thread[i] = warrior->position_thread[i+1];
	} 
	warrior->size_position_thread--;
	if(warrior->size_position_thread > 0)
	{
		warrior->position_thread = realloc(warrior->position_thread, warrior->size_position_thread);
	}
	else if(warrior->size_position_thread == 0)
	{
		free(warrior->position_thread);
	}
}

char check_zero(unsigned char modifier, struct instruction instruction)
{
	switch(modifier)
	{
		case MODIFIER_AB:
		case MODIFIER_A:
			if(instruction.field_a == 0)
			{
				return 1;
			} 
			break;
		case MODIFIER_BA:
		case MODIFIER_B:
			if(instruction.field_b == 0)
			{
				return 1;
			} 
			break;
		case MODIFIER_F:
		case MODIFIER_X:
			if(instruction.field_a == 0 || instruction.field_b == 0)
			{
				return 1;
			} 
			break;
	};
	return 0;
}

unsigned short get_referenced_instruction_indirect(struct mars* mars, unsigned short index_instruction, int field_instruction, char addressing)
{
			//MOV 0, @1
			//DAT 0, -1
			// get instruction at (index_instruction + field_instruction);
			struct instruction* instruct = get_instruction_pointer(mars, index_instruction + field_instruction);
			//switch sur le type d'adressage
			int value_field = 0;
			switch(addressing)
			{
				case ADDR_INDIRECT_A:
					value_field = instruct->field_a;
				break;
				case ADDR_INDIRECT_A_PREDECREMENT:
					instruct->field_a--;
					value_field = instruct->field_a;
				break;
				case ADDR_INDIRECT_A_POSTDECREMENT:
					value_field = instruct->field_a;
					instruct->field_a--;
				break;
				case ADDR_INDIRECT_B:
					value_field = instruct->field_b;
				break;
				case ADDR_INDIRECT_B_PREDECREMENT:
					instruct->field_b--;
					value_field = instruct->field_b;
				break;
				case ADDR_INDIRECT_B_POSTDECREMENT:
					value_field = instruct->field_b;
					instruct->field_b--;
				break;
			}
			//récupére le bon champ
			//addition avec index_instruction
			return index_instruction + value_field + field_instruction;
}

unsigned short get_referenced_instruction(struct mars* mars, unsigned short index_instruction, struct instruction instruction, char field)
{
	unsigned short index_referenced_instruction = 0;
	int field_instruction;
	unsigned char addressing;
	if(field == FIELD_A)
	{
		field_instruction = instruction.field_a;
		addressing = instruction.addressing_a;
	}	
	else
	{
		field_instruction = instruction.field_b;
		addressing = instruction.addressing_b;
	}
	if(addressing == ADDR_DIRECT)
	{
			index_referenced_instruction = index_instruction + field_instruction;
	}
	else if(addressing != ADDR_IMMEDIATE)
	{
		index_referenced_instruction = get_referenced_instruction_indirect(mars, index_instruction, field_instruction, addressing);
	}
	return index_referenced_instruction;
}


