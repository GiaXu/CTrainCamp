#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MAX_NUMBER 10
typedef enum {FALSE, TRUE} BOOL;
typedef struct Node
{
    struct Node *next;
    int number;
   
}TNode;

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


int main(void)
{
    int input[MAX_NUMBER];
    int output[MAX_NUMBER] = {0};
   
    for (size_t i= 0; i < MAX_NUMBER; ++i)
    {
        int tmp = random();
        if (tmp % 2)
        {
            tmp = -tmp;
        }
        input[i] = tmp / 10000000;
    }

    if (insertionSort(input, sizeof(input)/sizeof(int), output))
    {
        for(size_t i = 0;i < 10;++i)
        {
            printf("%d,",output[i]);
        }

        printf("\n");
    }

    else
    {
        printf("Wrong\n");
    }
 

    int data[10] = {0,0,1,2,3,4,5};
    size_t str = 2;
    size_t cou = 5;
    move(data, str, cou, -2);

        for(size_t i = 0;i < 10;++i)
        {
            printf("%d,",data[i]);
        }

        printf("\n");
    

   if (reverse(output, 10))
    {
        for(size_t i = 0;i < 10;++i)
        {
            printf("%d,",output[i]);
        }

        printf("\n");
    }

    else
    {
        printf("Wrong\n");
    }

    TNode *p = insertion(input, sizeof(input) / sizeof(int));
    
    while (NULL != p)
    {
        int number = p->number;
       printf("%d,", number);
        p = p->next;
    }
    printf("\n");

   


    TNode* pHead = reversNode(p);

    while (NULL != pHead)
    {
        int number = pHead->number;
        printf("%d,", number);
        pHead = pHead->next;
    }
    printf("\n");

    destory(pHead);
    pHead = NULL;


    int x = 0;
    printf("Please input the searched number:\n");
    scanf("%d", &x);
    int p = search(input, 0,sizeof(input) / sizeof(int) , x);
    if(p >= 0)
    {
        printf("Found! at [%d]\n",p);
    }
    else
    {
        printf("Not Found!\n");
    }
   
}
