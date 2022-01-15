/*#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;
typedef int KeyType;
#define MAXSIZE 100
#define N 8

typedef struct 
{
	KeyType key;
}SElemType;

typedef struct
{
	SElemType* elem;
	int length;
} SSTable; //查找表

typedef struct
{
	SSTable  r[MAXSIZE + 1];
	int length;
}SqList;  //顺序表

int Partition(SqList L,int low,int high) 
{
	L.r[0] = L.r[low];
	ElemType pivotkey = L.r[low].length;

	while (low < high) {
		while (low < high && L.r[high].length >= pivotkey)
		{
			--high;
			L.r[low] = L.r[high];
		}//while

		while (low < high && L.r[low].length <= pivotkey)
		{
			++low;
			L.r[high] = L.r[low];
		}
	}//while

	L.r[low] = L.r[0];
	return low;
}

void Qsort(SqList L,int low,int high) //快排（递归）
{
	if(low > high || low == high)
	{
		return;
	}
	if (low < high)
	{
		ElemType pivotkey = Partition(L,low,high);
		Qsort(L,low,(pivotkey - 1));
		Qsort(L,pivotkey + 1, high);
	}
}

void merge(SqList L, int start, int mid, int end) 
{
	int result[N+1];
	int a[10];
	int k = 0;
	int i = start;
	int j = mid + 1;
	while (i <= mid && j <= end) 
	{
		if (L.r[i].length < L.r[j].length) 
		{
			result[k++] = L.r[i++].length;
		}
		else {
			result[k++] = L.r[j++].length;
		}
	}
	if (i == mid + 1) 
	{
		while (j <= end)
		result[k++] = L.r[j++].length;
	}
	if (j == end + 1) 
	{
		while (i <= mid)
		result[k++] = L.r[i++].length;
	}
	for (j = 0, i = start; j < k; ++i, ++j) 
	{
		L.r[i].length = result[j];
	}
}

void mergeSort(SqList L, int start, int end)
{
	if (start >= end)
	{
		return;
	}
	int mid = (start + end) / 2;
	mergeSort(L, start, mid);
	mergeSort(L, mid + 1, end);
	merge(L, start, mid, end);
}

void seek(SSTable L, int m, int end, int key)
{
	int high = end;    
	int low = m;
	int mid = 0;
	while (low <= high)
	{

		mid = (low + high) / 2;  
		if (L.elem[mid].key == key)    
		{
			printf("%d\t",key);
			printf("at\t");
			printf("%d\t",mid);
			printf("location.\n");
			return;
		}
		else if (L.elem[mid].key > key)
		{
			high = mid - 1;
		}
		
		else
		{
			low = mid + 1;
		}
	}
	if (low > high)
	{
		printf("It does not in recently list.\n");
		return;
	}
}

int main() 
{
	SSTable ST;
	ST.elem = (SElemType*)malloc(sizeof(SElemType)*(N + 1));
	SqList L,L2;
	int p = 0;
	printf("Please input number:\n");
	for (int i = 1; i <= N; i++)
	{
		scanf("%d",&L.r[i].length);
		//L.r[i].length = p;
	}
	L.length = N;
	L2 = L; 
	L2.length = N;
	Qsort(L, 1, L.length);

	for (int i = 1; i <= N; i++)
	{
		printf("%d\n",L.r[i].length);
	}
	
	mergeSort(L2,1,L2.length);
	for (int i = 1; i <= N; i++)
		printf("%d\n",L2.r[i].length);
	
	return 0;
}

*/

#include<stdio.h>
#define ArrLen 20
#include <stdlib.h>
typedef int KeyType;
typedef struct{
    KeyType key;
}RedType;
typedef struct{
    RedType r[30];
	int length;
}SqList;

void printList(int arr[], int len) {
	int i;
	for (i = 0; i < len; i++) {
		printf("%d\t", arr[i]);
	}
}
void merge(int arr[], int start, int mid, int end) { //非递归归并查找
	int result[ArrLen];
	int k = 0;
	int i = start;
	int j = mid + 1;
	while (i <= mid && j <= end) {
		if (arr[i] < arr[j]){
			result[k++] = arr[i++];
        }
		else{
			result[k++] = arr[j++];
        }
	}
	if (i == mid + 1) {
		while(j <= end)
			result[k++] = arr[j++];
	}
	if (j == end + 1) {
		while (i <= mid)
			result[k++] = arr[i++];
	}
	for (j = 0, i = start ; j < k; i++, j++) {
		arr[i] = result[j];
	}
}
 
void mergeSort(int arr[], int start, int end) { //递归归并查找
	if (start >= end)
		return;
	int mid = ( start + end ) / 2;
	mergeSort(arr, start, mid);
	mergeSort(arr, mid + 1, end);
	merge(arr, start, mid, end);
}
 
 int Partition(SqList L,int low,int high){ //快速排序
	L.r[0]=L.r[low];
	KeyType pivotkey = L.r[low].key;
	while(low < high){
		while(low < high && L.r[high].key >= pivotkey)
			--high;
		L.r[low] = L.r[high];
		while(low < high && L.r[low].key <= pivotkey)
			++low;
		L.r[high] = L.r[low];
	}
	L.r[low] = L.r[0];
	return low;
}
void Qsort(SqList L,int low,int high){ //递归快速排序
	if(low < high){
		KeyType pivotkey = Partition(L,low,high);
        Qsort(L,low,pivotkey-1);
        Qsort(L,pivotkey+1,high);
	}
}

int main()
{
	printf("Please input :\n");
	int arr[8]; 
	int i; 
	int x; 
	for(i = 0;i < 8;i++)  //归并排序
	{ 
		scanf("%d",&x);
		arr[i] = x; 
	} 
	mergeSort(arr, 0, 9);
	printList(arr, 10);
	return 0;
}
void display(int* array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int getStandard(int array[], int i, int j) {
    int key = array[i];
    while (i < j) {
        while (i < j && array[j] >= key) {
            j--;
        }
        if (i < j) {
            array[i] = array[j];
        }
        while (i < j && array[i] <= key) {
            i++;
        }
        if (i < j) {
            array[j] = array[i];
        }
    }
    array[i] = key;
    return i;
}

void QuickSort(int array[], int low, int high) {

    if (low < high) 
	{
        int standard = getStandard(array, low, high);
        QuickSort(array, low, standard - 1);
        QuickSort(array, standard + 1, high);
    }
}
/*
int main()  //快速排序
{
	int array[8]; 
    //int array[] = {49, 38, 65, 97, 76, 13, 27, 49, 10};
    int size    = sizeof(array) / sizeof(int);


	int i; 
	int x; 
	for(i=0;i<8;i++) 
	{ 
	scanf("%d",&x);
	array[i]=x; 
	} 
	printf("%d \n", size);
    QuickSort(array, 0, size - 1);
    display(array, size);
	return 0;
}*/
