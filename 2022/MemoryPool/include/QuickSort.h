#ifndef __QUICK_SORT_H__
#define __QUICK_SORT_H__

#include "MemoryPool.h"

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

struct Node_s{
    struct Node_s* left;
    struct Node_s* right;
    int value;
};
typedef struct Node_s Node_t;

Node_t* creatNode (MemoryPool_t* mp);
Node_t* _remove (Node_t* pHead, Node_t* p);
Node_t* _insert (Node_t* root, Node_t* pBase, Node_t* pNewNode);
Node_t* find (Node_t* root, int value);
Node_t* seek (Node_t* root, int offset);
void append (Node_t* pPrev, Node_t* pLast);
void destroy (MemoryPool_t mp, Node_t* pHead);
void swap (Node_t*pHead, Node_t* p1, Node_t* p2);
int length (Node_t* pHead);
Node_t* addANode (Node_t* pHead, Node_t* p);
void listRecords(const Node_t *pHead);
Node_t* getpHead (Node_t* p);

Node_t* Partition (Node_t* pLow, Node_t* pHigh);
void QuickSort (Node_t* pLow, Node_t* pHigh);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __QUICK_SORT_H__