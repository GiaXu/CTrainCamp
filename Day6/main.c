#include <stdio.h>
#include <stdlib.h>

#define N 10

typedef struct stu
{
    int num;
    int score;
} stu;

int fun6_1(int *input, size_t start, size_t count, int x);

void fun6_2(int n);

void fun6_3(int x);

int fun6_4(struct stu *s, struct stu *h);

int main()
{
    //Day6-1
    int input[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int x = 0;
    printf("(Day6-1)Please input x:\n");
    scanf("%d", &x);

    printf("%d\n", fun6_1(input, 0, sizeof(input) / sizeof(int), x));




    //Day6-2
    int n = 0;
    printf("(Day6-2)Please input n:\n");
    scanf("%d", &n);
    fun6_2(n);




    //Day6-3
    int x1 = 0;
    printf("(Day6-3)Please input x:\n");
    scanf("%d", &x1);
    fun6_3(x1);




    //Day6-4
    stu s[N] = {{101, 97}, {102, 96}, {103, 98}, {104, 93}, {105, 93}, {106, 97}, {107, 93}, {108, 99}, {109, 95}, {110, 95}};
    stu h[N];
    int num, i;
    num = fun6_4(s, h);

    printf("(Day6-4)Having %d min score\n", num);

    for (i = 0; i < num; ++i)
    {
        printf("No.%d\tscore :%d\n", h[i].num, h[i].score);
    }




    //Day6-5
    int m;

    struct node
    {
        int code;
        struct node *next;
    };

    struct node *head, *p1, *p2;
    head = p1 = (struct node *)malloc(sizeof(struct node));
    printf("(Day6-5)Please input m:\n");
    scanf("%d", &m);
    p1->next = 0;

    while (m != 0)
    {
        p1->code = m;
        p2 = (struct node *)malloc(sizeof(struct node));
        p1->next = p2;
        p1 = p2;
        p1->next = 0;
        scanf("%d", &m);
    }
    p1 = head;
    while (p1->next != 0)
    {
        printf("%d,", p1->code);
        p1 = p1->next;
    }

    free(head);
    free(p1);
    free(p2);

    return 0;
}