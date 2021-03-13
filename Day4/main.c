#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUMBER 10

typedef enum
{
    FALSE,
    TRUE
} BOOL;

void fun4_3(char *a);

int fun4_4(char *a, char *b);

int search4_5(int *input, size_t start, size_t count, int x);

int *fun4_6(char *st, int a[3]);

void popSort(int *input, size_t input_length);

BOOL insertionSort(const int *input, size_t input_length, int *output);

void initIntArrayWithRadom(int *buffer, size_t count);

BOOL move(int *Buffer, size_t start, size_t count, int step);

int main()
{
    //Day4-1
    printf("Day4-1\n");

    int input[MAX_NUMBER];
    int output[MAX_NUMBER] = {0};
    int input0[MAX_NUMBER];

    for (size_t i = 0; i < MAX_NUMBER; ++i)
    {
        int tmp = random();

        if (tmp % 2)
        {
            tmp = -tmp;
        }

        input[i] = tmp / 10000000;
    }

    initIntArrayWithRadom(input, MAX_NUMBER);

    for (size_t i = 0; i < MAX_NUMBER; ++i)
    {
        printf("%d,", input[i]);
    }
    
    printf("\n");

    if (insertionSort(input, sizeof(input) / sizeof(int), output))
    {
        for (size_t i = 0; i < 10; ++i)
        {
            printf("%d,", output[i]);
        }

        printf("\n");
    }
    else
    {
        printf("Wrong\n");
    }




    //Day4-2
    printf("Day4-2\n");

    popSort(input0, sizeof(input0) / sizeof(int));
    for (size_t i0 = 0; i0 < sizeof(input0) / sizeof(int); ++i0)
    {
        printf("%d,", input0[i0]);
    }

    printf("\n");




    //Day4-3
    char a[100] = {0};
    printf("(Day4-3)Please input a:\n");
    fgets(a, sizeof(a), stdin);
    fun4_3(a);
    puts(a);




    //Day4-4
    char a0[100], b[20];
    printf("(Day4-4)Please input a0:\n");
    fgets(a0, sizeof(a0), stdin);
    printf("Please input b:\n");
    fgets(b, sizeof(b), stdin);
    printf("%d\n", fun4_4(a0, b));




    //Day4-5
  
    int x = 0;

    printf("(Day4-5)Please input the searched number:\n");
    scanf("%d", &x);

    int p = search4_5(output, 0, sizeof(output) / sizeof(int), x);

    if (p >= 0)
    {
        printf("Found! at [%d]\n", p);
    }
    else
    {
        printf("Not Found!\n");
    }




    //Day4-6
    char a1[100];
    int b1[3] = {0, 0, 0};
    int i1;
    printf("(Day4-6)Please input a1:\n");
    fgets(a1, sizeof(a1), stdin);
    int* p1 = fun4_6(a1, b1);
    for (i1 = 0; i1 < 3; ++i1)
    {
        printf("%d,", *p1++);
        
    }

    return 0;
}