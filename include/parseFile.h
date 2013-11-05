#include <stdio.h>
#include "header.h"

// ^ *(JMP|ADD|MOV) *(\#|@|{)([:digit:]), *(\#|@|{)([:digit:]) *;?.*$
struct instruction* parse_file(char* filename, unsigned short* size_instruction);

struct instruction parse_line(char* line);
