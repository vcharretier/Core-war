#ifndef  header_INC
#define  header_INC
struct warrior
{
	//Store the position of each thread
	unsigned short* position_thread;
	unsigned short size_position_thread;
	//Store the next thread which will be execute
	unsigned short next_thread; 
	unsigned short size_warrior;
	char has_change_current_thread;
};


//Here is a list of all the instructions used in Redcode:
//http://vyznev.net/corewar/guide.html
//DAT -- data (kills the process)
//MOV -- move (copies data from one address to another)
//ADD -- add (adds one number to another)
//SUB -- subtract (subtracts one number from another)
//MUL -- multiply (multiplies one number with another)
//DIV -- divide (divides one number with another)
//MOD -- modulus (divides one number with another and gives the remainder)
//JMP -- jump (continues execution from another address)
//JMZ -- jump if zero (tests a number and jumps to an address if it's 0)
//JMN -- jump if not zero (tests a number and jumps if it isn't 0)
//DJN -- decrement and jump if not zero (decrements a number by one, and jumps unless the result is 0)
//SPL -- split (starts a second process at another address)
//CMP -- compare (same as SEQ)
//SEQ -- skip if equal (compares two instructions, and skips the next instruction if they are equal)
//SNE -- skip if not equal (compares two instructions, and skips the next instruction if they aren't equal)
//SLT -- skip if lower than (compares two values, and skips the next instruction if the first is lower than the second)
//LDP -- load from p-space (loads a number from private storage space)
//STP -- save to p-space (saves a number to private storage space)
//NOP -- no operation (does nothing)
#define DAT 0
#define MOV 1
#define ADD 2
#define SUB 4
#define MUL 5
#define DIV 6
#define MOD 7
#define JMP 8
#define JMZ 9
#define JMN 10
#define DJN 11
#define SPL 12
#define CMP 13
#define SEQ 14
#define SNE 15
#define SLT 16
#define LDP 17
#define STP 18
#define NOP 19

//Adressing mode
//# -- immediate (exemple : add #4, 3 ; add value 4 to the second fiel of instruction 3)
//$ -- direct (the $ may be omitted)
//* -- A-field indirect (exemple : add #4, @3 ; add value 4 to the second fiel of instruction of the second field of instruction 3. (the instruction to modify is store in instruction 3)
//@ -- B-field indirect
//{ -- A-field indirect with predecrement
//< -- B-field indirect with predecrement
//} -- A-field indirect with postincrement
//> -- B-field indirect with postincrement
#define ADDR_IMMEDIATE 0
#define ADDR_DIRECT 1
#define ADDR_INDIRECT_A 2
#define ADDR_INDIRECT_A_PREDECREMENT 3
#define ADDR_INDIRECT_A_POSTDECREMENT 4
#define ADDR_INDIRECT_B 5
#define ADDR_INDIRECT_B_PREDECREMENT 6
#define ADDR_INDIRECT_B_POSTDECREMENT 7

#define FIELD_A 1
#define FIELD_B 2


#define MODIFIER_A 1
#define MODIFIER_B 2
#define MODIFIER_AB 3
#define MODIFIER_BA 4
#define MODIFIER_F 5
#define MODIFIER_X 6
#define MODIFIER_I 7
struct instruction
{
	unsigned char action;
	unsigned char modifier_action;
	unsigned char addressing_a;
	short field_a;
	unsigned char addressing_b;
	short field_b;
};
struct mars
{
	struct warrior* a_warrior;
	unsigned short size_a_warrior;
	struct instruction* memory;
	unsigned short size_memory;
	unsigned int current_cycle;
	unsigned int max_cycle;
};


#endif
