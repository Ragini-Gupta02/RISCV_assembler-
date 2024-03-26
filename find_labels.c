#include <stdio.h>
#include<stdlib.h>
#include <string.h>

    

int labels(const char *file_r, char (*label_names)[15],int* label_pos)
{
    char line[100];
    int output = 0;
    // Open the assembly file
    FILE* r_file = fopen(file_r, "r");
    if (r_file == NULL) {
        printf("Error opening read file\n");
        return 0;
    }
    else 
    printf("Read file in find_lables opened\n");
    
    int PC=0;
   // char* label_names[20];
    int count=0;

    while (fgets(line, sizeof(line), r_file)) // Read each line from the file
     {
        printf("%s",line);
        char *token = strtok(line, " \t\n"); // Tokenize the line
         //   printf("%s",token);
        if (token != NULL)
         {
            printf("%s\t--\n",token);
            if (strstr(token, "text") != NULL) 
                break; 
            
         }
        
     }               // Skip till the .text section header
      while (fgets(line, sizeof(line), r_file)) // Read each line from the file
     {
        printf("%s",line);
        char *token = strtok(line, " ,()\t\n"); // Tokenize the line
        if(token!=NULL)
        {
            if(strstr(token,":")!=NULL)
            {
                token = strtok(token, ":");
                //printf("%s--",token);
                strncpy(label_names[count],token,15);
                label_pos[count] = PC;
                count++;
            }
            else
            PC++;
        }
    }
    fclose(r_file);
    return count;
}
/*
int main() {
    
    // Open the assembly file
    FILE *riscv_file = fopen("test.asm", "r");
    if (riscv_file == NULL) {
        printf("Error: Unable to open RISC-V file\n");
    }
    else
    printf("file opened\n");
    char name[15][15];
    int pos[10];
    int ct;
    //printf("here-%s\n",name[0]);
   ct = labels("test.asm",name,pos);

   for(int i=0;i<ct;i++)
   {
   printf("pos= %d name= %s\n",pos[i],name[i]);
   }
   printf("ct= %d",ct);
  
}*/