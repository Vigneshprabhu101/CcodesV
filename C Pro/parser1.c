/*-----------------------------------------------------------------------------------------
Input from sensor will be in the form as shown below

 _________________________________
|  |  |  |                  |    | 
|FT|PN|DL|       DATA       |CHKS|
|__|__|__|__________________|____|

here,
FT= Frame type -> D or R
PN= Port Number -> 0 to 3
DL= Data length -> 1 to 3
DATA= DL*8
CHKS= Check sum -> SUm of all 1's in DATA 

Write a program to read string, parse FT, PN, DL, DATA and CHKS and do following,
if FT is D then display PN, DATA( hexa decimal value), and CHKS
if FT is R then display only PN

-----------------------------------------------------------------------------------------*/
#include<stdio.h>
#include<string.h>
typedef struct 
{
    char FT;
    unsigned int PN;
    unsigned int DL;
    unsigned int DATA;
    unsigned int CHKS;
}sensor;
unsigned char parser(char *str, sensor *a)
{
    a->PN=str[1]-'0';
    (*a).DL=str[2]-'0';// another way to acces structure pointer
    unsigned int decimal=0,chks=0;
    unsigned int index=0;
    for(int i=3;i<((a->DL)*8)+3;i++)
    {
        decimal=(decimal<<1)|(str[i]-'0');
        index=i;
    }
    a->DATA=decimal;
    index++;
    // printf("\n\ti=%d\n\tlength:%ld\n\t",index,strlen(str));
    for(int i=index;i<strlen(str)-1;i++)
    {
        // printf("\n\t%d\n\t",i);
        chks=chks*10+(str[i]-48);// '0' is 48
    }
    a->CHKS=chks;
    return str[0];
}
int main()
{
    sensor a;
    char str[100];
    unsigned char fd;
    printf("Enter the data: \t");
    fgets(str,sizeof(str),stdin);
    fd=parser(str,&a);
    if(fd=='D')
    {
        printf("\n\tPort number is : %u\n\tData length is :%u\n\tData :0x%x \n\tCheck sum : %d\n",a.PN,a.DL,a.DATA,a.CHKS);
    }
    if(fd=='R')
    {
        printf("\n\tPort number is : %u\n",a.PN);
    }
    return 0;
}