#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int I_format(int opcode, int fun3, char *operand[]){
 char rd[10]; 
 char rs1[10];
 int rd_val;
 int rs1_val;
 int imm_val;

 //printf("%s %s %s\n",operand[0],operand[1],operand[2]);
strncpy(rd, operand[0]+1, strlen(operand[0])-1);
rd_val = atoi(rd);

if(opcode == 0x3){
    imm_val = atoi(operand[1]);
    strncpy(rs1, operand[2]+1, strlen(operand[2])-1);
    //printf("%s",rs1);
    rs1_val = atoi(rs1);
}
   else{
    strncpy(rs1, operand[1]+1, strlen(operand[1])-1);
  //   printf("%s",rs1);
    rs1_val = atoi(rs1);
    imm_val = atoi(operand[2]);
   } 
  // printf("%d %d\n\n",rd_val,rs1_val);
 unsigned int instruction = 0;
 instruction |= (imm_val & 0xfff) << 20;   //bits 31-20
 instruction |= (rs1_val & 0x1f) << 15;     //bits 19-15
 instruction |= (fun3 & 0x7) << 12;    //bits 14-12
 instruction |= (rd_val & 0x1f) << 7;    //bits 11-7
 instruction |= (opcode & 0x7f);    //bits 6-0

return instruction;
}

int R_format(int opcode, int fun3, int fun7, char* operands[])
{
    char* rs1 = operands[1];
    char* rs2 = operands[2];
    char* rd = operands[0];
    int rd_val=0;
    int rs1_val=0;
    int rs2_val=0;

     for (int i = 1; i < strlen(rd); i++){          //Finding numerical value of rd
        rd_val = rd_val * 10 + (rd[i] - '0');
     }

     for (int i = 1; i < strlen(rs1); i++){         //Finding numerical value of rs1
        rs1_val = rs1_val * 10 + (rs1[i] - '0');
     }

     for (int i = 1; i < strlen(rs2); i++){         //Finding numerical value of rs2
        rs2_val = rs2_val * 10 + (rs2[i] - '0');
     }
     unsigned int instruction = 0;
    instruction |= opcode & 0x7F;                   //Generating Machine Code
    instruction |= (rd_val & 0x1F) << 7;
    instruction |= (fun3 & 0x7) << 12;
    instruction |= (rs1_val & 0x1F) << 15;
    instruction |= (rs2_val & 0x1F) << 20;
    instruction |= (fun7 & 0x7F) << 25;
    return instruction;
}
int S_format(int opcode, int fun3, char* operands[])
{
    char* rs1 = operands[0];
    char* rs2 = operands[2];
    char* imm = operands[1];
    int imm_val=0;
    int rs1_val=0;
    int rs2_val=0;

     for (int i = 0; i < strlen(imm); i++){        //Finding numerical value of rd
        imm_val = imm_val * 10 + (imm[i] - '0');
     }

     for (int i = 1; i < strlen(rs1); i++){         //Finding numerical value of rs1
        rs1_val = rs1_val * 10 + (rs1[i] - '0');
     }

     for (int i = 1; i < strlen(rs2); i++){         //Finding numerical value of rs2
        rs2_val = rs2_val * 10 + (rs2[i] - '0');
     }
     unsigned int instruction = 0;
    instruction |= opcode & 0x7F;                   //Generating Machine Code
    instruction |= (imm_val & 0x1F) << 7;
    instruction |= (fun3 & 0x7) << 12;
    instruction |= (rs2_val & 0x1F) << 15;
    instruction |= (rs1_val & 0x1F) << 20;
    instruction |= ((imm_val & 0xFE0)>>5) << 25;
    return instruction;
}

int U_format(int opcode,char* operands[])
{
    char* imm = operands[1];
    char* rd = operands[0];
    int rd_val=0;
    int imm_val=0;
    

     for (int i = 1; i < strlen(rd); i++){          //Finding numerical value of rd
        rd_val = rd_val * 10 + (rd[i] - '0');
     }

     for (int i = 0; i < strlen(imm); i++){         //Finding numerical value of rs1
        imm_val = imm_val * 10 + (imm[i] - '0');
     }

  
     unsigned int instruction = 0;
     instruction |= opcode & 0x7F;                   //Generating Machine Code
     instruction |= (rd_val & 0x1F) << 7;
     instruction |= (imm_val & 0xFFFFF) << 12;
     // printf("%d\n",imm_val);
      return instruction;
}
int J_format(int opcode, char* operands[],char (* label_name)[15],int label_pos[], int count,int PC)
{
    char* label = operands[1];
    char* rd = operands[0];
    int rd_val=0;
    int imm_val=0;
   // printf("ct=%d\n",count);
   /* for(int i=0;i<count;i++)
   {
   printf("pos= %d name= %s\n",label_pos[i],label_name[i]);
   }
    */

    for (int i = 1; i < strlen(rd); i++){          //Finding numerical value of rd
      rd_val = rd_val * 10 + (rd[i] - '0');
     }
   int i=0;
   for(i=0;i<count;i++)
   {
     if(strcmp(label,label_name[i])==0)
     {
        // printf("label_n= %s  i= %d\n",label_name[i],i);
         break;
     }
   }
   
  int pos = label_pos[i]*4;
   imm_val =  pos- PC;
//printf("pos=%d  imm=%d\n\n",pos,imm_val);

   int imm_20 = (imm_val >> 20) & 0x1;
   int imm_19_12 = (imm_val >> 12) & 0xFF;
   int imm_11 = (imm_val >> 11) & 0x1;
   int imm_10_1 = (imm_val >> 1) & 0x3FF;

    // Encode the UJ instruction
   int instruction = 0;
    instruction |= (imm_20 << 31);
    instruction |= (imm_19_12 << 12);
    instruction |= (imm_11 << 20);
    instruction |= (imm_10_1 << 21);

    // Set the opcode (JAL)
    instruction |= (0b1101111 );
   instruction |=  (rd_val & 0x1F) << 7;
    return instruction;


    

}
/*int main()
{
    char* st[3] = {"x1","62"};
    unsigned int ins = U_format(0x33,st);
    printf("0x%08X",ins);

    char *field[] = {"x1", "10", "x5"};
    unsigned int test = I_format(0x3, 0x0, field );
    printf("0x%08X",test ); 
 }
*/

