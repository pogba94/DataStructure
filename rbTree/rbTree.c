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

typedef enum{
	RED = 0,
	BLACK = 1,
}color_t;

typedef int ElemType_t;
typedef struct RBTNode{
	ElemType_t key;
	color_t color;
	struct RBTNode* lchild;
	struct RBTNode* rchild;
	struct RBTNode* parent;
}RBTNode,*pRBTNode;
typedef pRBTNode RBTree;

char* colorName[2] = {"red","black"};

/****************************************************************************
*  Declaration
*****************************************************************************/



/****************************************************************************
*  Functions
*****************************************************************************/

static pRBTNode grandparent(pRBTNode node)
{
	return (node != NULL && node->parent != NULL) ? node->parent->parent : NULL;
}

static pRBTNode uncle(pRBTNode node)
{
	if(grandparent(node) != NULL)
		return (grandparent(node)->lchild == node->parent) ? grandparent(node)->rchild : grandparent(node)->lchild;
	else
		return NULL;
}

static void leftRotate(RBTree *pT,pRBTNode node)
{
	if(pT != NULL && (*pT) != NULL && node != NULL){
		pRBTNode rc = node->rchild;
		if((node->rchild = rc->lchild)){//left child exsits
			rc->lchild->parent = node;
		}
		rc->lchild = node;
		if((rc->parent = node->parent)){//node is not root node
			if(node->parent->lchild == node)
				node->parent->lchild = rc;
			else
				node->parent->rchild = rc;
		}else{
			*pT = rc;
		}
		node->parent = rc;
	}
}

static void rightRotate(RBTree *pT,pRBTNode node)
{
	if(pT != NULL && (*pT) != NULL && node != NULL){
		pRBTNode lc = node->lchild;
		if((node->lchild = lc->rchild)){//right child exsits
			lc->rchild->parent = node;
		}
		lc->rchild = node;
		if((lc->parent = node->parent)){//node is not root node
			if(node->parent->rchild == node)
				node->parent->rchild = lc;
			else
				node->parent->lchild = lc;
		}else{
			*pT = lc;
		}
		node->parent = lc;
	}
}

static void RBTInsertFix(RBTree *pT,pRBTNode x)
{
	if(pT != NULL && *pT != NULL && x != NULL){
		pRBTNode u;
		while(x->parent && x->parent->color == RED){
			u = uncle(x);
			if(u && u->color == RED){ // case 1
				grandparent(x)->color = RED;
				u->color = x->parent->color = BLACK;
				x = grandparent(x);
			}else{
				if(x->parent->rchild == x){//case 2
					if(grandparent(x)->rchild == x->parent){
						x->parent->color = BLACK;
						grandparent(x)->color = RED;
						leftRotate(pT,grandparent(x));
					}else if(grandparent(x)->lchild == x->parent){
						leftRotate(pT,x->parent);
						x = x->lchild;   //take care!
					}
				}else if(x->parent->lchild == x){//case 3
					if(grandparent(x)->lchild == x->parent){
						x->parent->color = BLACK;
						grandparent(x)->color = RED;
						rightRotate(pT,grandparent(x));
					}else if(grandparent(x)->rchild == x->parent){
						rightRotate(pT,x->parent);
						x = x->rchild;
					}
				}
			}
		}
		if(x->parent == NULL) //x is root
			x->color = BLACK;
	}
}

pRBTNode RBTreeInsert(RBTree *pT,ElemType_t e)
{
	if(*pT == NULL){
		pRBTNode pNode = (pRBTNode)malloc(sizeof(RBTNode));
		if(pNode == NULL)
			return NULL;
		pNode->lchild = pNode->rchild = NULL;
		pNode->key = e;
		pNode->color = BLACK;
		pNode->parent = NULL;
		*pT = pNode;
		return pNode;
	}else{
		pRBTNode cur = *pT,curParent = NULL;
		while(cur != NULL){
			curParent = cur;
			if(cur->key > e){
				cur = cur->lchild;
			}else if(cur->key < e){
				cur = cur->rchild;
			}else{
				return NULL;
			}
		}
		cur = (pRBTNode)malloc(sizeof(RBTNode));
		if(cur == NULL)
			return NULL;
		cur->lchild = cur->rchild = NULL;
		cur->color = RED;
		cur->key = e;
		cur->parent = curParent;
		if(curParent->key > e)
			curParent->lchild = cur;
		else
			curParent->rchild = cur;
		RBTInsertFix(pT,cur);
		return cur;
	}
}

void RBTreeInOrderTraverse(RBTree T)
{
	if(T != NULL){
		RBTreeInOrderTraverse(T->lchild);
		printf("%d\t",T->key);
		RBTreeInOrderTraverse(T->rchild);
	}
}

pRBTNode RBTreeFind(RBTree T,ElemType_t e)
{
	if(T == NULL)
		return NULL;
	if(T->key == e){
		return T;
	}else if(T->key > e){
		return RBTreeFind(T->lchild,e);
	}else{
		return RBTreeFind(T->rchild,e);
	}
}

pRBTNode RBTreeFindMax(RBTree T)
{
	if(T == NULL)
		return NULL;
	if(T->rchild == NULL)
		return T;
	return RBTreeFindMax(T->rchild);
}

pRBTNode RBTreeFindMin(RBTree T)
{
	if(T == NULL)
		return NULL;
	if(T->lchild == NULL)
		return T;
	return RBTreeFindMin(T->lchild);
}

static void RBTDeleteFix(RBTree *pT,pRBTNode node)
{
	if(pT != NULL && pT != NULL&& node != NULL){
		
	}
}

