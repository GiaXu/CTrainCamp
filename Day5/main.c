#include <stdio.h>

void fun5_2(int aa[], int x, int *n);

void fun5_3(int *a, int *b);

int fun5_4(int lim, int aa[100]);

int main()
{
   
    //Day5-1
    int a[100];
    int n = 0;
    int i = 0;
    printf("(Day5-1)Please input numbers:\n");
    scanf("%d", &n);
    printf("Please input arrys:\n");
    for (i = 0; i < n; ++i)
    {
        scanf("%d,", &a[i]);
    }

    for (i = n - 1; i >= 0; --i)
    {
        printf("%d\t", a[i]);
    }

    printf("\n");


    //Day5-2
    int a0[100], x;
    int n0, i0;
    printf("(Day5-2)Please input numbers:\n");
    scanf("%d", &n0);
    printf("Please input a:\n");
    for (i0 = 0; i0 < n; ++i0)
    {
        scanf("%d,", &a0[i0]);
    }
    printf("Please input x:\n");
    scanf("%d", &x);

    fun5_2(a0, x, &n0);

    for (i0 = 0; i0 < n - 1; ++i0)
    {
        printf("%2d", a0[i0]);
    }


    printf("\n");

    //Day5-3
    int i1 = 0;
    int n1 = 0;
    int m[100];
    fun5_3(m, &n1);
    printf("(Day5-3)now n is \n%d\n", n1);
    for (i1 = 0; i1 < n1; ++i1)
    {
        printf("%d", m[i1]);
    }
    return 0;

    printf("\n");


    //Day5-4
    int lim, aa[100];
    printf("(Day5-4)Please input lim:\n");
    scanf("%d", &lim);
    printf("%d\n", fun5_4(lim, aa));


    printf("\n");

    //Day5-5
    int a2[3][3];
    int i2, j, s = 0;
    printf("(Day5-5)Please input a:\n");
    for (i2 = 0; i2 < 3; ++i2)
    {
        for (j = 0; j < 3; ++j)
        {
            scanf("%d,", &a[i2]);
        }
    }
    for (i2 = 0; i2 < 3; ++i2)
    {
        s += a[i2];
    }
    printf("%d\n", s);


    printf("\n");


    //Day5-6
    int a3[3][3], i3, j3;
    printf("(Day5-6)Please input a:\n");
    for (i3 = 0; i3 < 9; ++i3)
    {
        scanf("%d", &a3[0][0] + i3);
    }

    printf("before init is:\n");

    for (i3 = 0; i3 < 9; ++i3)
    {
        printf("%2d", a3[0][0] + i3);

        if (i3 % 3 == 2)
        {
            printf("\n");
        }
    }

    printf("NOW is:\n");

    for (i3 = 0; i3 < 3; ++i3)
    {
        for (j3 = 0; j3 < 3; ++j3)
        {
            printf("%2d", a3[j3][i3]);

            if (j3 == 2)
            {
                printf("\n");
            }
        }
    }

    return 0;
}