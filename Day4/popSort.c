#include <stdio.h>

typedef enum {FALSE, TRUE} BOOL;

void popSort(int *input, size_t input_length)
{
    if (NULL == input || 0 == input_length)
    {
        return;
    }

    size_t k = input_length;

    while (k > 0)
    {
        BOOL noSweap = TRUE;

        for (size_t i = 0; i < k - 1; ++i)
        {
            if (input[i + 1] < input[i])
            {
                int m = input[i + 1];
                input[i + 1] = input[i];
                input[i] = m;

                noSweap = FALSE;
            }
        }

        if (noSweap)
        {
            break;
        }

        --k;
    }
}
