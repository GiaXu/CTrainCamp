#include <string.h>
/*
#include "insert_sort.h"
#include "insert_sort_d.h"
*/
#include <stdlib.h>
/*
#include "pop_sort.h"
#include "func_pointer.h"
#include "stack.h"
#include "filetest.h"
*/
#include <math.h>
#include <stdio.h>
#include "SUT.h"

#define MAX_NUMBER 10

struct TA
{

    char m_a;
    char m_d;
    int m_b;
    //float m_c;
};

struct TB
{
    char m_e;
    char m_g;

    int m_f;
    int m_h;
};

struct TStudent
{
    int id;
    int grade;
    //char name[20];
    struct TName
    {
        char FirstName[10];
        char SecondName[10];

    } name;
};

union TC
{
    char m_a[4];
    int m_b;
};

int inc(int *a)
{

    ++(*a);
    return *a;
}

//int a = 1000;
int func()
{
    static int a = 1000;
    printf("&a = %p\n", &a);
    a += 1;
    return a;
}

int test01()
{
    int h = 100;
    {
        int h = 200;
        printf("h = %d\n", h);
    }
    printf("h = %d\n", h);
    printf("&h = %p\n", &h);
    inc(&h);
    printf("h = %d\n", h);

    printf("func() = %d\n", func());
    printf("func() = %d\n", func());
    printf("func() = %d\n", func());
    printf("func() = %d\n", func());

    return 0;

    union TC K;
    printf("&K = %p\n", &K);
    printf("&K.m_a = %p\n", &K.m_a);
    printf("&K.m_b = %p\n", &K.m_b);

    printf("\n");

    K.m_b = 0x0a0b0c0d;
    printf("K.m_a[0] = %x\n", K.m_a[0]);
    printf("K.m_a[1] = %x\n", K.m_a[1]);
    printf("K.m_a[2] = %x\n", K.m_a[2]);
    printf("K.m_a[3] = %x\n", K.m_a[3]);

    printf("K.m_b = %x\n", K.m_b);

    printf("\n");

    char tmp = K.m_a[1];
    K.m_a[1] = K.m_a[2];
    K.m_a[2] = tmp;
    tmp = K.m_a[0];
    K.m_a[0] = K.m_a[3];
    K.m_a[3] = tmp;

    printf("K.m_a[0] = %x\n", K.m_a[0]);
    printf("K.m_a[1] = %x\n", K.m_a[1]);
    printf("K.m_a[2] = %x\n", K.m_a[2]);
    printf("K.m_a[3] = %x\n", K.m_a[3]);

    printf("K.m_b = %x\n", K.m_b);

    printf("\n");

    struct TStudent A;
    A.id = 101;
    A.grade = 100;
    strcpy(A.name.FirstName, "Xu");
    strcpy(A.name.SecondName, "Jiaqi");

    printf("id = %d\n", A.id);
    printf("grade = %d\n", A.grade);
    printf("Firstname = %s\n", A.name.FirstName);
    printf("Secondname = %s\n", A.name.SecondName);

    printf("\n");

    struct TStudent *pA = &A;
    printf("id = %d\n", pA->id);
    printf("grade = %d\n", (*pA).grade);
    printf("Firstname = %s\n", pA->name.FirstName);
    printf("Secondname = %s\n", pA->name.SecondName);

    printf("\n");

    printf("sizeof(TA) = %ld\n", sizeof(struct TA));

    struct TA G;
    printf("&G = %p\n", &G);
    printf("&G.a = %p\n", &G.m_a);
    printf("&G.d = %p\n", &G.m_d);
    printf("&G.b = %p\n", &G.m_b);

    printf("\n");

    G.m_a = 'a';
    G.m_d = 'd';
    G.m_b = 201230825;

    printf("G.m_a = %c\n", G.m_a);
    printf("G.m_d = %c\n", G.m_d);
    printf("G.m_b = %d\n", G.m_b);

    printf("\n");

    struct TA *pG = &G;
    printf("pG->m_a = %c\n", pG->m_a);
    printf("pG->m_d = %c\n", pG->m_d);
    printf("pG->m_b = %d\n", pG->m_b);

    printf("\n");

    char *pch = (char *)pG;
    printf("pch[0] = %c\n", pch[0]);
    printf("pch[1] = %c\n", pch[1]);

    printf("\n");

    struct TB F;
    printf("sizeof(TB) = %ld\n", sizeof(struct TB));

    printf("&F = %p\n", &F);
    printf("&F.f = %p\n", &F.m_f);
    printf("&F.h = %p\n", &F.m_h);
    printf("&F.e = %p\n", &F.m_e);
    printf("&F.g = %p\n", &F.m_g);

    printf("sizeof(char) = %ld\n", sizeof(char));
    printf("sizeof(short) = %ld\n", sizeof(short));
    printf("sizeof(int) = %ld\n", sizeof(int));
    printf("sizeof(float) = %ld\n", sizeof(float));
    printf("sizeof(long) = %ld\n", sizeof(long));
    printf("sizeof(double) = %ld\n", sizeof(double));

    printf("\n");

    printf("sizeof(char*) = %ld\n", sizeof(char *));
    printf("sizeof(short*) = %ld\n", sizeof(short *));
    printf("sizeof(int*) = %ld\n", sizeof(int *));
    printf("sizeof(float*) = %ld\n", sizeof(float *));
    printf("sizeof(long*) = %ld\n", sizeof(long *));
    printf("sizeof(double*) = %ld\n", sizeof(double *));

    printf("\n");

    char a[100];
    printf("sizeof(char[100]) = %ld\n", sizeof(a));

    short b[100];
    printf("sizeof(short[100]) = %ld\n", sizeof(b));

    int c[100];
    printf("sizeof(int[100]) = %ld\n", sizeof(c));

    float d[100];
    printf("sizeof(float[100]) = %ld\n", sizeof(d));

    long e[100];
    printf("sizeof(long[100]) = %ld\n", sizeof(e));

    double f[100];
    printf("sizeof(double[100]) = %ld\n", sizeof(f));

    printf("\n");

    return 0;
}

