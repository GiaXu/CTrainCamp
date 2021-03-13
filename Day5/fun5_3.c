#include <stdio.h>

void fun5_3(int* a,int* b)
{
    int i = 1;
    for(i = 1;i <= 100;++i)
    {
        if(i % 7 == 0 || i % 11 == 0)
        {
            *a = i;
            ++a;
            ++(*b);
        }
    }
}