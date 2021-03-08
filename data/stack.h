#ifndef __STACK_H__
#define __STACK_H__
#include "insert_sort.h"

struct Range
{
    int start;
    int count;
    
}; 

struct TStack
{
    struct Range *stack;
    int size;
    int top;
};

struct TStackInt
{
    int *stack;
    int size; 
    int top;
};
//New
void initIntStack(struct TStackInt* pStack, int size);

void releaseIntStack(struct TStackInt *pStack);

BOOL isFull_Int(const struct TStackInt *pStack);

BOOL isEmpty_Int(const struct TStackInt *pStack);

BOOL push_int(struct TStackInt *pStack, char number);

int top_Int(const struct TStackInt *pStack);

void pop_Int(struct TStackInt *pStack);

int Qaz(const char* input);

int calculate(int a,int op,int b);

int priority(int ch);






// Old
void initStack(struct TStack *pStack,int size);

void releaseStack(struct TStack *pStack);

BOOL isFull(const struct TStack *pStack);

BOOL isEmpty(const struct TStack *pStack);

BOOL push(struct TStack *pStack,int start, int count);

const struct Range*  top(const struct TStack *pStack);

void pop(struct TStack *pStack);

void testStack(void);


#endif //__STACK_H__