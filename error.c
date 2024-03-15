#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 100

// Function to check for basic errors in RISC-V assembly code
void checkAssemblyErrors(FILE *assemblyFile) {
    char line[MAX_LINE_LENGTH];
    int lineNumber = 0;
    int *reg_num = malloc(sizeof(int));

    // Supported RISC-V opcodes
    const char *validOpcodes[] = {"add", "sub", "and", "or", "sll", "slt", "sra", "srl", "xor", "mul", "div", "rem", "lb",
     "lh", "lw", "ld", "sb", "sh", "sw", "sd", "beq", "bne","blt", "bge", "jal", "jalr", "lui", "auipc", "addi", "andi",
      "ori"};

    while (fgets(line, MAX_LINE_LENGTH, assemblyFile)) // Read each line from the file
     {
        lineNumber++;
        char *token = strtok(line, " \t\n"); // Tokenize the line
        if (token != NULL)
        {
            if (strstr(token, "text") != 0)
                break; 
        }
        // Skip till the .text section header
    }

    while (fgets(line, MAX_LINE_LENGTH, assemblyFile) != NULL) {
        printf("%s \n", line);
        lineNumber++;
        // Check for line length
        if (strlen(line) >= MAX_LINE_LENGTH - 1 && line[MAX_LINE_LENGTH - 2] != '\n') {
            fprintf(stderr, "Error: Line %d is too long\n", lineNumber);
            exit(EXIT_FAILURE);
        }

        // Tokenize line to extract opcode and operands
        char *token = strtok(line, " ,\t\n");
        printf("%s\n", token);
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
            for(int j = 0; j<3; j++){
                token = strtok(NULL, " ,\t\n");
                printf("%s\n", token);
                sscanf(token, "%*[^0-9]%d", reg_num);
                printf("%d\n", *reg_num);
                if (token == NULL) {
                    fprintf(stderr, "Error: Missing operand in line %d\n", lineNumber);
                    exit(EXIT_FAILURE);
                }
                else if(strchr(token, 'x') == NULL || !isdigit(token[1])){
                    fprintf(stderr, "Error: Wrong register name in line %d\n", lineNumber);
                    exit(EXIT_FAILURE);
                }
                else if(*reg_num<0 || *reg_num>31){
                    fprintf(stderr, "Error: Incorrect register number in line %d\n", lineNumber);
                    exit(EXIT_FAILURE);
                }
            }
        }
        else if (strcmp(token, "addi") == 0 || strcmp(token, "andi") == 0 || strcmp(token, "ori") == 0 || strcmp(token, "jalr") == 0) {
            token = strtok(NULL, " ,\t\n");         //operand 1
            printf("%s\n", token);
            sscanf(token, "%*[^0-9]%d", reg_num);
            printf("%d\n", *reg_num);
            if (token == NULL) {
                fprintf(stderr, "Error: Missing operand in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            }
            else if(strchr(token, 'x') == NULL || !isdigit(token[1])){
                fprintf(stderr, "Error: Wrong register name in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            }
            else if(*reg_num<0 || *reg_num>31){
                fprintf(stderr, "Error: Incorrect register number in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            }
            token = strtok(NULL, " ,\t\n");         //operand 2
            printf("%s\n", token);
            sscanf(token, "%*[^0-9]%d", reg_num);
            printf("%d\n", *reg_num);
            if (token == NULL) {
                fprintf(stderr, "Error: Missing operand in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            }
            else if(strchr(token, 'x') == NULL || !isdigit(token[1])){
                fprintf(stderr, "Error: Wrong register name in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            }
            else if(*reg_num<0 || *reg_num>31){
                fprintf(stderr, "Error: Incorrect register number in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            }
            token = strtok(NULL, " ,\t\n");         //operand 3
            printf("%s\n", token);
            printf("%d\n", atoi(token));
            if (token == NULL) {
                fprintf(stderr, "Error: Missing operand in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            } 
            else if(isalpha(token[0])){
                fprintf(stderr, "Error: Operand should be an immediate in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            }
            else if(atoi(token) < -2048 || atoi(token) > 2047){
                fprintf(stderr, "Error: Immediate is out of range in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            }
        }
        else if (strcmp(token, "lb") == 0 || strcmp(token, "lh") == 0 || strcmp(token, "lw") == 0 || strcmp(token, "ld") == 0  
            || strcmp(token, "sb") == 0  || strcmp(token, "sh") == 0  || strcmp(token, "sw") == 0  || strcmp(token, "sd") == 0) {
            token = strtok(NULL, " ,\t\n()");           //operand 1
            printf("%s\n", token);
            sscanf(token, "%*[^0-9]%d", reg_num);
            printf("%d\n", *reg_num);
            if (token == NULL) {
                fprintf(stderr, "Error: Missing operand in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            }
            else if(strchr(token, 'x') == NULL || !isdigit(token[1])){
                fprintf(stderr, "Error: Wrong register name in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            }
            else if(*reg_num<0 || *reg_num>31){
                fprintf(stderr, "Error: Incorrect register number in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            }
            token = strtok(NULL, " ,\t\n()");           //operand 2
            printf("%s\n", token);
            printf("%d\n", atoi(token));
            if (token == NULL) {
                fprintf(stderr, "Error: Missing operand in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            }
            else if(isalpha(token[0])){
                fprintf(stderr, "Error: Operand should be an immediate in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            }
            else if(atoi(token) < -2048 || atoi(token) > 2047){
                fprintf(stderr, "Error: Immediate is out of range in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            }
            token = strtok(NULL, " ,\t\n()");           //operand 3
            printf("%s\n", token);
            sscanf(token, "%*[^0-9]%d", reg_num);
            printf("%d\n", *reg_num);
            if (token == NULL) {
                fprintf(stderr, "Error: Missing operand in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            }
            else if(strchr(token, 'x') == NULL || !isdigit(token[1])){
                fprintf(stderr, "Error: Wrong register name in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            }
            else if(*reg_num<0 || *reg_num>31){
                fprintf(stderr, "Error: Incorrect register number in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            }
        }    
        else if (strcmp(token, "beq") == 0 || strcmp(token, "bne") == 0 || strcmp(token, "blt") == 0 || strcmp(token, "bge") == 0) {
            token = strtok(NULL, " ,\t\n");         //operand 1
            printf("%s\n", token);
            sscanf(token, "%*[^0-9]%d", reg_num);
            printf("%d\n", *reg_num);
            if (token == NULL) {
                fprintf(stderr, "Error: Missing operand in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            }
            else if(strchr(token, 'x') == NULL || !isdigit(token[1])){
                fprintf(stderr, "Error: Wrong register name in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            }
            else if(*reg_num<0 || *reg_num>31){
                fprintf(stderr, "Error: Incorrect register number in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            }
            token = strtok(NULL, " ,\t\n");         //operand 2
            printf("%s\n", token);
            sscanf(token, "%*[^0-9]%d", reg_num);
            printf("%d\n", *reg_num);
            if (token == NULL) {
                fprintf(stderr, "Error: Missing operand in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            }
            else if(strchr(token, 'x') == NULL || !isdigit(token[1])){
                fprintf(stderr, "Error: Wrong register name in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            }
            else if(*reg_num<0 || *reg_num>31){
                fprintf(stderr, "Error: Incorrect register number in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            }
            token = strtok(NULL, " ,\t\n");         //operand 3
            printf("%s\n", token);
            if (token == NULL) {
                fprintf(stderr, "Error: Missing operand in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            }
        } 
        else if (strcmp(token, "jal") == 0) {
            token = strtok(NULL, " ,\t\n");             //operand 1
            printf("%s\n", token);
            sscanf(token, "%*[^0-9]%d", reg_num);
            printf("%d\n", *reg_num);
            if (token == NULL) {
                fprintf(stderr, "Error: Missing operand in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            }
            else if(strchr(token, 'x') == NULL || !isdigit(token[1])){
                fprintf(stderr, "Error: Wrong register name in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            }
            else if(*reg_num<0 || *reg_num>31){
                fprintf(stderr, "Error: Incorrect register number in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            }
            token = strtok(NULL, " ,\t\n");             //operand 2
            printf("%s\n", token);
            if (token == NULL) {
                fprintf(stderr, "Error: Missing operand in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            }
        }
         else if (strcmp(token, "lui") == 0 || strcmp(token, "auipc") == 0) {
            token = strtok(NULL, " ,\t\n");             //operand 1
            printf("%s\n", token);
            sscanf(token, "%*[^0-9]%d", reg_num);
            printf("%d\n", *reg_num);
            if (token == NULL) {
                fprintf(stderr, "Error: Missing operand in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            }
            else if(strchr(token, 'x') == NULL || !isdigit(token[1])){
                fprintf(stderr, "Error: Wrong register name in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            }
            else if(*reg_num<0 || *reg_num>31){
                fprintf(stderr, "Error: Incorrect register number in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            }
            token = strtok(NULL, " ,\t\n");             //operand 2
            printf("%s\n", token);
            printf("%d\n", atoi(token));
            if (token == NULL) {
                fprintf(stderr, "Error: Missing operand in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            }
            else if(isalpha(token[0])){
                fprintf(stderr, "Error: Operand should be an immediate in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            }
            else if(atoi(token) < 0 || atoi(token) > 1048575){
                fprintf(stderr, "Error: Immediate is out of range in line %d\n", lineNumber);
                exit(EXIT_FAILURE);
            }
            
        }
        else {
            fprintf(stderr, "Error: Unsupported instruction in line %d\n", lineNumber);
            exit(EXIT_FAILURE);
        }
    }

    printf("No errors found in the assembly code.\n");
    free(reg_num);
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

