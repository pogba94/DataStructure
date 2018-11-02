/****************************************************************************
*  Includes
*****************************************************************************/

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "windows.h"

/****************************************************************************
*  Typde definnition
*****************************************************************************/

typedef int ElemType_t;
typedef struct BSTNode{
	ElemType_t key;
	struct BSTNode* lchild;
	struct BSTNode* rchild;
}BSTNode,*pBSTNode;
typedef pBSTNode BSTree;

/****************************************************************************
*  Declaration
*****************************************************************************/

pBSTNode BSTreeInsert(BSTree T,ElemType_t e);
void BSTreeInOrderTraverse(BSTree T);
pBSTNode BSTreeFind(BSTree T,ElemType_t e);
pBSTNode BSTreeFindMax(BSTree T);
pBSTNode BSTreeFindMin(BSTree T);
BSTree BSTreeDelete(BSTree T,ElemType_t e);
int BSTreeDepth(BSTree T);
int BSTreeSize(BSTree T);
void printBSTree(BSTree T);
static void displayMenu(void);
void BSTreeDemo(void);

/****************************************************************************
*  Functions
*****************************************************************************/

pBSTNode BSTreeInsert(BSTree T,ElemType_t e)
{
	if(T == NULL){
		T = (pBSTNode)malloc(sizeof(BSTNode));
		if(T != NULL){
			T->key = e;
			T->lchild = T->rchild = NULL;
		}
	}else{
		if(e > T->key){
			T->rchild = BSTreeInsert(T->rchild,e);
		}else if(e < T->key){
			T->lchild = BSTreeInsert(T->lchild,e);
		}
	}
	return T;
}

void BSTreeInOrderTraverse(BSTree T)
{
	if(T != NULL){
		BSTreeInOrderTraverse(T->lchild);
		printf("%d\t",T->key);
		BSTreeInOrderTraverse(T->rchild);
	}
}

pBSTNode BSTreeFind(BSTree T,ElemType_t e)
{
	if(T == NULL)
		return NULL;
	if(T->key == e){
		return T;
	}else if(T->key > e){
		return BSTreeFind(T->lchild,e);
	}else{
		return BSTreeFind(T->rchild,e);
	}
}

pBSTNode BSTreeFindMax(BSTree T)
{
	if(T == NULL)
		return NULL;
	if(T->rchild == NULL)
		return T;
	return BSTreeFindMax(T->rchild);
}

pBSTNode BSTreeFindMin(BSTree T)
{
	if(T == NULL)
		return NULL;
	if(T->lchild == NULL)
		return T;
	return BSTreeFindMin(T->lchild);
}

BSTree BSTreeDelete(BSTree T,ElemType_t e)
{
	pBSTNode tmp;
	if(T == NULL){
	}else if(T->key > e){
		T->lchild =  BSTreeDelete(T->lchild,e);
	}else if(T->key < e){
		T->rchild = BSTreeDelete(T->rchild,e);
	}else if(T->lchild != NULL && T->rchild != NULL){ //find node
		tmp = BSTreeFindMin(T->rchild);
		T->key = tmp->key;
		T->rchild = BSTreeDelete(T->rchild,T->key);
	}else{
		tmp = T;
		if(T->lchild == NULL){
			T = T->rchild;
		}else if(T->rchild == NULL){
			T = T->lchild;
		}else{
			T = NULL;
		}
		free(tmp);
	}
	return T;
}

int BSTreeDepth(BSTree T)
{
	int depth = 0;
	if(T != NULL){
		int leftDepth = BSTreeDepth(T->lchild);
		int rightDepth = BSTreeDepth(T->rchild);
		depth = (leftDepth>rightDepth) ? leftDepth+1 : rightDepth+1;
	}
	return depth; 
}

int BSTreeSize(BSTree T)
{
	if(T != NULL){
		return 1 + BSTreeSize(T->lchild) + BSTreeSize(T->rchild);
	}
	return 0;
}

void printBSTree(BSTree T)
{
	if(T != NULL){
		printf("----%d----",T->key);
		if(T->lchild){
			printf("%d----",T->lchild->key);
		}else{
			printf("NULL----");
		}
		if(T->rchild){
			printf("%d----\n",T->rchild->key);
		}else{
			printf("NULL----\n");
		}
		printBSTree(T->lchild);
		printBSTree(T->rchild);
	}
}