int main(void)
{
    /*
   int input[MAX_NUMBER];

    int output[MAX_NUMBER] = {0};
   
    for (size_t i= 0; i < MAX_NUMBER; ++i)
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
 

    if (insertionSort(input, sizeof(input)/sizeof(int), output))
    {
        for(size_t i = 0;i < 10;++i)
        {
            printf("%d,",output[i]);
        }

        printf("\n");
    }

    else
    {
        printf("Wrong\n");
    }
 

    int data[10] = {0,0,1,2,3,4,5};
    size_t str = 2;
    size_t cou = 5;
    move(data, str, cou, -2);

        for(size_t i = 0;i < 10;++i)
        {
            printf("%d,",data[i]);
        }

        printf("\n");
    

  

   if (reverse(output, 10))
    {
        for(size_t i = 0;i < 10;++i)
        {
            printf("%d,",output[i]);
        }

        printf("\n");
    }

    else
    {
        printf("Wrong\n");
    }

    // TNode *p = insertion(input, sizeof(input) / sizeof(int));
    
    while (NULL != p)
    {
        int number = p->number;
       printf("%d,", number);
        p = p->next;
    }
    printf("\n");

   



    TNode_d *p = insertion_d(input, sizeof(input) / sizeof(int));

    while (NULL != p)
    {
        int number = p->number;
        printf("%d,", number);
        p = p->next;
    }
    printf("\n");

    TNode* pHead = reversNode(p);

    while (NULL != pHead)
    {
        int number = pHead->number;
        printf("%d,", number);
        pHead = pHead->next;
    }
    printf("\n");

    destory(pHead);
    pHead = NULL;


   

    popSort(input, sizeof(input) / sizeof(int));
    for (size_t i = 0; i < sizeof(input) / sizeof(int); ++i)
    {
        printf("%d,", input[i]);
    }

    printf("\n");

   

 

    TNode *p = popSort_d(input, sizeof(input) / sizeof(int));
    while (NULL != p)
    {
        int number = p->number;
        printf("%d,", number);
        p = p->next;
    }
    printf("\n");

    destory(p);
    p = NULL;


    int x = 0;
    printf("Please input the searched number:\n");
    scanf("%d", &x);
    int p = search(input, 0,sizeof(input) / sizeof(int) , x);
    if(p >= 0)
    {
        printf("Found! at [%d]\n",p);
    }
    else
    {
        printf("Not Found!\n");
    }
   


    //test_func_pointer();

   testStack();
 


    int x = 0;
    printf("Please input the searched number:\n");
    scanf("%d", &x);
    int p = search_d(output,0,sizeof(output) / sizeof(int),x);

    if(p >= 0)
    {
        printf("Found! at [%d]\n",p);
    }
    else
    {
        printf("Not Found!\n");
    }

const char* szInput="2*5-1+4*3";
const char* szInput2="1+2*3-5+7";

char a = szInput2[0];
char b = szInput2[1];

int p = Qaz(szInput);

printf("The result is %d\n",p);


printf("testFile begin\n");

testFile();

printf("testFile ends");*/

    //Day 1
    //1-1
    /*  
int main()
{  
    double x,y;

    printf("Please input x,y:\n");
    scanf("%lf,%lf",&x,&y);

    double a ;
    a = fun01(x,y);
    
    printf("result is %lf\n",a);

    return 0;
}
*/
    //1-2
    /*
int main()
{
    int num = 0;
    printf("Please input a number:\n");
    scanf("%d",&num);
    int c = fun02(num);

    printf("result is %d\n",c);
    
    return 0;
}
*/
    //1-3
    /*
int main()
{
    int a = 5;
    int b = 3;
    printf("a = %d,b = %d\n",a,b);

    fun03(&a,&b);
    printf("\n");

    printf("now,a = %d,b = %d\n",a,b);

    return 0;
}
*/
    //1-4
    /*
int main()
{
    int a = 0;
    int b = 0;

    printf("Please input a,b:\n");
    scanf("%d,%d",&a,&b);

    int c = fun04(a,b);
    printf("c is %d\n",c);

    int d = fun04_2(a,b);
    printf("d is %d\n",d);
    
    return 0;
}
*/
    //1-5
    /*
int main()
{
    printf("Please input num:\n");

    float num;
    scanf("%f", &num);

    float pi = fun05(num);
    printf("pi is %f\n",pi);

    return 0;
}
    */

    //Day 2
    //2-1
    /* 
    int main()
    { 
        float x;
        int m = 0;

        printf("Please input x:\n");
        scanf("%f", &x);
        printf("Please input m:\n");
        scanf("%d", &m);

        float re = fun11(x, m);

        printf("Now result is %f\n", re);

        return 0;
    }
   */
    //2-2
    /* 
    int main()
    {
        unsigned w;

        printf("Please input w:\n");
        scanf("%d", &w);

        unsigned x = fun12(w);

        printf("number is %d\n", x);

        return 0;
    }
    */
    //2-3
    /*
    int main()
    {
        long s;

        printf("Please input s:\n");
        scanf("%ld",&s);

        long t = fun13(s);

        printf("t is %ld\n",t);


        return 0;
    }
    */
    //2-4
    /*
    int main()
    {
         int n = 0;
        int k = 0;

        printf("Please input number:\n");
        scanf("%d",&n);

        printf("Please input k:\n");
        scanf("%d",&k);

        int x = fun14(n,k);
        printf("number is %d\n",x);


        return 0;
    }
    */
    //2-5
    /*
    int main()
    {
        int k = 0;
        printf("Please input number:\n");
        scanf("%d",&k);

        fun15(k);

        return 0;
    }
    */
    //2-6
    /*
    int main()
    {
        int a = 0;
        int n = 0;

        printf("Please input a:\n");
        scanf("%d", &a);

        printf("Please input n:\n");
        scanf("%d", &n);

        int i, j, t;
        int s = 0;
        for (i = 0; i < n; ++i)
        {
            s = s + a;
            a = a * 10;
        }

        t = s;

        while (t)
        {
            t = t / 10;
            s = s - t;
        }
        printf("result is %d\n", s);    

        return 0;
    }
    */
    //2-7
    /*
    int main()
    {

        return 0;
    } 
   
    float eps;
    printf("Please input eps:\n");
    scanf("%f", &eps);

    printf("result is %f\n",fun17(eps));
*/
    //2-8
    /* 
  
  int main()
  {
    int m;
    printf("Please input m :\n");
    scanf("%d",&m);
    printf("number is %d\n",fun18(m));

    return 0;
  }
    */

    //Day 3
    //3-1
    /*
    void main()
{
    char s[100];

    printf("Please input char:\n");
    scanf("%s",s);

    printf("number is %d\n",len21(s));
}
*/
    //3-2
    /*
    void main()
    {
    char s[100];
    char w;

    printf("Please input a checked word:\n");
    scanf("%c",&w);

    printf("Please input char:\n");
    scanf("%s",s);

    printf("have %d\n",fun22(s,w));
    }
    */
    //3-3
    /*

void main()
{
    printf("Please input a:\n");
    scanf("%s",a);
    while (gets(a))
    {
        k = strlen(a);
        a[0] -= 32;
        for(i = 0;i < k;++i)
        {
            if(a[i] == ' ')
            {
                a[i + 1] -= 32;
                printf("%c",a[i]);
            }
        }
        printf("\n");
    }

}*/
    //3-4
    /*
    void main()
    {
    char a[100];
    gets(a);
    fun24(a);
    puts(a);
    }
    */
    //3-5
    /*
    void main()
    {
        char a[100],b[100];
    
        gets(a);
        fun25(a,b);

        puts(b);
    }
    */
    //3-6
    /*
    void main()
    {
        char str[80];
        gets(str);

        fun26(str);

        printf("now is :\n");
        puts(str);
    }
    */
    //3-7
    /*
    char a[100],b[100],c[100];
    gets(a);
    gets(b);
    fun27(a,b,c);

    puts(c);
*/

    //Day 4
    //4-1
    /*
void main()
{
    int input[MAX_NUMBER];
    int output[MAX_NUMBER] = {0};
   
    for (size_t i= 0; i < MAX_NUMBER; ++i)
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

    if (insertionSort(input, sizeof(input)/sizeof(int), output))
    {
        for(size_t i = 0;i < 10;++i)
        {
            printf("%d,",output[i]);
        }

        printf("\n");
    }
    else
    {
        printf("Wrong\n");
    }  
} 
*/
    //4-2
    /*
    void main()
    {
    int input[MAX_NUMBER];
    int output[MAX_NUMBER] = {0};
   
    for (size_t i= 0; i < MAX_NUMBER; ++i)
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
    popSort(input, sizeof(input) / sizeof(int));
    for (size_t i = 0; i < sizeof(input) / sizeof(int); ++i)
    {
        printf("%d,", input[i]);
    }

    printf("\n");
    }
    */
    //4-3
    /*
    void main()
    {
    char a[100];
    gets(a);
    fun4_1(a);
    puts(a);
    }
    */
    //4-4
    /*
    void main()
    {
    char a[100],b[20];
    gets(a);
    gets(b);
    printf("%d\n",fun4_4(a,b));
    }
    */
    //4-5
    /*
    void main()
    {
    int input[MAX_NUMBER];

    int output[MAX_NUMBER] = {0};
   
    for (size_t i= 0; i < MAX_NUMBER; ++i)
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
 

    if (insertionSort(input, sizeof(input)/sizeof(int), output))
    {
        for(size_t i = 0;i < 10;++i)
        {
            printf("%d,",output[i]);
        }

        printf("\n");
    }

    else
    {
        printf("Wrong\n");
    }

     int x = 0;

    printf("Please input the searched number:\n");
    scanf("%d", &x);

    int p = search4_5(output,0,sizeof(output) / sizeof(int),x);

    if(p >= 0)
    {
        printf("Found! at [%d]\n",p);
    }
    else
    {
        printf("Not Found!\n");
    }
    }
    */
    //4-6
    /*
    void main()
    {
    char a[100];
    int b[3] = {0,0,0};
    int i;
    int* p;
    gets(a);
    p = fun4_6(a,b);
    for(i = 0;i < 3;++i)
    {
        printf("%d,",*p++);
    }
    }
    */

    //Day 5
    //5-1
    /*
    void main()
    {
    int a[100];
    int n = 0;
    int i = 0;
    printf("Please input numbers:\n");
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
    }
    */
    //5-2
    /*
    void main()
    {
    int a[100],x;
    int n,i;
    printf("Please input numbers:\n");
    scanf("%d",&n);
    printf("Please input a:\n");
    for(i = 0;i < n;++i)
    {
        scanf("%d,",&a[i]);
    }
        printf("Please input x:\n");
        scanf("%d",&x);

        fun5_2(a,x,&n);
        
        for(i = 0;i < n - 1;++i)
        {
            printf("%2d",a[i]);
        }
    
    }
    */
    //5-3
    /*
    int main()
    {
    int i = 0;
    int n = 0;
    int m[100];
    fun5_3(m,&n);
    printf("%d\n",n);
    for(i = 0;i < n;++i)
    {
        printf("%d",m[i]);
    }
    return 0;
    }
    */
    //5-4
    /*
    void main()
    {
    int lim,aa[100];
    scanf("%d",&lim);
    printf("%d\n",fun5_4(lim,aa));
    }
    */
    //5-5
    /*
   void main()
   {
    int a[3][3];
    int i,j,s = 0;
    for(i = 0;i < 3;++i)
    {
        for(j = 0;j < 3;++j)
        {
            scanf("%d",&a[i][j]);
        }
    }
    for(i = 0;i < 3;++i)
    {
        s += a[i][i];
    }
    printf("%d\n",s);
   }
   */
    //5-6
    /*
    void main()
    {
    int a[3][3],i,j;
    for(i = 0;i < 9;++i)
    {
        scanf("%d",&a[0][0] + i);
    } 
    
    printf("before init is:\n");

    for(i = 0;i < 9;++i)
    {
        printf("%2d",a[0][0] + i);

        if(i % 3 == 2)
        {
            printf("\n");
        }
    }

    printf("NOW is:\n");

    for(i = 0;i < 3;++i)
    {
        for(j = 0;j < 3;++j)
        {
            printf("%2d",a[j][i]);

            if(j == 2)
            {
                printf("\n");
            }
        }
    }
    }
    */

    //Day 6
    //6-1
    /*
    void main()
    {
    int x = 0;

    int input[MAX_NUMBER];

    int output[MAX_NUMBER] = {0};

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

    popSort(input, sizeof(input) / sizeof(int));
    for (size_t i = 0; i < sizeof(input) / sizeof(int); ++i)
    {
        printf("%d,", input[i]);
    }

    printf("\n");

    printf("Please input x:\n");
    scanf("%d",&x);

    printf("%d\n",fun6_1(input,0,sizeof(input) / sizeof(int),x));
    }
    */
    //6-2
    /*
    void main()
    {
    int n = 0;
    printf("Please input n:\n");
    scanf("%d",&n);
    fun6_2(n);
    }
    */
    //6-3
    /*
    void main()
    {

    int x = 0;
    printf("Please input x:\n");
    scanf("%d",&x);
    fun6_3(x);
    }
    */
    //6-4
    /*
    void main()
    {
        stu s[N] = {{101, 97}, {102, 96}, {103, 98}, {104, 93}, {105, 93}, {106, 97}, {107, 93}, {108, 99}, {109, 95}, {110, 95}};
        stu h[N];
        int num, i;
        num = fun6_4(s, h);

        printf("Having %d min score\n", num);

        for (i = 0; i < num; ++i)
        {
            printf("No.%d\tscore :%d\n", h[i].num, h[i].score);
        }
    }
    */
    //6-5
    /*
    void main()
    {
    int m;
    struct node
    {
        int code;
        struct node *next;
    };
    struct node *head, *p1, *p2;
    head = p1 = (struct node *)malloc(sizeof(struct node));
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
    }
    */

    return 0;
}