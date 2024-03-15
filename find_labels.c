#include <stdio.h>
#include<stdlib.h>
#include <string.h>

int labels(const char *file_r)
{
    char line[100];
    int output = 0;
    // Open the assembly file
    FILE* r_file = fopen(file_r, "r");
    if (r_file == NULL) {
        printf("Error opening read file\n");
        return 1;
    }
    else 
    printf("Read file in find_lables opened\n");
    

    while (fgets(line, sizeof(line), r_file)) // Read each line from the file
     {
        printf("%s",line);
        char *token = strtok(line, " \t\n"); // Tokenize the line
         //   printf("%s",token);
        if (token != NULL)
         {
          //  printf("%s\t--\n",token);
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
        break;
        }
    }
}