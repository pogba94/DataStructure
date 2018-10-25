/****************************************************************************
*  Includes
*****************************************************************************/

#include "stdio.h"
#include "stdlib.h"

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
typedef int statu_t;

/****************************************************************************
*  Declaration
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
		printf("%d\n",T->key);
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
//		printf("not found\n");
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

static void displayMenu(void)
{
	printf("-----------------------Menu-------------------------\n");
	printf("-      1. insert item         2.  delete item      -\n");
	printf("-      3. find item           4.  get size         -\n");
	printf("-      5. find max            6.  find min         -\n");
	printf("-      7. get depth           8.  traverse tree    -\n");
	printf("-      9. show menu                                -\n");
	printf("----------------------------------------------------\n\n");
}

void BSTreeDemo(void)
{
	int tmp;
	ElemType_t element;
	BSTree myBSTree = NULL;

	displayMenu();
	while(1){
		printf("please choose which action to do:");
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
			default:
			printf("illegal cmd\n");
			break;
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

/****************************************************************************
*  Functions
*****************************************************************************/

int main(void)
{
	BSTreeDemo();
	for(;;);
	return 0;
}