int RBTreeDelete(RBTree *pT,ElemType_t e)
{
	if(pT != NULL || *pT != NULL)
		return -1;
	pRBTNode x = *pT,p = NULL;
	while(x != NULL){
		if(x->key == e){
			break;
		}else if(x->key > e){
			p = x;
			x = x->lchild;
		}else{
			p = x;
			x = x->rchild;
		}
	}
	if(x == NULL) //not found
		return -2;
	if(x->lchild == NULL && x->rchild == NULL){//delete root node or leaf node
		if(x == *pT){
			*pT = NULL;
		}else{
			if(x->parent->lchild == x)
				x->parent->lchild = NULL;
			else
				x->parent->rchild = NULL;
		}
		free(x);
	}else if(x->lchild != NULL && x->rchild != NULL){//the delete node has two children
		pRBTNode next = RBTreeFindMin(x->rchild);
		x->key = next->key;
		if(next->parent->lchild == next)
			next->parent->lchild = next->rchild;
		else if(next->parent->rchild == next)
			next->parent->rchild = next->rchild;
		if(next->rchild){
			next->rchild->parent = next->parent;
			RBTDeleteFix(pT,next->rchild);
		}
		free(next);
	}else{//the deleted node only have one child
		if(x->lchild){ // left child only
			if(x->parent->lchild == x)
				x->parent->lchild = x->lchild;
			else
				x->parent->rchild = x->lchild;
			x->lchild->parent = x->parent;
			RBTDeleteFix(pT,x->lchild); 
		}else{ // right child only
			if(x->parent->lchild == x)
				x->parent->lchild = x->rchild;
			else
				x->parent->rchild = x->rchild;
			x->rchild->parent = x->parent;
			RBTDeleteFix(pT,x->rchild);
		}
		free(x);
	}
	return 0;
}

int RBTreeDepth(RBTree T)
{
	int depth = 0;
	if(T != NULL){
		int leftDepth = RBTreeDepth(T->lchild);
		int rightDepth = RBTreeDepth(T->rchild);
		depth = (leftDepth>rightDepth) ? leftDepth+1 : rightDepth+1;
	}
	return depth; 
}

int RBTreeSize(RBTree T)
{
	if(T != NULL){
		return 1 + RBTreeSize(T->lchild) + RBTreeSize(T->rchild);
	}
	return 0;
}

void printRBTree(RBTree T)
{
	if(T != NULL){
		printf("----%d----%s----",T->key,colorName[T->color]);
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
		printRBTree(T->lchild);
		printRBTree(T->rchild);
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

void RBTreeDemo(void)
{
	int tmp;
	ElemType_t element;
	RBTree myRBTree = NULL;

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
				if(RBTreeInsert(&myRBTree,element))
					printf("element had been inserted\n");
				break;
			}
			case 2:
			{
				printf("please input the element you want to delete:");
				scanf("%d",&element);
				if(!RBTreeDelete(&myRBTree,element))
					printf("element %d had been deleted\n",element);
				break;
			}
			case 3:
			{
				pRBTNode pTmpNode;
				printf("please input the element you want to find:");
				scanf("%d",&element);
				pTmpNode = RBTreeFind(myRBTree,element);
				if(!pTmpNode){
					printf("not found\n");
				}else{
					printf("found\n");
				}
				break;
			}
			case 4:
			{
				printf("size of RBTree:%d\n",RBTreeSize(myRBTree));
				break;
			}
			case 5:
			{
				pRBTNode pTmpNode =  RBTreeFindMax(myRBTree);
				if(!pTmpNode){
					printf("no element\n");
				}else{
					printf("max element:%d\n",pTmpNode->key);
				}
				break;
			}
			case 6:
			{
				pRBTNode pTmpNode = RBTreeFindMin(myRBTree);
				if(!pTmpNode){
					printf("no element\n");
				}else{
					printf("min element:%d\n",pTmpNode->key);
				}
				break;
			}
			case 7:
			{
				printf("Depth of RBTree:%d\n",RBTreeDepth(myRBTree));
				break;
			}
			case 8:
			{
				printf("traverse RBTree:\n");
				RBTreeInOrderTraverse(myRBTree);	
				break;
			}
			case 9:
			{
				displayMenu();
				break;
			}
			case 10:
			{
				printRBTree(myRBTree);
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
					RBTreeInsert(&myRBTree,dataSet[i]);
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


void RBTreeTest(void)
{
	ElemType_t tmp;
	pRBTNode pMax,pMin;
	RBTree myRBTree = NULL;

	for (int i = 0; i < 10; i++)
	{
		printf("please input the %d th element:",i);
		scanf("%d",&tmp);
		RBTreeInsert(&myRBTree,tmp);
	}
	printf("inOrder traverse RBTree:\n");
	RBTreeInOrderTraverse(myRBTree);
	printf("please input element you want to find:");
	scanf("%d",&tmp);
	if(!RBTreeFind(myRBTree,tmp)){
		printf("not found\n");
	}else{
		printf("found\n");
	}
	pMax = RBTreeFindMax(myRBTree);
	pMin = RBTreeFindMin(myRBTree);
	printf("max element:%d\n",pMax->key);
	printf("min element:%d\n",pMin->key);
	printf("please input element you want to delete:");
	scanf("%d",&tmp);
	myRBTree = RBTreeDelete(myRBTree,tmp);
	printf("inOrder traverse RBTree:\n");
	RBTreeInOrderTraverse(myRBTree);
}

int main(void)
{
	RBTreeDemo();
	for(;;);
	return 0;
}