#include <stdio.h>
#include <stdlib.h>

typedef struct LNode *List;
struct LNode{
    int Data;
    List Next;
};

typedef enum
{
    FALSE = 0,
    TRUE
} BOOL;

const char *option = 
    "\n=======================\n\
    Please choose a command :\n\
    1. Add a record;\n\
    2. List records;\n\
    3. Delete a record\n\
    4. Insert a record\n\
    0. Quit\n";

List createANode()
{
    List pHead;
    pHead = (List)malloc(sizeof(struct LNode));

    return pHead;
}

int Length(List PtrL)
{
    List P = PtrL;
    int i = 0;
    while (P)
    {
        P = P->Next;
        ++i;
    }
    return i;
}

BOOL Add(List pHead,List p2) //在末尾增加一个结点，p1后增加p2
{
    if(pHead == p2 || NULL == pHead || NULL == p2)
    {
        return FALSE;
    }
    List p = pHead;

    while (NULL != p->Next)
    {
        p = p->Next;
    }
    p->Next = p2;

    return TRUE;
    
}

List addRecord(List pHead,int data)
{
 
    List p0 = createANode();
    p0->Data = data;
    if(NULL == pHead)
    {
        pHead = p0;
    }
    else
    {
        List p = pHead;
        while(NULL != p->Next)
        {
            p = p->Next;
        }
        p->Next = p0;
    }

    return pHead;
}


List FindKth(int k,List PtrL)
{
    List P = PtrL;
    int i = 1;
    while (P != NULL && i < k)
    {
        P = P->Next;
        ++i;
    }
    if(i == k)
    return P;
    else 
    
    return NULL;
    
}


List Find(int x,List PtrL)
{
    List P = PtrL;
    while(P != NULL && P->Data != x)
    {
        P = P->Next;
    }
    return P;
}

List Insert(int data,int num,List PtrL)
{
    List p,s;
    if(1 == num)
    {
        s = (List)malloc(sizeof(struct LNode));
        s->Data = data;
        s->Next = PtrL;
        return s;
    }
    p = FindKth(num - 1,PtrL);
    if(NULL == p)
    {
        printf("wrong!");
        return NULL;
    }
    else
    {
        s = (List)malloc(sizeof(struct LNode));
        s->Data = data;
        s->Next = p->Next;
        p->Next = s;
        return PtrL;
    }
}

List Delete(int num,List PtrL)
{
    List p,s;
    if(1 == num)
    {
        s = PtrL;
        if(NULL != PtrL)
        {
            PtrL = PtrL->Next;
        }
        else
        {
            return NULL;
        }
        free(s);
        return PtrL;
    }
    p = FindKth(num - 1,PtrL);
    if(NULL == p)
    {
        printf("%d wrong",num-1);
        return NULL;
    }
    else if(NULL == p->Next)
    {
        printf("%d wrong",num);
        return NULL;
    }
    else
    {
        s = p->Next;
        p->Next = s->Next;
        free(s);
        return PtrL;
    }
    
}

BOOL Destroy(List pHead)
{
    if(NULL == pHead)
    {
        return FALSE;
    }
    int i = 1;
    do
    {
        pHead = Delete(i,pHead);
        ++i;
    } while (NULL != pHead);

    return TRUE;
    
}

BOOL listAllRecords(List pHead)
{
    if (NULL == pHead)
    {
        return FALSE;
    }
    while (NULL != pHead)
    {
        printf("%d ",pHead->Data);
        pHead = pHead->Next;
    }
    return TRUE;
}

List initData()
{
    List p0 = createANode();
    p0->Data = 56;

    List p1 = createANode();
    p1->Data = 42;
    p0->Next = p1;

    List p2 = createANode();
    p2->Data = 75;
    p1->Next = p2;

    return p0;
}

int main()
{
    List pHead = initData();
    printf("%s\n",option);

    int op = 0;
    scanf("%d",&op);

    int Data = 0;
    int num = 0;

    while (0 != op)
    {
        switch(op)
        {
            case 1: //add
            {
                printf("Please input data:\n");
                scanf("%d",&Data);
                

                pHead = addRecord(pHead,Data);
            }
            break;

            case 2: //print
            {
                listAllRecords(pHead);
                op = 0;
            }
            break;

            case 3: //delete
            {
                printf("Please input num:\n");
                scanf("%d",&num);

                pHead = Delete(num,pHead);

            }
            break;

            case 4: //insert
            {
                printf("Please input num:\n");
                scanf("%d",&num);

                printf("Please input data:\n");
                scanf("%d",&Data);

                pHead = Insert(Data,num,pHead);


            }
            break;

            default:
            {
                printf("Wrong options!\n");
            }
            break;
        }//switch

        printf("%s\n",option);
        scanf("%d",&op);

    }//while

    Destroy(pHead);
    pHead = NULL;
    
    return 0;
}
