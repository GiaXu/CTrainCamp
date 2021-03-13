#include <stdio.h>

void fun5_2(int aa[],int x,int* n)
{
    int i,j;
    for(i = 0;i < *n;++i)
    {
        if(aa[i] == x)
        {
           while (i < *n)
           {
               j = i + 1;
               aa[i] = aa[j];
               ++i;
           }
           
        }
    }
}