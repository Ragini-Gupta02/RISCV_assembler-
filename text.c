#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "formats.h"
#define MAX_LINE_LENGTH 256
 // func3, func7 and opcodes determination.
    int opcode_bin=0;
    int fun3_bin=0;
    int fun7_bin=0;
    char format ='\0';
    int PC=0;

void Machine_Code(char * opcode);
// Function to convert binary string to hexadecimal
char * binaryToHex(char *binaryString) {
    char hexString[9]; // Hexadecimal string will be at most 8 characters long (4 bits per hex digit) + null terminator
    unsigned int decimalValue;

    // Convert binary string to decimal
    decimalValue = strtol(binaryString, NULL, 2);

    // Convert decimal to hexadecimal string
    sprintf(hexString, "%08X", decimalValue);

    // Print the hexadecimal string
    printf("Hexadecimal representation: 0x%s\n", hexString);
    return 0;
}

int parse_instructions(const char *file_m)
{
    char line[100];
    int output = 0;
    // Open the assembly file
    FILE* file = fopen(file_m, "r");
    if (file == NULL) {
        printf("Error opening file2.\n");
        return 1;
    }
    else 
    printf("file in parse_instructions opened\n");
    
    while (fgets(line, sizeof(line), file)) // Read each line from the file
     {
        printf("%s\n",line);
        char *token = strtok(line, " \t\n"); // Tokenize the line
         //   printf("%s",token);
        if (token != NULL)
         {
            printf("%s\t--\n",token);
            if (strcmp(token, "and") == 0) {
               printf("end\n");
                break; 
            }
            
         }
        
                    // Skip till the .text section header
    }
     while (fgets(line, sizeof(line), file)) // Read each line from the file
     {
        char *token = strtok(line, " ,()\t\n"); // Tokenize the line
        char operation[20];
        char *operands[MAX_LINE_LENGTH]; // Initialize to empty string
        int num_operands = 0;
        if (token != NULL)
         {
          if((strstr(token,":"))==NULL) 
          {
            strcpy(operation, token); // First token is the operation
            token = strtok(NULL, " ,()\t\n"); // Get next token(operand)
            
            while (token != NULL) 
            {
                    operands[num_operands++]= token;
                    token = strtok(NULL, " ,()\t\n"); // Get next token     
            }          
        
        Machine_Code(operation) ;

       printf("%s %s %s %c\n\n",operation,operands[0],operands[1],format);
        if(format == 'r'){
            output = R_format(opcode_bin, fun3_bin, fun7_bin, operands);
        }
        else if(format == 'i'){
            output = I_format(opcode_bin, fun3_bin, operands);   
        }
        else if(format == 's'){
            output = S_format(opcode_bin, fun3_bin, operands);
        }
        else if(format == 'u'){
            output = U_format(opcode_bin, operands);
        }
        printf("0x%08X",output);
     PC +=4;
    }}
}
return 0;
}



