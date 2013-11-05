#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include "header.h"
#include "parseFile.h"
#include "mars.h"
#include "mars_initialisation.h"

void print_instrction(struct instruction instruction)
{
	printf ( "%d %d, %d\n", instruction.action, instruction.field_a, instruction.field_b);
}

void print_memory(struct mars* mars)
{
	
	for (int i = 0; i < mars->size_memory; i++ ) 
	{
		print_instrction(mars->memory[i]);	
	}
}

void test_function(void)
{
	struct instruction instruction;
	instruction.action = DAT;
	instruction.modifier_action = MODIFIER_I;
	instruction.addressing_a = ADDR_DIRECT;
	instruction.field_a = 0;
	instruction.addressing_b = ADDR_DIRECT;
	instruction.field_b = 0;
	struct mars* mars = create_mars(10, 10, &instruction); 
	struct instruction list_instruction[3];
	list_instruction[0].action = DIV;
	list_instruction[0].modifier_action = MODIFIER_AB;
	list_instruction[0].addressing_a = ADDR_IMMEDIATE;
	list_instruction[0].field_a = 0;
	list_instruction[0].addressing_b = ADDR_DIRECT;
	list_instruction[0].field_b = 4;
	list_instruction[1].action = NOP;
	list_instruction[1].addressing_a = ADDR_DIRECT;
	list_instruction[1].field_a = 1;
	list_instruction[1].addressing_b = ADDR_DIRECT;
	list_instruction[1].field_b = 1;
	list_instruction[2].action = MOV;
	list_instruction[2].modifier_action = MODIFIER_I;
	list_instruction[2].addressing_a = ADDR_DIRECT;
	list_instruction[2].field_a = 0;
	list_instruction[2].addressing_b = ADDR_DIRECT;
	list_instruction[2].field_b = 1;
	add_warrior(mars, list_instruction, 3); 
	print_memory(mars);
	printf("\n");
	spend_cycle(mars);
	spend_cycle(mars);
	spend_cycle(mars);
	spend_cycle(mars);
	spend_cycle(mars);
	print_memory(mars);
	destroy_mars(mars);
}

int main(int argc, char** argv)
{
	printf("[i] Begin\n");
	test_function();
	int opth = 0;
	struct instruction initial_instruction;
	unsigned short max_cycle = 8000;
	unsigned short size_memory = 400;	
	while( (opth = getopt(argc, argv, "hp:c:i:m:")) != -1)
	{
		switch(opth)
		{
			case 'h':
				printf("-h\tPrint help\n");
				printf("-p <file name>\tLoad this file as processus for corewar\n");
				printf ( "-c <cycle>\tChange the number of cycle. (default : 8000)\n" );
				printf ( "-i <instruction>\tSet the init instruction of memory (\"random\" to randomize memory)\n" );
				printf ( "-m <size>\tSet the size of the memory (default : 400)\n" );
				return -1;
				break;
			case 'p':
				//Add to an array
				break;
			case 'c':
				max_cycle = atoi(optarg); 
				break;
			case 'i':
				initial_instruction = parse_line(optarg);
				break;
		}
	}

	printf("[i] End\n");
	return 0;
}
