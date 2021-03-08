#ifndef __INSERT_SORT_D_H__
#define __INSERT_SORT_D_H__
#include "insert_sort.h"

typedef struct Node_d
{
    struct Node_d *next;
    struct Node_d *prev;
    int number;
   
}TNode_d;

TNode_d *insertion_d(const int *input, size_t input_lenth);

TNode_d *creatNode_d(void);

void destory_d(TNode_d* pHead);

TNode_d* remove_d(TNode_d *pHead,TNode_d *p0);




#endif //__INSERT_SORT_D_H__