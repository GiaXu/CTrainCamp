#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void initIntArrayWithRadom(int *buffer, size_t count)
{
    if (NULL == buffer)
    {
        return;
    }

    for (size_t i = 0; i < count; ++i)
    {
        int tmp = random();
        if (tmp % 2)
        {
            tmp = -tmp;
        }
        buffer[i] = tmp / 10000000;
    }
}