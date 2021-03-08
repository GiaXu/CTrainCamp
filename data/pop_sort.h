#ifndef __POP_SORT_H__
#define __POP_SORT_H__
#include "insert_sort.h"
#include <math.h>

void popSort(int* input,size_t input_length);

TNode* popSort_d(int *input,size_t input_length);

TNode* creatList(int *input, size_t input_length);

TNode* checkList(TNode* pHead);

TNode *exchange(TNode *pHead,TNode *p);
/**
 * @brief dichotomizing search
 * 
 * @param input A sorted array 
 * @param start start array number
 * @param count last array number
 * @param x the target number
 * @return int : if -1 ,failing the search; else,return the array index
 */
int search(int *input, size_t start,size_t count, int x);

int search_d(int *input,int start, int count,int x);


#endif // __POP_SORT_H__