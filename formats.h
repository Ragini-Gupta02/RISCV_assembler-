#ifndef FORMAT_h
#define FORMAT_h

#include <stdio.h>
unsigned int I_format(int opcode, int fun3, char *operand[]); 

int R_format(int opcode, int fun3, int fun7, char* operands[]);

int S_format(int opcode, int fun3, char* operands[]);

int U_format(int opcode,char* operands[]);

int J_format(int opcode, char* operands[],char(* label_name)[15],int label_pos[], int count,int PC);

#endif