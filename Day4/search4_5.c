#include <stdio.h>

int search4_5(int *input, size_t start, size_t count, int x)
{
    if (NULL == input || count <= 0)
    {
        return -1;
    }

    size_t mid = ((start + count) + start) / 2;

    if (input[mid] == x)
    {
        return mid;
    }
    else if (input[mid] > x)
    {
        return search4_5(input, start, (mid - start), x);
    }
    else
    {
        return search4_5(input, mid + 1, (start + count - mid - 1), x);
    }
}
