/****************************************************************************
*  Includes
*****************************************************************************/

#include "stdio.h"
#include "stdlib.h"

/****************************************************************************
*  Typde definnition
*****************************************************************************/

typedef int elemType_t;
typedef struct treeNode{
	elemType_t element;
	struct treeNode* lchild;
	struct treeNode* rchild;
}biTNode,*biTree;

/****************************************************************************
*  Declaration
*****************************************************************************/

void createBiTree(biTree *T);
int getTreeDepth(biTree T);
int getLeafNodeNum(biTree T);
int getNodeNum(biTree T);
void preOrderTraverse(biTree T);
void inOrderTraverse(biTree T);
void postOrderTraverse(biTree T);
void printByLevel(biTree T,int level);
void levelOrderTraverse(biTree T);
void exchangeChildTree(biTree T);
biTree findNode(biTree T,elemType_t e);
void destroyTree(biTree T);
void biTreeTest(void);

/****************************************************************************
*  Function 
*****************************************************************************/

void createBiTree(biTree *T)
{
	elemType_t data;
	scanf("%d",&data);
	if(data == -1){
		*T = NULL;
	}else{
		*T = (biTree)malloc(sizeof(biTNode));
        (*T)->element = data;
        printf("please input the left child of %d：", data);
        createBiTree(&((*T)->lchild));
        printf("plese input the right child of %d：", data);
        createBiTree(&((*T)->rchild));
	}
}

int getTreeDepth(biTree T)
{
	int depth = 0;
	if(T){
		int leftDepth = getTreeDepth(T->lchild);
		int rightDepth = getTreeDepth(T->rchild);
		depth = leftDepth >rightDepth? leftDepth+1 : rightDepth+1;
	}
	return depth;
}

int getLeafNodeNum(biTree T)
{
	if(T){
		if(T->lchild == NULL && T->rchild == NULL){
			return 1;
		}else if(T->lchild != NULL && T->rchild == NULL){
			return getLeafNodeNum(T->lchild);
		}else if(T->lchild == NULL && T->rchild != NULL){
			return getLeafNodeNum(T->rchild);
		}else{
			return getLeafNodeNum(T->lchild) + getLeafNodeNum(T->rchild);
		}
	}
	return 0;
}

int getNodeNum(biTree T)
{
	if(!T)
		return 0;
	return getNodeNum(T->lchild) + getNodeNum(T->rchild) + 1;
}

void preOrderTraverse(biTree T)
{
	if(T != NULL){
		printf("%d\n",T->element);
		preOrderTraverse(T->lchild);
		preOrderTraverse(T->rchild);
	}
}

void inOrderTraverse(biTree T)
{
	if(T != NULL){
		inOrderTraverse(T->lchild);
		printf("%d\n",T->element);
		inOrderTraverse(T->rchild);
	}
}

void postOrderTraverse(biTree T)
{
	if(T != NULL){
		postOrderTraverse(T->lchild);
		postOrderTraverse(T->rchild);
		printf("%d\n",T->element);
	}
}

void printByLevel(biTree T,int level)
{
	if(T != NULL && level>=0){
		if(level == 0){
			printf("%d\n",T->element);
		}else{
			printByLevel(T->lchild,level-1);
			printByLevel(T->rchild,level-1);
		}
	}
}

void levelOrderTraverse(biTree T)
{
	int depth;
	if(T != NULL){
		depth = getTreeDepth(T);
		for(int i=0;i<depth;i++){
			printByLevel(T,i);
		}
	}
}

void exchangeChildTree(biTree T)
{
	if(T){
		biTree temp = NULL;
		if(T->lchild || T->rchild){
			exchangeChildTree(T->lchild);
			exchangeChildTree(T->rchild);
			temp = T->lchild;
			T->lchild = T->rchild;
			T->rchild = temp;
		}
	}
}

biTree findNode(biTree T,elemType_t e)
{
	if(T == NULL)
		return NULL;
	if(T->element == e){
		return T;
	}else{
		biTree p;
		if(p = findNode(T->lchild,e))
			return p;
		if(p = findNode(T->rchild,e))
			return p;
		return NULL;
	}
	
}

void destroyTree(biTree T)
{
	if(T == NULL)
		return;
	destroyTree(T->lchild);
	destroyTree(T->rchild);
	free(T);
	T = NULL;
}

void biTreeTest(void)
{
	elemType_t nodeVal;
	biTree myTree;
	printf("please input the value of root node\n");
	createBiTree(&myTree);
	printf("preOrder\n");
	preOrderTraverse(myTree);
	printf("inOrder\n");
	inOrderTraverse(myTree);
	printf("postOrder\n");
	postOrderTraverse(myTree);
	printf("levelOrder\n");
	levelOrderTraverse(myTree);
/*	printf("exchange child of biTree\n");
	exchangeChildTree(myTree);
	printf("level order after exchange\n");
	levelOrder(myTree);
*/	printf("depth of biTree:%d\n",getTreeDepth(myTree));
	printf("num of nodes:%d\n",getNodeNum(myTree));
	printf("num of leaf nodes:%d\n",getLeafNodeNum(myTree));
	printf("please input the value of node you want to find:\n");
	scanf("%d",&nodeVal);
	printf("levelOrder of the node\n");
	levelOrderTraverse(findNode(myTree,nodeVal));
	destroyTree(myTree);
}

int main(void)
{
	biTreeTest();
	for(;;);
	return 0;
}