static void displayMenu(void)
{
	printf("-----------------------Menu--------------------------\n");
	printf("-      1.  insert item         2.  delete item      -\n");
	printf("-      3.  find item           4.  get size         -\n");
	printf("-      5.  find max            6.  find min         -\n");
	printf("-      7.  get depth           8.  traverse tree    -\n");
	printf("-      9.  show menu           10. print tree       -\n");
	printf("-      11. random insert                            -\n");
	printf("-----------------------------------------------------\n\n");
}

void BSTreeDemo(void)
{
	int tmp;
	ElemType_t element;
	BSTree myBSTree = NULL;

	displayMenu();
	while(1){
		printf("\nplease choose which action to do:");
		scanf("%d",&tmp);
		printf("\n");
		switch(tmp){
			case 1:
			{
				printf("please input the element you want to insert:");
				scanf("%d",&element);
				myBSTree = BSTreeInsert(myBSTree,element);
				printf("element had been inserted\n");
				break;
			}
			case 2:
			{
				printf("please input the element you want to delete:");
				scanf("%d",&element);
				myBSTree = BSTreeDelete(myBSTree,element);
				break;
			}
			case 3:
			{
				pBSTNode pTmpNode;
				printf("please input the element you want to find:");
				scanf("%d",&element);
				pTmpNode = BSTreeFind(myBSTree,element);
				if(!pTmpNode){
					printf("not found\n");
				}else{
					printf("found\n");
				}
				break;
			}
			case 4:
			{
				printf("size of BSTree:%d\n",BSTreeSize(myBSTree));
				break;
			}
			case 5:
			{
				pBSTNode pTmpNode =  BSTreeFindMax(myBSTree);
				if(!pTmpNode){
					printf("no element\n");
				}else{
					printf("max element:%d\n",pTmpNode->key);
				}
				break;
			}
			case 6:
			{
				pBSTNode pTmpNode = BSTreeFindMin(myBSTree);
				if(!pTmpNode){
					printf("no element\n");
				}else{
					printf("min element:%d\n",pTmpNode->key);
				}
				break;
			}
			case 7:
			{
				printf("Depth of BSTree:%d\n",BSTreeDepth(myBSTree));
				break;
			}
			case 8:
			{
				printf("traverse BSTree:\n");
				BSTreeInOrderTraverse(myBSTree);	
				break;
			}
			case 9:
			{
				displayMenu();
				break;
			}
			case 10:
			{
				printBSTree(myBSTree);
				break;
			}
			case 11:
			{
				ElemType_t min,max,mod,*dataSet;
				int num,start,end;
				printf("please input min val of data set:");
				scanf("%d",&min);
				printf("please input max val of data set:");
				scanf("%d",&max);
				printf("please input the size of data set:");
				scanf("%d",&num);
				printf("current time:%ld\n",time(NULL));
				srand(time(NULL));
				dataSet = (ElemType_t*)malloc(sizeof(ElemType_t)*num);
				if(dataSet == NULL){
					printf("malloc fail\n");
					break;
				}
				mod = max-min+1;
				for(int i=0;i<num;i++)
					dataSet[i] = (ElemType_t)(rand()%mod+min);
				start = GetTickCount();
				for(int i=0;i<num;i++)
					myBSTree = BSTreeInsert(myBSTree,dataSet[i]);
				end = GetTickCount();
				printf("insert time:%d ms (%d elements)\n",end-start,num);
				free(dataSet);
				break;
			}
			default:
			{
				printf("illegal cmd\n");
				break;
			}
		}
	}
}


void BSTreeTest(void)
{
	ElemType_t tmp;
	pBSTNode pMax,pMin;
	BSTree myBSTree = NULL;

	for (int i = 0; i < 10; i++)
	{
		printf("please input the %d th element:",i);
		scanf("%d",&tmp);
		myBSTree = BSTreeInsert(myBSTree,tmp);
	}
	printf("inOrder traverse BSTree:\n");
	BSTreeInOrderTraverse(myBSTree);
	printf("please input element you want to find:");
	scanf("%d",&tmp);
	if(!BSTreeFind(myBSTree,tmp)){
		printf("not found\n");
	}else{
		printf("found\n");
	}
	pMax = BSTreeFindMax(myBSTree);
	pMin = BSTreeFindMin(myBSTree);
	printf("max element:%d\n",pMax->key);
	printf("min element:%d\n",pMin->key);
	printf("please input element you want to delete:");
	scanf("%d",&tmp);
	myBSTree = BSTreeDelete(myBSTree,tmp);
	printf("inOrder traverse BSTree:\n");
	BSTreeInOrderTraverse(myBSTree);
}

int main(void)
{
	BSTreeDemo();
	for(;;);
	return 0;
}