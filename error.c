#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 100

// Function to check for basic errors in RISC-V assembly code
void checkAssemblyErrors(FILE *assemblyFile) {
    char line[MAX_LINE_LENGTH];
    int lineNumber = 0;

    // Supported RISC-V opcodes
    const char *validOpcodes[] = {"add", "sub", "and", "or", "sll", "slt", "sra", "srl", "xor", "mul", "div", "rem", "lb",
     "lh", "lw", "ld", "sb", "sh", "sw", "sd", "beq", "bne","blt", "bge", "jal", "jalr", "lui", "auipc", "addi", "andi",
      "ori"};

    while (fgets(line, MAX_LINE_LENGTH, assemblyFile)) // Read each line from the file
     {
        lineNumber++;
        char *token = strtok(line, " \t\n"); // Tokenize the line
            //printf("%s \n",token);
        if (token != NULL)
        {
            if (strcmp(token, ".text") == 0)
                break; 
        }
        // Skip till the .text section header
    }

    while (fgets(line, MAX_LINE_LENGTH, assemblyFile) != NULL) {
        printf("%s \n", line);
        lineNumber++;
        //printf("%d \n", lineNumber);
        // Check for line length
        if (strlen(line) >= MAX_LINE_LENGTH - 1 && line[MAX_LINE_LENGTH - 2] != '\n') {
            fprintf(stderr, "Error: Line %d is too long\n", lineNumber);
            exit(EXIT_FAILURE);
        }

        // Tokenize line to extract opcode and operands
        char *token = strtok(line, " ,\t\n");
        if (token == NULL || strchr(token, '#') || strchr(token, ':') != NULL) // Ignore empty lines or comments
            continue;

        // Check if opcode is valid
        int validOpcode = 0;
        for (int i = 0; i < sizeof(validOpcodes)/ sizeof(validOpcodes[0]); i++) {
            if (strcmp(token, validOpcodes[i]) == 0) {
                validOpcode = 1;
                break;
            }
        }
        if (!validOpcode) {
            fprintf(stderr, "Error: Invalid opcode in line %d\n", lineNumber);
            exit(EXIT_FAILURE);
        }

        // Check for correct number of operands for supported instructions
        if (strcmp(token, "add") == 0 || strcmp(token, "sub") == 0 || strcmp(token, "and") == 0 ||
            strcmp(token, "or") == 0 || strcmp(token, "sll") == 0 || strcmp(token, "slt") == 0 ||
            strcmp(token, "sra") == 0 || strcmp(token, "srl") == 0 || strcmp(token, "xor") == 0 || 
            strcmp(token, "mul") == 0 || strcmp(token, "div") == 0 || strcmp(token, "rem") == 0) {
            for(int i = 0; i<3; i++){
                token = strtok(NULL, " ,\t\n");
                if (token == NULL) {
                    fprintf(stderr, "Error: Missing operand in line %d\n", lineNumber);
                    exit(EXIT_FAILURE);
                }
            }
        }
        else if (strcmp(token, "addi") == 0 || strcmp(token, "andi") == 0 || strcmp(token, "ori") == 0 || strcmp(token, "jalr") == 0) {
            token = strtok(NULL, " ,\t\n");
            if (token == NULL) {
                fprintf(stderr, "Error: Missing operand in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            }
            token = strtok(NULL, " ,\t\n");
            if (token == NULL) {
                fprintf(stderr, "Error: Missing operand in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            }
            token = strtok(NULL, " ,\t\n");
            if (token == NULL) {
                fprintf(stderr, "Error: Missing operand in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            } 
        }
        else if (strcmp(token, "lb") == 0 || strcmp(token, "lh") == 0 || strcmp(token, "lw") == 0 || strcmp(token, "ld") == 0  
            || strcmp(token, "sb") == 0  || strcmp(token, "sh") == 0  || strcmp(token, "sw") == 0  || strcmp(token, "sd") == 0) {
            token = strtok(NULL, " ,\t\n()");
            if (token == NULL) {
                fprintf(stderr, "Error: Missing operand in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            }
            token = strtok(NULL, " ,\t\n()");
            if (token == NULL) {
                fprintf(stderr, "Error: Missing operand in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            }
            token = strtok(NULL, " ,\t\n()");
            if (token == NULL) {
                fprintf(stderr, "Error: Missing operand in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            }
        }    
        else if (strcmp(token, "beq") == 0 || strcmp(token, "bne") == 0 || strcmp(token, "blt") == 0 || strcmp(token, "bge") == 0) {
            token = strtok(NULL, " ,\t\n");
            if (token == NULL) {
                fprintf(stderr, "Error: Missing operand in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            }
            token = strtok(NULL, " ,\t\n");
            if (token == NULL) {
                fprintf(stderr, "Error: Missing operand in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            }
            token = strtok(NULL, " ,\t\n");
            if (token == NULL) {
                fprintf(stderr, "Error: Missing operand in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            }
        } 
        else if (strcmp(token, "jal") == 0 || strcmp(token, "lui") == 0 || strcmp(token, "auipc") == 0) {
            token = strtok(NULL, " ,\t\n");
            if (token == NULL) {
                fprintf(stderr, "Error: Missing operand in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            }
            token = strtok(NULL, " ,\t\n");
            if (token == NULL) {
                fprintf(stderr, "Error: Missing operand in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            }
        }
        else {
            fprintf(stderr, "Error: Unsupported instruction in line %d\n", lineNumber);
            exit(EXIT_FAILURE);
        }
    }

    printf("No errors found in the assembly code.\n");
}

int main() {
    FILE *assemblyFile = fopen("test.asm", "r");
    if (assemblyFile == NULL) {
        fprintf(stderr, "Error: Could not open the assembly file.\n");
        return EXIT_FAILURE;
    }

    checkAssemblyErrors(assemblyFile);

    fclose(assemblyFile);
    return EXIT_SUCCESS;
}

