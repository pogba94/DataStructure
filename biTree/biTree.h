#ifndef _BITREE_H
#define _BITREE_H

#ifdef __cplusplus
extern "C"{
#endif

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


#ifdef __cplusplus
}
#endif

#endif