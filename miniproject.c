#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
//#include<fstream>

struct symtab
{
    int address;
    char symbol;
}my_symtab[20];
struct optab
{
    char code[20];
    char object_code[20];
}my_optab[3]={
    {
        "LDA","00"
    },
    {
        "STA","01"
    },
    {
        "JMP","02"
    }
};
char opcode[20],label[20],operand[20],prog_name[20];
int locctr,start_address,symbol_count;
void pass1()
{
    FILE *f1,*f2;
    f1=fopen("input.txt","r");
    f2=fopen("inter.txt","w");
    fscanf(f1,"%s%s%s",label,opcode,operand);

    if(strcmp(opcode,"START")==0)
    {
        start_address=atoi(operand);
        locctr=start_address;
        strcpy(prog_name,label);
        printf("\n%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
        fprintf(f2,"\n%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
        fscanf(f1,"%s%s%s",label,opcode,operand);
    }
    while(strcmp(opcode,"END")!=0)
    {
        if(strcmp(label,"*"))
        {
            chk_label();
        }
        if(strcmp(opcode,"*"))
        {
            chk_opcode();
        }
        if(strcmp(label,"*")!=0&&strcmp(opcode,"*")!=0&&strcmp(operand,"*")!=0)
        {
            printf("\n%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
            //fprintf(f2,"%d%s%s%s\n",locctr,label,opcode,operand);
        }
        if(strcmp(label,"*")==0&&strcmp(opcode,"*")!=0&&strcmp(operand,"*")!=0)
        {
            printf("\n%d\t%s\t%s",locctr,opcode,operand);
            //fprintf(f2,"%d%s%s",locctr,opcode,operand);
        }
        if(strcmp(label,"*")!=0&&strcmp(opcode,"*")!=0&&strcmp(operand,"*")==0)
        {
            printf("\n%d\t%s\t%s",locctr,label,opcode);
            //fprintf(f2,"%d%s%s\n",locctr,label,opcode);
        }
        if(strcmp(label,"*")==0&&strcmp(opcode,"*")!=0&&strcmp(operand,"*")==0)
        {
            printf("\n%d\t%s\n",locctr,opcode);
            //fprintf(f2,"%d%s\n",locctr,opcode);
        }
        fprintf(f2,"%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
        fscanf(f1,"%s%s%s",label,opcode,operand);
    }
    printf("\n%d\t%s\n",locctr,opcode);
    fprintf(f2,"%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
    fclose(f1);
    fclose(f2);
}
void chk_label()
{
    int i,flag=0;
    for(i=0;i<symbol_count;i++)
    {
        if(strcmp(label,my_symtab[i].symbol)==0)
        {
            printf("error");
            flag=1;
            break;
        }
        if(flag==0)
        {
            strcpy(my_symtab[symbol_count].symbol,label);
            symbol_count++;
            my_symtab[symbol_count].address=locctr;
        }
    }
}
void chk_opcode()
{
    int i,flag=0,operand_length;
    for(i=0;i<3;i++)
    {
        if(strcmp(opcode,my_optab[i].code)==0)
        {
            locctr=locctr+3;
            flag=1;
            break;
        }
        if(flag==0)
        {
            if(strcmp(opcode,"WORD")==0)
            {
                locctr=locctr+3;
            }
            if(strcmp(opcode,"RESW")==0)
            {
                locctr=locctr+3*atoi(operand);
            }
            if(strcmp(opcode,"RESB")==0)
            {
                locctr=locctr+atoi(operand);
            }
              if(strcmp(opcode,"BYTE")==0)
            {
                opcode_length=strlen(opcode);
                if(opcode[0]=='c')
                {
                    locctr=locctr+(operand_length-3);
                }
                if(opcode[0]=='x')
                {
                    operand_length=(operand_length-2)/2
                    locctr=locctr+operand_length;
                }

            }
        }
    }
}
void main()
{
    pass1();
    getch();
}
