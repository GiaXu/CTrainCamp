#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int len21(char *s);

int fun22(char *s, char k);

void fun24(char *s);

void fun25(char *a, char *b);

void fun26(char *p);

void fun27(char *a, char *b, char *c);


int main()
{
    //Day3-1
    char c[100];

    printf("(Day3-1)Please input char:\n");
    scanf("%s", c);

    printf("number is %d\n", len21(c));




    //Day3-2
    char s[100];
    char w;

    printf("(Day3-2)Please input a checked word:\n");
    scanf("%c", &w);

    printf("Please input char:\n");
    scanf("%s", s);

    printf("have %d\n", fun22(s, w));




    //Day3-3
    char a[100];
    printf("(Day3-3)Please input a:\n");
    scanf("%s", a);
    int k,i;
    while (fgets(a, sizeof(a), stdin))
    {
        k = strlen(a);
        a[0] -= 32;
        for (i = 0; i < k; ++i)
        {
            if (a[i] == ' ')
            {
                a[i + 1] -= 32;
                printf("%c", a[i]);
            }
        }
        printf("\n");
    }




    //Day3-4
    char a0[100];
    printf("(Day3-4)Please input a0:\n");
    fgets(a0, sizeof(a0), stdin);
    fun24(a0);
    puts(a0);




    //Day3-5
    char a1[100], b[100];
    printf("(Day3-5)Please input a1:\n");
    fgets(a1, sizeof(a1), stdin);
    fun25(a1, b);

    puts(b);




    //Day3-6
    char str[80];
    printf("(Day3-6)Please input str:\n");
    fgets(str, sizeof(str), stdin);

    fun26(str);

    printf("now is :\n");
    puts(str);




    //Day3-7
    char a2[100], b0[100], c0[100];
    printf("(Day3-7)Please input a2:\n");
    fgets(a2, sizeof(a2), stdin);
    printf("Please input b0:\n");
    fgets(b0, sizeof(b0), stdin);
    fun27(a2, b0, c0);

    puts(c0);


    return 0;
}