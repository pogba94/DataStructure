#ifndef _BINARY_SORT_TREE_H
#define _BINARY_SORT_TREE_H

#ifdef __cplusplus
extern "C"{
#endif

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

#ifdef __cplusplus
}
#endif

#endif