#include<stdio.h>
#include<stdlib.h>

typedef char TElemType;
typedef struct BiTNode {
	TElemType  data;
	struct BiTNode* lchild, * rchild;
}BiTNode, *BiTree;

int sum = 0;
int top = 1;

void push(BiTNode** a, BiTNode* elem) {
	a[++top] = elem;
}

void pop(){
	if(-1 == top)
	return;
	--top;
}

BiTNode* getTop(BiTNode** a){
	return a[top];
}

void PreOrder(BiTree T) {  
	if (T) {
		printf ("%c",T->data);
		PreOrder(T->lchild);
		PreOrder(T->rchild);
	}
}
void InOrder(BiTree T) {
	if (T) {
		InOrder(T->lchild);
		printf ("%c",T->data);
		InOrder(T->rchild);
	}
}
void PostOrder(BiTree T) {
	if (T) {
		PostOrder(T->lchild);
		PostOrder(T->rchild);
		printf ("%c",T->data);
	}
}
void CreateBit(BiTree *T) {
	TElemType ch;
	scanf("%c",&ch);
	if (ch == '#')
	{
		*T = NULL;
		return;
	}
	else
	{
		*T = (BiTree)malloc(sizeof(BiTNode));
		(*T)->data = ch;
		CreateBit(&(*T)->lchild);
		CreateBit(&(*T)->rchild);
	}
	
}

void PreOrders(BiTNode* T){ //先序非递归算法
	BiTNode* stack[15];
	int top = -1;
	BiTNode* p = T;
	while (NULL != p || -1 != top)
	{
		if(NULL != p){
			stack[++top] = p;
			printf("%c",p->data);
			p = p->lchild;
		}
		else{
			p = stack[top--];
			p = p->rchild;
		}
	}//while
	
}

void InOrders(BiTree Tree) { //中序非递归算法
	BiTNode* a[20] = {0};
	BiTNode* p = Tree;
	push(a,Tree);
	while (-1 != top)
	{
		while ((p = getTop(a)) && p)
		{
			push(a,p->lchild);
		}
		pop();
		if(-1 != top){
			p = getTop(a);
			pop(); 
			printf("%c",p->data); 
			push(a,p->rchild);
		}
		
	}
	
}
int leafc(BiTree T) {
	if(T) 
	{
		leafc(T->lchild);
		leafc(T->rchild);
		if(NULL == T->lchild && NULL == T->rchild)
		sum++;
	}
	return sum;
}
int main() 
{
	BiTree T;
	printf("Please input:\n");
	CreateBit(&T);
	printf("Create successfully!\n");

	printf("Preorder is:  ");
	PreOrder(T); 
	printf("\n");
	printf("Preorder successfully!\n");

	printf("Inorder is:  ");
	InOrder(T); 
	printf("\n");
	printf("InOrder successfully!\n");

	printf("Postorder is:  ");
	PostOrder(T); 
	printf("\n");
	printf("PostOrder successfully!\n");

	printf("Preorders is:  ");
	PreOrders(T);
	printf("\n");
	printf("Preorders successfully!\n");
	
	printf("Inorders is:  ");
	InOrders(T);
	printf("\n");
	printf("Inorders successfully!\n");

	int num = 0;
	num = leafc(T);
	printf("Leafc number is:  ");
	printf("%d",num);
	printf("\n");


	free(T);
	return 0;
}