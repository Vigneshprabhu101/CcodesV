/*-----------------------------------------------------------------------------------------
Input from sensor will be in the form as shown below

 ___________________________________
|  |  |  |  |                  |    | 
|SL|FT|PN|DL|       DATA       |CHKS|
|__|__|__|__|__________________|____|

here,
SL= Stream length -> 0 to 10
FT= Frame type -> D or R
PN= Port Number -> 0 to 3
DL= Data length -> 1 to 3
DATA= DL*8
CHKS= Check sum -> Sum of all 1's in DATA 
part1:
Write a program to read string, parse FT, PN, DL, DATA and CHKS
part 2:
Write a program to Store recived data in array of structure of 5, 
if input exceeds then according to FIFO method arrange the array of structure

-----------------------------------------------------------------------------------------*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define maxS 3
unsigned int size=maxS;
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
    size=str[0]-'0';
    a->FT=str[1];
    a->PN=str[2]-'0';
    (*a).DL=str[3]-'0';// another way to acces structure pointer
    unsigned int decimal=0,chks=0;
    unsigned int index=0;
    for(int i=4;i<((a->DL)*8)+4;i++)
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
    return a->FT;
}
void FIFO(sensor *a)
{
    for(int i=0;i<maxS-1;i++)
    {
        a[i]=a[i+1];
    }
    
}
void display(sensor *a)
{
    printf("\n\tFT:%c\tPN:%d\tDL:%d\tDATA:0x%x\tCHKS:%d\t\n",a->FT,a->PN,a->DL,a->DATA,a->CHKS);
}
int main()
{
    sensor *a=(sensor*)malloc(maxS*sizeof(sensor));

    char str[100];
    unsigned char fd;
    unsigned int stack=0;
    for(int i=0;i<size;i++)
    {
        if(stack=maxS)
        {
            FIFO(a);
            stack--;
        }
    printf("Enter the data: \t");
    fgets(str,sizeof(str),stdin);
    parser(str,&a[stack]);
    stack++;
    }
    for(int i=0;i<maxS;i++)
    {
        printf("\nindex:%d\n",i);
        display(&a[i]);
    }
    return 0;
}