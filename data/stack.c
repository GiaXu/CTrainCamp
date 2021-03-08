#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

void initStack(struct TStack *pStack, int size)
{
    pStack->top = 0;
    pStack->size = size;
    pStack->stack = malloc(sizeof(struct Range) * size);
}

void initIntStack(struct TStackInt *pStack, int size)
{
    pStack->top = 0;
    pStack->size = size;
    pStack->stack = malloc(sizeof(int) * size);
}

void releaseStack(struct TStack *pStack)
{
    if (NULL == pStack || NULL == pStack->stack)
    {
        return;
    }

    free(pStack->stack);

    pStack->stack = NULL;
    pStack->top = 0;
    pStack->size = 0;
}

void releaseIntStack(struct TStackInt *pStack)
{
    if (NULL == pStack || NULL == pStack->stack)
    {
        return;
    }

    free(pStack->stack);

    pStack->stack = NULL;
    pStack->top = 0;
    pStack->size = 0;
}

BOOL isFull(const struct TStack *pStack)
{
    if (pStack->top < pStack->size)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

BOOL isFull_Int(const struct TStackInt *pStack)
{
    if (pStack->top < pStack->size)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

BOOL isEmpty(const struct TStack *pStack)
{
    if (0 == pStack->top)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOL isEmpty_Int(const struct TStackInt *pStack)
{
    if (0 == pStack->top)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOL push(struct TStack *pStack, int start, int count)
{
    if (isFull(pStack))
    {
        return FALSE;
    }
    else
    {
        pStack->stack[pStack->top].start = start;
        pStack->stack[pStack->top].count = count;
        pStack->top++;
        return TRUE;
    }
}

BOOL push_int(struct TStackInt *pStack, char number)
{
    if (isFull_Int(pStack))
    {
        return FALSE;
    }
    else
    {
        pStack->stack[pStack->top] = number;

        pStack->top++;
        return TRUE;
    }
}

const struct Range *top(const struct TStack *pStack)
{
    if (isEmpty(pStack))
    {
        return NULL;
    }
    else
    {
        return pStack->stack + (pStack->top - 1);
    }
}

int top_Int(const struct TStackInt *pStack)
{
    if (isEmpty_Int(pStack))
    {
        return 10;
    }
    else
    {
        return pStack->stack[pStack->top - 1];
    }
}

void pop(struct TStack *pStack)
{
    if (isEmpty(pStack))
    {
        return;
    }
    else
    {
        pStack->top--;
    }
}

void pop_Int(struct TStackInt *pStack)
{
    if (isEmpty_Int(pStack))
    {
        return;
    }
    else
    {
        pStack->top--;
    }
}

void printStack(const struct TStack *pStack)
{
    if (NULL == pStack)
    {
        printf("Null Stack.");
        return;
    }

    printf("[");
    for (int i = 0; i < pStack->top; ++i)
    {

        printf("(%d,%d)", pStack->stack[i].start, pStack->stack[i].count);
        if (i + 1 < pStack->top)
        {
            printf(",");
        }
    }
    printf("], top = %d\n", pStack->top);
}

void testStack(void)
{
    struct TStack aStack;

    aStack.top;

    struct TStack *pStack = malloc(sizeof(struct TStack));
    pStack->top;

    initStack(pStack, 20);

    int i = 0;

    while (!isFull(pStack))
    {
        for (int i = 0; i < pStack->size; i++)
        {
            push(pStack, i, (i + 2));
        }
    }

    printStack(pStack);
    printf("\n");

    while (!isEmpty(pStack))
    {
        top(pStack);
        pop(pStack);
        printStack(pStack);
        printf("\n");
    }

    releaseStack(pStack);

    free(pStack);

    return;
}

int Qaz(const char *input)
{
    struct TStackInt Num; //number
    struct TStackInt OP;  //ch

    initIntStack(&Num, 100);
    initIntStack(&OP, 100);

    while ('\0' != *input)
    {
        int tmp = *input;
        if (tmp >= '0' && tmp <= '9')
        {
            // is number
            push_int(&Num, tmp - '0');
        }
        else
        {
            // assume it is an operator
            if (isEmpty_Int(&OP))
            {
                push_int(&OP, tmp);
            }
            else
            {
                int _p1 = priority(tmp);
                int _p2 = priority(top_Int(&OP));
                if (_p1 > _p2)
                {
                    push_int(&OP, tmp);
                }
                else
                {
                    // calculate....
                    int b = top_Int(&Num);
                    pop_Int(&Num);

                    int a = top_Int(&Num);
                    pop_Int(&Num);

                    int op = top_Int(&OP);
                    pop_Int(&OP);

                    int result = calculate(a, op, b);

                    push_int(&Num, result);
                    continue;
                }
            }
        }

        input++;
    } // while

    while (!isEmpty_Int(&OP))
    {
        int b = top_Int(&Num);
        pop_Int(&Num);

        int a = top_Int(&Num);
        pop_Int(&Num);

        int op = top_Int(&OP);
        pop_Int(&OP);

        int result = calculate(a, op, b);

        push_int(&Num, result);

    } // while

    int p = top_Int(&Num);

    releaseIntStack(&Num);
    releaseIntStack(&OP);

    return p;
}


int calculate(int a, int op, int b)
{
    int result = 0;

    switch (op)
    {
    case '+':

        result = a + b;

        break;

    case '-':

        result = a - b;

        break;

    case '*':

        result = a * b;

        break;

    case '/':

        result = a / b;

        break;

    default:

        printf("Wrong!\n");

        break;
    }

    return result;
}

int priority(int ch)
{
    if (ch == '(')
    {
        return 3;
    }

    if (ch == '*' || ch == '/')
    {
        return 2;
    }

    if (ch == '+' || ch == '-')
    {
        return 1;
    }

    if (ch == ')')
    {
        return 0;
    }
}