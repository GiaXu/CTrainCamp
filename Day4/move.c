#include <stdio.h>

typedef enum
{
    FALSE,
    TRUE
} BOOL;

BOOL move(int *Buffer, size_t start, size_t count, int step)
{
    if (count == 0 || step == 0)
    {
        return FALSE;
    }

    size_t last = start + count;
    size_t i = 0; //change last when the loop ends once

    while (step > 0)
    {

        while (last > start)
        {
            Buffer[last] = Buffer[last - 1];
            --last;

        } //while

        --step;
        ++i;
        last = start + count + i;

    } //while

    while (step < 0)
    {
        while (last > start)
        {
            Buffer[start - 1] = Buffer[start];
            ++start;
        }
        start = start - count - 1;
        ++step;

    } //while

    return TRUE;
}
