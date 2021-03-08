#include "pop_sort.h"
#include "insert_sort.h"
#include "stack.h"
#include <stdlib.h>
#include <math.h>

void popSort(int *input, size_t input_length)
{
    if (NULL == input || 0 == input_length)
    {
        return;
    }

    size_t k = input_length;

    while (k > 0)
    {
        BOOL noSweap = TRUE;

        for (size_t i = 0; i < k - 1; ++i) //i < k - 1
        {
            if (input[i + 1] < input[i])
            {
                int m = input[i + 1];
                input[i + 1] = input[i];
                input[i] = m;

                noSweap = FALSE;
            }
        }

        if (noSweap)
        {
            break;
        }

        --k;
    }
}

TNode *popSort_d(int *input, size_t input_length)
{
    TNode *pHead = creatList(input, input_length);

    TNode *p0 = checkList(pHead);
    TNode *p1 = pHead;

    while (p0 != pHead)
    {
        if (p1->number > p1->next->number)
        {
            pHead = exchange(pHead, p1);

            if (p0->next == p1)
            {
                p1 = pHead;
            }
        }
        else
        {
            p1 = p1->next;
        }

    } //while

    return pHead;
}

TNode *creatList(int *input, size_t input_length)
{
    if (NULL == input || 0 == input_length)
    {
        return NULL;
    }

    TNode *pHead = creatNode();
    TNode *p0 = pHead;
    p0->number = input[0];

    for (size_t i = 1; i < input_length; ++i)
    {
        if (NULL == p0->next)
        {
            p0->next = creatNode();
            p0 = p0->next;
        }
        p0->number = input[i];
    }

    return pHead;
}

TNode *checkList(TNode *pHead)
{
    if (NULL == pHead)
    {
        return NULL;
    }
    TNode *p0 = pHead;

    while (NULL != p0->next)
    {

        p0 = p0->next;
    }
    return p0;
}

TNode *exchange(TNode *pHead, TNode *p)
{
    if (NULL == pHead || NULL == p || NULL == p->next)
    {
        return NULL;
    }

    TNode *p0 = p->next;
    TNode *p1 = pHead;

    if (pHead == p)
    {
        p1->next = p0->next;
        p0->next = p;

        return p0;
    }

    while (p1->next != p)
    {
        p1 = p1->next;
    }

    p->next = p0->next;
    p0->next = p;
    p1->next = p0;

    return pHead;
}

/*int search(int *input, size_t input_length, int x)
{
    if (NULL == input || 0 == input_length)
    {
        return -1;
    }

    int *pHead = input[0];
    size_t middle = input_length / 2;
    int *p = input[middle];

    if (x == *pHead || x == *p || x == input[input_length - 1])
    {
        if (x == *pHead)
        {
            return 0;
        }

        if (x == *p)
        {
            return middle;
        }

        if (x == input[input_length - 1])
        {
            return (input_length - 1);
        }
    }

    while (x < *p)
    {
        size_t i = 1;
        size_t middle_prev = middle / 2;
        int* p1 = input[middle_prev];
        if(p == p1++)
        {
            return -1;
        }

        if(x == *p1)
        {
            return middle_prev;
        }

        if(x < *p1)
        {
            middle = middle_prev;
            p = p1;
        }

        if(x > *p1)
        {
            size_t middle_prev_next = (middle_prev + middle) / 2;
            int* p2 = input[middle_prev_next];
            if(x == *p2)
            {
                return middle_prev_next;
            }
            if(x < *p2)
            {
                p = p2;
                middle = middle_prev_next;
            }

            if(x > *p2)
            {
                p1 = p2;
                middle_prev = middle_prev_next;
            }

        }
    }
    
}
*/
int search(int *input,size_t start, size_t count,int x)
{
    if (NULL == input || count <= 0)
    {
        return -1;
    }

    size_t mid = ((start + count) + start) / 2;

    if(input[mid] == x)
    {
        return mid;
    }
    else if(input[mid] > x)
    {
        return search(input,start,(mid - start ),x);
    }
    else
    { 
        return search(input,mid + 1,(start + count - mid - 1),x);
    }
}


int search_d(int *input, int start, int count, int x)
{
    if (NULL == input || count <= 0)
    {
        return -1;
    }

    int mid = ((start + count) + start) / 2;

    if (input[mid] == x)
    {
        return (mid - start);
    }
    else if (input[mid] > x)
    {
        count = mid;
    }
    else
    {
        count = (start + count - mid - 1);
        start = mid + 1;
    }

    struct TStack aStack ;
    struct TStack* pStack = &aStack;
    initStack(pStack, 20);

    push(pStack, start, count);
    const struct Range* aTopValue = NULL;

    while (!isEmpty(pStack))
    {
        aTopValue = top(pStack);
        pop(pStack);
        int mid = ((aTopValue->start + aTopValue->count) + aTopValue->start) / 2;
        
        if (input[mid] == x)
        {
            return mid;
        }
        else if (input[mid] > x)
        {
            count = (mid - start);
        }
        else
        {
            count = (start + count - mid - 1);
            start = mid + 1;
        }

        push(pStack, start, count);


    }


}

