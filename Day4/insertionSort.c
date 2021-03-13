#include <stdio.h>

typedef enum {FALSE, TRUE} BOOL;

BOOL insertionSort(const int *input, size_t input_length, int *output)
{
    if (NULL == input || 0 == input_length || NULL == output)
    {
        return FALSE;
    }

    size_t i_input = 0;
    size_t sortedNumber = 0;

    output[0] = input[0]; //init the first one
    ++i_input;
    ++sortedNumber;

    while (i_input < input_length)
    {
        size_t m_output = 0;

        while (input[i_input] >= output[m_output])
        {
            ++m_output;

            if (sortedNumber == m_output)
            {
                break;
            }
        }

        if (m_output < sortedNumber)
        {
            move(output, m_output, (sortedNumber - m_output), 1);
        }

        output[m_output] = input[i_input];

        sortedNumber++;

        ++i_input;

    } //while

    return TRUE;
}
