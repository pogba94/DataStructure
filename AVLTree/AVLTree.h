#ifndef _AVL_TREE_H
#define _AVL_TREE_H

#ifdef __cplusplus
extern "C"{
#endif

/****************************************************************************
*  Typde definnition
*****************************************************************************/

typedef int ElemType_t;
typedef enum{
	EH = 0,
	LH = 1,
	RH = -1,
}BF_t;

typedef struct AVLTNode{
	ElemType_t key;
	int bf;
	struct AVLTNode* lchild;
	struct AVLTNode* rchild;
}AVLTNode,*pAVLTNode;
typedef pAVLTNode AVLTree;
typedef bool statu_t;

/****************************************************************************
*  Declaration
*****************************************************************************/

static void leftRotate(AVLTree *pT);
static void rightRotate(AVLTree *pT);
static void leftBanlance(AVLTree *pT);
static void rightBanlance(AVLTree *pT);
statu_t AVLTreeInsert(AVLTree *pT,ElemType_t e,bool *taller);
statu_t AVLTreeDelete(AVLTree *pT,ElemType_t e,bool *lower);
void AVLTreeInOrderTraverse(AVLTree T);
pAVLTNode AVLTreeFind(AVLTree T,ElemType_t e);
pAVLTNode AVLTreeFindMax(AVLTree T);
pAVLTNode AVLTreeFindMin(AVLTree T);
int AVLTreeDepth(AVLTree T);
int AVLTreeSize(AVLTree T);
void printAVLTree(AVLTree T);
static void displayMenu(void);
void AVLTreeDemo(void);


#ifdef __cplusplus
}
#endif

#endif