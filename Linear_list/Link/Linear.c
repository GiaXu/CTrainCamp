#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 10

typedef struct LNode *List;
struct LNode{

    int Data[MAXSIZE];
    int Last;
};

struct LNode L;
List PtrL;

List InitList()
{
    List PtrL;
    PtrL = (List)malloc(sizeof(struct LNode));
    PtrL->Last = -1;

    return PtrL;
}


int Find(int x,List PtrL)
{
    int i = 0;
    while (i <= PtrL->Last && PtrL->Data[i] != x)
    {
        ++i;
    }
    if(i > PtrL->Last)
    {
        return -1;
    }
    else
    {
        return i;
    }
}

void Insert(int x,int i,List PtrL)
{
    int j;
    if(PtrL->Last == MAXSIZE - 1)
    {
        printf("FULL");
        return;
    }
    if(i < 1 || i > PtrL->Last + 2)
    {
        printf("Illegal Location");
        return;
    }
    for(j = PtrL->Last;j <= i-1;--j)
    {
        PtrL->Data[j+1] = PtrL->Data[j];
    }
    PtrL->Data[i-1] = x;
    PtrL->Last++;

    return;
}

void Delete(int i,List PtrL)
{
    if(i < 1 || i > PtrL->Last + 2)
    {
        printf("Illegal location");
        return;
    }
    for(int j = i;i < PtrL->Last + 1;++j)
    {
        PtrL->Data[j] = PtrL->Data[j+1];
    }
    PtrL->Last--;
    
    return;
}




