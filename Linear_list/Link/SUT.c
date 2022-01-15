#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    FALSE = 0,
    TRUE
} BOOL;

typedef  struct  LNode 
{
    int data;  
    struct LNode *next;  

}LNode, *LinkList;

const char *option = 
    "\n=======================\n\
    Please choose a command :\n\
    1. Add a record;\n\
    2. List records;\n\
    3. Remove a record\n\
    4. Insert a record\n\
    0. Quit\n";


LNode *Creat(int data) //创建一个结点
{
    LNode *p = (LinkList)malloc(sizeof(LNode));
    p->next = NULL;
    p->data = data;

    return p;
}

int Length(LNode *pHead)
{
    if(NULL == pHead)
    {
        return -1;
    }
    int i = 1;
    while(NULL != pHead->next)
    {
        pHead = pHead->next;
        ++i;
    }
    return i;
}


BOOL Add(LNode *p1,LNode *p2) //在末尾增加一个结点，p1后增加p2
{
    if(p1 == p2 || NULL == p1 || NULL == p2)
    {
        return FALSE;
    }
    LNode *p = p1;

    while (NULL != p->next)
    {
        p = p->next;
    }
    p->next = p2;

    return TRUE;
    
}

BOOL Insert(LNode *pHead,LNode *p0,int num)
{
    if(pHead == p0 || NULL == pHead || NULL == p0)
    {
        return FALSE;
    }
    if(num > Length(pHead))
    {
        return FALSE;
    }
    if(0 == num)
    {
        p0->next = pHead;
        return TRUE;
    }

    LNode *p1 = pHead;
    int i = 1;
    while(i < (num-1))
    {
        p1 = p1->next;
        ++i;
    }
    p0->next = p1->next;
    p1->next = p0;

    return TRUE;
}


/*
LNode *Remove(LNode *pHead,LNode *p0) //删除一个结点
{
    if(NULL == pHead || NULL == p0) 
    {
        return pHead;
    }
    if(pHead == p0)
    {
        pHead = pHead->next;
        free(p0);
        return pHead;
    }
    LNode *p1 = pHead;

    while (p1->next != p0)
    {
        p1 = p1->next;

        if(NULL == p1) //p0不在链表中
        {
            return pHead;
        }
    }
    p1->next = p0->next;
    free(p0);

    return pHead;
}

BOOL destroy(LNode *pHead)
{
    if(NULL == pHead)
    {
        printf("Unextra!");
        return FALSE;
    }
    
    do
    {
        pHead = Remove(pHead,pHead);
    }while (NULL != pHead);

    return TRUE;
}
*/
void printANode(LNode *pHead)
{
    if(NULL == pHead)
    {
        printf("Wrong!");
        return;
    }

    printf("%d,",pHead->data);
}

void printALink(LNode *pHead)
{
    if(NULL == pHead)
    {
        return;
    }
    while(NULL != pHead->next)
    {
        printANode(pHead);
        pHead = pHead->next;
    }
    
}

int main()
{
    int a[6] = {21,18,30,75,42,56};
    int b[6] = {0};
    int i = 0;
    int j = 0;

    for(int i = 5;i >= 0;--i) //实现逆序
    {
        b[j] = a[i];
        printf("%d,",b[j]);
        ++j;
    }
    
    LNode *pHead = Creat(b[0]);
    LNode *p1;
    p1->data = b[1];
    pHead->next = p1;
    printALink(pHead);
    free(pHead);
    free(p1);
    
    return 0;
}