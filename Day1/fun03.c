#include <stdio.h>

void fun03(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;

    return;
}