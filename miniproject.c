#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
struct symtab
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
        "JMP","03"
    }
};
char label[20],opcode[20],operand[20],prog_name[20];
int locctr,start_address;
void pass1()
{


    FILE *f1,*f2,*f3;
    f1=fopen("input.txt","r");
    f2=fopen("inter.txt","w");
    f3=fopen("sym_tab.txt","w");
    fscanf(f1,"%s%s%s",label,opcode,operand);
    if(strcmp(opcode,"START")==0)
    {
       start_address=atoi(operand);
       locctr=start_address;
       strcpy(prog_name,label);
       printf("\n%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
       fprintf(f2,"%d\t%s\t%s\t%s",locctr,label,opcode,operand);
       fscanf(f1,"%s%s%s",label,opcode,operand);
    }
    while(strcmp(opcode,"END")!=0)
    {

        if(strcmp(label,"*")!=0)
        {
            fprintf(f3,"\n%s\t%d\n",label,locctr);
        }
            printf("\n%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
        if(strcmp(opcode,"*")!=0)
        {
            chk_opcode();
        }

        fscanf(f1,"%s%s%s",label,opcode,operand);
    }
    printf("\n%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
    fclose(f1);
    fclose(f2);
    fclose(f3);

}
void chk_opcode()
{
    int i,j,flag=0,flag1=0,operand_length;
    for(i=0;i<3;i++)
    {
        if(strcmp(opcode,my_optab[i].code)==0)
        {

            flag=1;

        }
    }
    if(flag!=1)
    {
        if(strcmp(opcode,"WORD")==0)
        {
            locctr=locctr+3;
        }
        else if(strcmp(opcode,"RESW")==0)
        {
            locctr=locctr+3*atoi(operand);
        }
        else if(strcmp(opcode,"RESB")==0)
        {
            locctr=locctr+atoi(operand);
        }
        else if(strcmp(opcode,"BYTE")==0)
        {
                operand_length=strlen(operand);
                if(opcode[0]=='c')
                {
                    locctr=locctr+(operand_length-3);
                }
                if(opcode[0]=='x')
                {
                    for(i=2;i<operand_length;i++)
                    {
                        flag1++;
                    }


                    locctr=locctr+flag/2;
                }

        }
        else
        {
            printf("err");
        }

    }
    else
    {
        locctr=locctr+3;
    }

}

void main()
{
    pass1();
    getch();
}
