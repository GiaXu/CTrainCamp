#include "insert_sort.h"
#include <stdlib.h>

BOOL insertionSort(const int *input, size_t input_length, int *output)
{
    if (NULL == input || 0 == input_length || NULL == output)
    {
        return FALSE;
    }

    size_t i_input = 0;
    size_t sortedNumber = 0;

    output[0] = input[0]; //init the first one
    ++i_input;
    ++sortedNumber;

    while (i_input < input_length)
    {
        size_t m_output = 0;

        while (input[i_input] >= output[m_output])
        {
            ++m_output;

            if (sortedNumber == m_output)
            {
                break;
            }
        }

        if (m_output < sortedNumber)
        {
            move(output, m_output, (sortedNumber - m_output), 1);
        }

        output[m_output] = input[i_input];

        sortedNumber++;

        ++i_input;

    } //while

    return TRUE;
}

BOOL move(int *Buffer, size_t start, size_t count, int step)
{
    if (count == 0 || step == 0)
    {
        return FALSE;
    }

    size_t last = start + count;
    size_t i = 0; //change last when the loop ends once

    while (step > 0)
    {

        while (last > start)
        {
            Buffer[last] = Buffer[last - 1];
            --last;

        } //while

        --step;
        ++i;
        last = start + count + i;

    } //while

    while (step < 0)
    {
        while (last > start)
        {
            Buffer[start - 1] = Buffer[start];
            ++start;
        }
        start = start - count - 1;
        ++step;

    } //while

    return TRUE;
}

BOOL reverse(int *Buffer, size_t count)
{
    if (NULL == Buffer || 0 == count)
    {
        return FALSE;
    }

    size_t last = count - 1;
    int tmp = 0;
    size_t i = 0;

    while (i < last)
    {
        /*
        tmp = Buffer[last];
        Buffer[last] = Buffer[i];
        Buffer[i] = tmp;
        */
        Buffer[last] ^= Buffer[i];
        Buffer[i] ^= Buffer[last];
        Buffer[last] ^= Buffer[i];

        ++i;
        --last;
    }

    return TRUE;
}
TNode *creatNode(void)
{
    TNode *p = malloc(sizeof(TNode));
    p->next = NULL;

    return p;
}

TNode *insertion(const int *input, size_t input_lenth)
{

    if (NULL == input || 0 == input_lenth)
    {
        printf("Wrong\n");
        return NULL;
    }
    TNode *pHead = creatNode();
    size_t i_input = 0;
    pHead->number = input[i_input++];
    TNode *p0 = pHead;

    while (i_input < input_lenth)
    {
        p0 = pHead;

        while (p0->number < input[i_input])
        {

            if (NULL == p0->next)
            {
                p0->next = creatNode();
                p0 = p0->next;
                p0->number = input[i_input];

                break;
            }

            p0 = p0->next;

        } //while

        if (p0->number > input[i_input])
        {
            if (pHead == p0)
            {
                TNode *p = creatNode();

                p->next = pHead;
                p->number = input[i_input];
                pHead = p;
            }
            else
            {
                TNode *p1 = getPrevNode(pHead, p0);
                if (NULL == p1)
                {
                    // error
                    destory(pHead);
                    return NULL;
                }
                else
                {
                    TNode *p = creatNode();
                    p1->next = p;
                    p->next = p0;
                    p->number = input[i_input];
                }
            }

        } //if

        ++i_input;
    } //while

    return pHead;
}

size_t countOfList(TNode *pHead)
{
    TNode *p0 = pHead;
    size_t i = 1;
    while (NULL != p0->next)
    {
        p0 = p0->next;
        ++i;
    }
    return i;
}

TNode *getPrevNode(TNode *pHead, TNode *p)
{
    if (NULL == pHead || NULL == p || pHead == p)
    {
        return NULL;
    }

    TNode *p0 = pHead;

    while (p0->next != p)
    {
        p0 = p0->next;
        if (0 == p0)
        {
            break;
        }
        // check if p0 is NULL
    }

    return p0;
}

void destory(TNode *pHead)
{
    while (NULL != pHead)
    {
        pHead = remove_(pHead, pHead);
    }
}

TNode *remove_(TNode *pHead, TNode *p0)
{
    if (NULL == pHead || NULL == p0)
    {
        return pHead;
    }

    if (p0 == pHead)
    {
        pHead = pHead->next;
        free(p0);
        p0 = NULL;

        return pHead;
    }

  
    TNode *p1 = pHead;

    while (p1->next != p0)
    {
        p1 = p1->next;
        if ( NULL == p1)
        {
            return pHead;
        }
    }

    p1->next = p0->next;
    free(p0);
    p0 = NULL;

    return pHead;
}

void initIntArrayWithRadom(int *buffer, size_t count)
{
    if (NULL == buffer)
    {
        return;
    }

    for (size_t i = 0; i < count; ++i)
    {
        int tmp = random();
        if (tmp % 2)
        {
            tmp = -tmp;
        }
        buffer[i] = tmp / 10000000;
    }
}

TNode *reverNode(TNode *pHead)
{
    if (NULL == pHead)
    {
        return NULL;
    }
    //init
    TNode *p1 = pHead;

    if (NULL != pHead->next)
    {
        pHead = pHead->next;
    }

    TNode *p0 = pHead;

    if (NULL != pHead->next)
    {
        pHead = pHead->next;
    }
    //insert
    size_t i = 0;
    size_t m = countOfList(pHead);

    while (i < (m - 1))
    {
        p0->next = p1;
        while (p1->next != p0)
        {
            p1 = p1->next;
        }
        p1->next = pHead;
        p1 = p0;
        if (NULL != pHead->next)
        {
            pHead = pHead->next;

            while (p0->next != pHead)
            {
                p0 = p0->next;
            }
        }
        ++i;
    }

    //insert
    p0->next = p1;
    while (p1->next != p0)
    {
        p1 = p1->next;
    }
    p1->next = pHead;
    p1 = p0;

    while (p0->next != pHead)
    {
        p0 = p0->next;
    }

    /*
    //insert
    p0->next = p1;
    p1->next->next->next = pHead;
    p1 = p0;
    if (NULL != pHead->next)
    {
        pHead = pHead->next;

        while (p0->next != pHead)
        {
            p0 = p0->next;
        }
    }*/

    pHead->next = p1;
    p0->next = NULL;

    return pHead;
}

TNode *reversNode(TNode *pHead)
{
    if (NULL == pHead)
    {
        return NULL;
    }

    if (NULL == pHead->next)
    {
        return pHead;
    }

    //init
    TNode *p0 = pHead;
    TNode *p1 = pHead->next;

    if (NULL == p1->next)
    {
        p1->next = p0;
        p0->next = NULL;
        pHead = p1;

        return pHead;
    }

    TNode *p2 = p1->next;

    while (TRUE)
    {
        p1->next = pHead;
        p0->next = p2;
        pHead = p1;
        if (NULL == p2)
        {
            break;
        }

        p1 = p2;
        p2 = p2->next;
    }

    return pHead;
}
