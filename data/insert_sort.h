#ifndef __INSERT_SORT_H__
#define __INSERT_SORT_H__
#include <stdio.h>
typedef struct Node
{
    struct Node *next;
    int number;
   
}TNode;

typedef enum {FALSE, TRUE} BOOL;

BOOL insertionSort(const int* input, size_t input_length, int* output);

BOOL move(int *Buffer, size_t start, size_t count,int step);

BOOL reverse(int *Buffer, size_t count);

TNode* insertion(const int* input,size_t count);

TNode *creatNode(void);

size_t countOfList(TNode *pHead);

TNode *getPrevNode(TNode *pHead, TNode *p);     

void destory(TNode* pHead);

TNode *remove_(TNode *pHead,TNode *p0);

void initIntArrayWithRadom(int* buffer, size_t count);

TNode* reversNode(TNode* pHead);

#endif // __INSERT_SORT_H__