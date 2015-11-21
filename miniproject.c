#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
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
        "JMP","03"
    }
};
char label[20],opcode[20],operand[20],prog_name[20];
int locctr,start_address,length,start_address,sym_count=0;
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
       fprintf(f2,"\n%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
       fscanf(f1,"%s%s%s",label,opcode,operand);
    }
    while(strcmp(opcode,"END")!=0)
    {

        if(strcmp(label,"*")!=0)
        {
            fprintf(f3,"\n%s\t%d\n",label,locctr);
            sym_count++;
        }
            printf("\n%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
            fprintf(f2,"\n%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
        if(strcmp(opcode,"*")!=0)
        {
            chk_opcode();
        }

        fscanf(f1,"%s%s%s",label,opcode,operand);
    }
    printf("\n%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
    fprintf(f2,"\n%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
    fclose(f1);
    fclose(f2);
    fclose(f3);
    length=locctr-start_address;

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
void pass2()
{
    FILE *f2,*f3,*f4;
    int l,i,j,len,flag=0,ch=0;
    char lo[20],value[20],x[20],ad_val[20],op_tab[20],lab[20],loc[20];
    f2=fopen("inter.txt","r");
    f3=fopen("sym_tab.txt","r");
    f4=fopen("output.txt","w");
    fscanf(f2,"%s%s%s%s",lo,label,opcode,operand);
    printf("\nH^%s^%d^%d\n",prog_name,start_address,length);
    while(strcmp(opcode,"END")!=0)
    {
        ch=0;
        j=0;
        lab[0]='\0';
        loc[0]='\0';
        ad_val[0]='\0';
        fscanf(f2,"%s%s%s%s",lo,label,opcode,operand);
        if(strcmp(opcode,"BYTE")==0)
        {
            l=strlen(operand);
            l=l-3;
            if(operand[0]=="C")
            {
                for(i=0;i<(l+2);i++)
                {
                    itoa(operand[i],value,16);
                    printf("\n%s\t%s\t%s\t%s\t%s\n",lo,label,opcode,operand,value);
                }
            }
            else
            {
                for(i=0;i<(l+2);i++)
                {
                    value[j]=operand[i];
                    j++;
                    printf("\n%s\t%s\t%s\t%s\t%s\n",lo,label,opcode,operand,value);
                }
            }
        }
        else if(strcmp(opcode,"WORD")==0)
        {
            l=strlen(operand);
            atoi(itoa(operand,x,16));
            len=strlen(x);
            for(i=0;i<(6-len);i++)
            {
                value[j]="0";
                j++;
            }
            value[j]=x;
            printf("\n%s\t%s\t%s\t%s\t%s\n",lo,label,opcode,operand,value);
        }
        else if(strcmp(opcode,"RESB")==0||strcmp(opcode,"RESW")==0)
        {

            printf("\n%s\t%s\t%s\t%s\n",lo,label,opcode,operand);
        }
        else
        {
            for(i=0;i<3;i++)
            {
                if(strcmp(opcode,my_optab[i].code)==0)
                {
                    j=i;


                    flag=1;
                    break;

                }
            }

                if(strcmp(operand,"*")!=0)
                {
                    rewind(f3);



                fscanf(f3,"%s%s",lab,loc);

                while(strcmp(operand,lab)!=0)

                fscanf(f3,"%s%s",lab,loc);



                   printf("\n%s\t%s\t%s\t%s\t%s%s\n",lo,label,opcode,operand,my_optab[j].object_code,loc);
                }


                if(strcmp(operand,"*")==0)
                {
                    printf("\n%s\t%s\t%s\t%s\t0000%s\n",lo,label,opcode,operand,my_optab[j].object_code);
                }

        }

    }
    fclose(f2);
    fclose(f3);
    fclose(f4);
}




void main()
{
    pass1();
    pass2();
    getch();
}
