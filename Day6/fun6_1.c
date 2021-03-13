#include <stdio.h>

int fun6_1(int *input,size_t start, size_t count,int x)
{
    if (NULL == input || count <= 0)
    {
        return 0;
    }

    size_t mid = ((start + count) + start) / 2;

    if(input[mid] == x)
    {
        return 1;
    }
    else if(input[mid] > x)
    {
        return fun6_1(input,start,(mid - start ),x);
    }
    else
    { 
        return fun6_1(input,mid + 1,(start + count - mid - 1),x);
    }

}