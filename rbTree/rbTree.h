#ifndef _RB_TREE_H
#define _RB_TREE_H

#ifdef __cplusplus
extern "C"{
#endif

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

/****************************************************************************
*  Declaration
*****************************************************************************/
pRBTNode RBTreeInsert(RBTree *pT,ElemType_t e);
void RBTreeInOrderTraverse(RBTree T);
pRBTNode RBTreeFind(RBTree T,ElemType_t e);
pRBTNode RBTreeFindMax(RBTree T);
pRBTNode RBTreeFindMin(RBTree T);
int RBTreeDelete(RBTree *pT,ElemType_t e);
int RBTreeDepth(RBTree T);
int RBTreeSize(RBTree T);
void printRBTree(RBTree T);
void RBTreeDemo(void);

#ifdef __cplusplus
}
#endif

#endif