void Machine_Code(char * opcode)
{
   
    if(strcmp(opcode,"add")==0)
    {
        opcode_bin = 0x33;
        fun3_bin = 0x0;
        fun7_bin = 0x0;
        format ='r';
    }
    else if(strcmp(opcode,"sub")==0)
    {
        opcode_bin = 0x33;
        fun3_bin = 0x0;
        fun7_bin = 0x20;
        format ='r';
    }
    else if(strcmp(opcode,"and")==0)
    {
        opcode_bin = 0x33;
        fun3_bin = 0x7;
        fun7_bin = 0x0;
        format ='r';
    }
    else if(strcmp(opcode,"or")==0)
    {
        opcode_bin = 0x33;
        fun3_bin = 0x6;
        fun7_bin = 0x0;
        format ='r';
    }
    else if(strcmp(opcode,"sll")==0)
    {
        opcode_bin = 0x33;
        fun3_bin = 0x1;
        fun7_bin = 0x0;
        format ='r';
    }
    else if(strcmp(opcode,"slt")==0)
    {
        opcode_bin = 0x33;
        fun3_bin = 0x2;
        fun7_bin = 0x0;
        format ='r';
    }
    else if(strcmp(opcode,"sra")==0)
    {
        opcode_bin = 0x33;
        fun3_bin = 0x5;
        fun7_bin = 0x20;
        format ='r';
    }
    else if(strcmp(opcode,"srl")==0)
    {
        opcode_bin = 0x33;
        fun3_bin = 0x5;
        fun7_bin = 0x0;
        format ='r';
    }
    else if(strcmp(opcode,"xor")==0)
    {
        opcode_bin = 0x33;
        fun3_bin = 0x4;
        fun7_bin = 0x0;
        format ='r';
    }
    else if(strcmp(opcode,"mul")==0)
    {
        opcode_bin = 0x33;
        fun3_bin = 0x0;
        fun7_bin = 0x1; 
        format ='r';   
    }
    else if(strcmp(opcode,"div")==0)
    {
        opcode_bin = 0x33;
        fun3_bin = 0x4;
        fun7_bin = 0x1; 
        format ='r';   
    }
    else if(strcmp(opcode,"rem")==0)
    {
        opcode_bin = 0x33;
        fun3_bin = 0x6;
        fun7_bin = 0x1;
        format ='r';    
    }
    else if(strcmp(opcode,"addi")==0)
    {
        opcode_bin =0x13 ;
        fun3_bin = 0x0;
        format = 'i';
    }
    else if(strcmp(opcode,"andi")==0)
    {
        opcode_bin =0x13 ;
        fun3_bin = 0x7;
        format = 'i';
    }
    else if(strcmp(opcode,"ori")==0)
    {
        opcode_bin =0x13 ;
        fun3_bin = 0x6;
        format = 'i';
    }
    else if(strcmp(opcode,"lb")==0)
    {
        opcode_bin =0x3 ;
        fun3_bin = 0x0;
        format = 'i';
    }           
        else if(strcmp(opcode,"ld")==0)
    {
        opcode_bin =0x3 ;
        fun3_bin = 0x3;
        format = 'i';
    }    
        else if(strcmp(opcode,"lh")==0)
    {
        opcode_bin =0x3 ;
        fun3_bin = 0x1;
        format = 'i';
    }        
        else if(strcmp(opcode,"lw")==0)
    {
        opcode_bin =0x3 ;
        fun3_bin = 0x2;
        format = 'i';
    }    
        else if(strcmp(opcode,"jalr")==0)
    {
        opcode_bin =0x67 ;
        fun3_bin = 0x0;
        format = 'i';
    }        
        else if(strcmp(opcode,"sd")==0)
    {
        opcode_bin =0x23 ;
        fun3_bin = 0x3;
        format = 's';
    }
        else if(strcmp(opcode,"sb")==0)
    {
        opcode_bin =0x23 ;
        fun3_bin = 0x0;
        format = 's';
    }             
        else if(strcmp(opcode,"sh")==0)
    {
        opcode_bin =0x23 ;
        fun3_bin = 0x1;
        format = 's';
    }           
        else if(strcmp(opcode,"sw")==0)
    {
        opcode_bin =0x23 ;
        fun3_bin = 0x2;
        format = 's';
    }     
           else if(strcmp(opcode,"lui")==0)
    {
        opcode_bin =0x37 ;
        fun3_bin = 0x0;
        format = 'u';
    }        
        else if(strcmp(opcode,"auipc")==0)
    {
        opcode_bin =0x17 ;
        fun3_bin = 0x0;
        format = 'u';
    }
        else if(strcmp(opcode,"jal")==0)
    {
        opcode_bin =0x6F ;
        fun3_bin = 0x0;
        format = 'j';
    }                
        else if(strcmp(opcode,"beq")==0)
    {
        opcode_bin =0x63 ;
        fun3_bin = 0x0;
        format = 'b';
    }
        else if(strcmp(opcode,"bne")==0)
    {
        opcode_bin =0x63 ;
        fun3_bin = 0x1;
        format = 'b';
    }        
        else if(strcmp(opcode,"blt")==0)
    {
        opcode_bin =0x63 ;
        fun3_bin = 0x4;
        format = 'b';
    }        
        else if(strcmp(opcode,"bge")==0)
    {
        opcode_bin =0x63 ;
        fun3_bin = 0x5;
        format = 'b';
    }                
}


int main() {
    
    // Open the assembly file
  /*  FILE *riscv_file = fopen("test.asm", "r");
    if (riscv_file == NULL) {
        printf("Error: Unable to open RISC-V file\n");
    }
    else
    printf("file opened\n");*/
   int a = parse_instructions("test.asm");
}