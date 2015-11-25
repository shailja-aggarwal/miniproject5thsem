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
int locctr,length,start_address,sym_count=0;
unsigned long convtodecnum(char hex[])
{
    char *hexs;
    int len = 0;
    const int b = 16;
    unsigned long dnum = 0;
    int i;
    for (hexs = hex; *hexs != '\0'; hexs++)
    {
        len++;
    }
    hexs= hex;
    for (i = 0; *hexs != '\0' && i < len; i++, hexs++)
    {
        if (*hexs >= 48 && *hexs <= 57)
        {
            dnum += (((int)(*hexs)) - 48) * pow(b, len - i - 1);
        }
        else if ((*hexs >= 65 && *hexs <= 70))
        {
            dnum += (((int)(*hexs)) - 55) * pow(b, len - i - 1);
        }
        else if (*hexs >= 97 && *hexs <= 102)
        {
            dnum += (((int)(*hexs)) - 87) * pow(b, len - i - 1);
        }
        else
        {
            printf(" Invalid Hexadecimal Number \n");
        }
    }
    return dnum;
}
void pass1()
{
    int c;
    char new_val[20];

    FILE *f1,*f2,*f3;
    f1=fopen("input.txt","r");
    f2=fopen("inter.txt","w");
    f3=fopen("sym_tab.txt","w");
    fscanf(f1,"%s%s%s",label,opcode,operand);

    if(strcmp(opcode,"START")==0)
    {
       start_address=convtodecnum(operand);
       locctr=start_address;
       strcpy(prog_name,label);
       printf("\n%x\t%s\t%s\t%s\n",locctr,label,opcode,operand);
       fprintf(f2,"%x\t%s\t%s\t%s\n",locctr,label,opcode,operand);
       fscanf(f1,"%s%s%s",label,opcode,operand);
    }
    while(strcmp(opcode,"END")!=0)
    {

        if(strcmp(label,"*")!=0)
        {
            fprintf(f3,"%s\t%x\n",label,locctr);
            sym_count++;
        }
            printf("%x\t%s\t%s\t%s\n",locctr,label,opcode,operand);
            fprintf(f2,"%x\t%s\t%s\t%s\n",locctr,label,opcode,operand);
        if(strcmp(opcode,"*")!=0)
        {
            chk_opcode();
        }

        fscanf(f1,"%s%s%s",label,opcode,operand);
    }
    printf("\n%x\t%s\t%s\t%s\n",locctr,label,opcode,operand);
    fprintf(f2,"%x\t%s\t%s\t%s\n",locctr,label,opcode,operand);
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
                if(operand[0]=='c')//operand ......not opcode
                {
                    locctr=locctr+(operand_length-3);
                }
                if(operand[0]=='x')//operand ........not opcode
                {
                    for(i=2;i<operand[i]!='\0';i++)//................i<operand_length-1.....as for string shubham length is 7.
                    {
                        flag1++;
                    }
                    locctr=locctr+(flag1/2);//.........................flag1 not flag
                }

        }
        else
        {
            printf("err\n");
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
    int l,i,j,len,flag=0,ch=0,total_length;
    char lo[20],value[20],x[20],ad_val[20],op_tab[20],lab[20],loc[20],addr[20],text_record[100];
    f2=fopen("inter.txt","r");
    f3=fopen("sym_tab.txt","r");
    f4=fopen("output.txt","w");
    fscanf(f2,"%s%s%s%s",lo,label,opcode,operand);
    printf("\nH^% 6s^%x^%06d\n",prog_name,start_address,length);
    fprintf(f4,"\nH^%s^00%x^%06d\n",prog_name,start_address,length);
    printf("*\t%s\t%s\t%s",lo,label,opcode,operand);
    fscanf(f2,"%s%s%s%s",lo,label,opcode,operand);
    while(strcmp(opcode,"END")!=0)
    {
        text_record[0]='\0';
        total_length=0;
         strcpy(addr,lo);
        while(total_length<30&&strcmp(opcode,"END")!=0)
        {

        ch=0;
        j=0;
        lab[0]=0;
        loc[0]=0;
        ad_val[0]=0;
        if(strcmp(opcode,"BYTE")==0)
        {
            l=strlen(operand);
            l=l-3;
            strcat(text_record,"^");
            if(operand[0]=='c')
            {
                printf("\n%s\t%s\t%s\t%s\t",lo,label,opcode,operand);
                for(i=2;i<(l+2);i++)
                {
                    itoa(operand[i],value,16);
                    printf("%s",value);
                    strcat(text_record,value);

                }
                printf("\n");
                total_length+=(strlen(value))/2;
            }
            else
            {
                for(i=2;i<(l+2);i++)
                {
                    value[j]=operand[i];
                    j++;

                }
                value[j]='\0';
                 printf("\n%s\t%s\t%s\t%s\t%s\n",lo,label,opcode,operand,value);

                strcat(text_record,value);
                total_length+=(strlen(value))/2;
            }
        }
        else if(strcmp(opcode,"WORD")==0)
        {
            l=strlen(operand);
            int xx;
            xx=atoi(operand);
            itoa(xx,x,16);
            len=strlen(x);
            j=0;
            for(i=0;i<(6-len);i++)
            {
                value[j]='0';
                j++;
            }
            strcat(value,x);
            printf("\n%s\t%s\t%s\t%s\t%s\n",lo,label,opcode,operand,value);
             strcat(text_record,"^");
            strcat(text_record,value);
            total_length+=(strlen(value))/2;
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



                fscanf(f3,"%s%s",lab,loc);


                while(ch<=sym_count)
                {
                    if(strcmp(operand,lab)==0)
                    {
                        strcpy(ad_val,loc);
                        break;
                    }
                    fscanf(f3,"%s%s",lab,loc);
                    ch++;

                }
                    rewind(f3);
                   printf("\n%s\t%s\t%s\t%s\t%s%s\n",lo,label,opcode,operand,my_optab[j].object_code,ad_val);
                    strcat(text_record,"^");
                    strcat(text_record,my_optab[j].object_code);
                    strcat(text_record,ad_val);
                    total_length+=3;
                }

                if(strcmp(operand,"*")==0)
                {
                    printf("\n%s\t%s\t%s\t%s\t%s0000\n",lo,label,opcode,operand,my_optab[j].object_code);
                    strcat(text_record,"^");
                    strcat(text_record,my_optab[j].object_code);
                    strcat(text_record,"0000");
                     total_length+=3;
                }


        }
        fscanf(f2,"%s%s%s%s",lo,label,opcode,operand);

    }
            fprintf(f4,"\nT^00%s^%x%s\n",addr,total_length,text_record);
    }
    fprintf(f4,"\nE^00%x\n",start_address);
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


