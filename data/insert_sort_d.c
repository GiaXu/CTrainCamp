#include "insert_sort_d.h"
#include <stdlib.h>

TNode_d *insertion_d(const int *input, size_t input_lenth)
{
    if (NULL == input || 0 == input_lenth)
    {
        printf("Wrong\n");
        return NULL;
    }

    TNode_d *pHead = creatNode_d();
    size_t i_input = 0;
    pHead->number = input[i_input++];
    TNode_d *p0 = pHead;

    while (i_input < input_lenth)
    {
        p0 = pHead;

        while (p0->number < input[i_input])
        {

            if (NULL == p0->next)
            {
                TNode_d *p1 = creatNode_d();
                p0->next = p1;
                p1->prev = p0;
                p1->number = input[i_input];
                p0 = p1;

                break;
            }

            p0 = p0->next;
        }
        if (p0->number > input[i_input])
        {
            if (NULL == p0->prev)
            {
                TNode_d *p1 = creatNode_d();
                p1->next = p0;
                p0->prev = p1;
                p1->number = input[i_input];
                pHead = p1;
            }
            else
            {
                TNode_d *p1 = creatNode_d();
                TNode_d *p = p0->prev;
                p->next = p1;
                p1->prev = p;
                p1->next = p0;
                p0->prev = p1;
                p1->number = input[i_input];
            }
        }

        //while

        ++i_input;
    }
    return pHead;
}

TNode_d *creatNode_d(void)
{
    TNode_d *p = malloc(sizeof(TNode_d));
    p->next = NULL;
    p->prev = NULL;

    return p;
}

void destory_d(TNode_d *pHead)
{
    while (NULL != pHead)
    {
        pHead = remove_d(pHead, pHead);
    }
}

TNode_d *remove_d(TNode_d *pHead, TNode_d *p0)
{
    if (NULL == pHead || NULL == p0)
    {
        return pHead;
    }

    if (p0 == pHead)
    {
        pHead = pHead->next;
        pHead->prev = NULL;
        free(p0);
        p0 = NULL;

        return pHead;
    }

    TNode_d *p1 = pHead;

    while (p1->next != p0)
    {
        p1 = p1->next;

        if ( NULL == p1)
        {
            return pHead;
        }
    }
    p1->next = p0->next;
    p0->next->prev = p1;

    free(p0);
    p0 = NULL;

    return pHead;
}