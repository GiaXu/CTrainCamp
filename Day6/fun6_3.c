#include <stdio.h>

void fun6_3(int x)
{
    int i,a[2];
    a[0] = x * x;
    a[1] = x * x * x;
    for(i = 0;i < 2;++i)
    {
        printf("%d\n",a[i]);
    }
}