/****************************************************************************
*  Includes
*****************************************************************************/

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "AVLTree.h"

/****************************************************************************
*  Functions
*****************************************************************************/

static void leftRotate(AVLTree *pT)
{
	pAVLTNode rc = (*pT)->rchild;
	(*pT)->rchild = rc->lchild;
	rc->lchild = *pT;
	*pT = rc;
}

static void rightRotate(AVLTree *pT)
{
	pAVLTNode lc = (*pT)->lchild;
	(*pT)->lchild = lc->rchild;
	lc->rchild = *pT;
	*pT = lc;
}


static void leftBanlance(AVLTree *pT)
{
	if(pT != NULL && *pT != NULL){
		pAVLTNode lc = (*pT)->lchild;
		pAVLTNode rd = lc->rchild;
		switch(lc->bf){
			case LH:
				(*pT)->bf = lc->bf = EH;
				rightRotate(pT);
				return;
			case RH:
				switch(rd->bf){
					case LH:
						(*pT)->bf = RH;
						lc->bf = EH;
						break;
					case EH:
						(*pT)->bf = EH;
						lc->bf = EH;
						break;
					case RH:
						(*pT)->bf = EH;
						lc->bf = LH;
						break;
				}
				rd->bf = EH;
				leftRotate(&((*pT)->lchild));
				rightRotate(pT);
				break;
		}
	}
	printf("left balance\n");
}

static void rightBanlance(AVLTree *pT)
{
	if(pT != NULL && (*pT) != NULL){
		pAVLTNode rc = (*pT)->rchild;
		pAVLTNode ld = rc->lchild;
		switch(rc->bf){
			case RH:
				(*pT)->bf = rc->bf = EH;
				leftRotate(pT);
				break;
			case LH:
				switch(ld->bf){
					case LH:
						(*pT)->bf = EH;
						rc->bf = RH;
						break;
					case EH:
						(*pT)->bf = rc->bf = EH;
						break;
					case RH:
						(*pT)->bf = LH;
						rc->bf = EH;
						break;
				}
				ld->bf = EH;
				rightRotate(&((*pT)->rchild));
				leftRotate(pT);
				break;
		}
	}
	printf("right balance\n");
}

statu_t AVLTreeInsert(AVLTree *pT,ElemType_t e,bool *taller)
{
	if(pT == NULL)
		return false;
	if((*pT) == NULL){
		pAVLTNode pNode = (pAVLTNode)malloc(sizeof(AVLTNode));
		if(pNode == NULL)
			return false;
		pNode->lchild = pNode->rchild = NULL;
		pNode->key = e;
		pNode->bf = EH;
		*taller = true;
		*pT = pNode;
	}else{
		if((*pT)->key == e){
			return false;
		}else if((*pT)->key > e){
			if(AVLTreeInsert(&((*pT)->lchild),e,taller) == false)
				return false;
			if(*taller){
				switch((*pT)->bf){
					case LH:
						leftBanlance(pT);
						*taller = false;
						break;
					case EH:
						*taller = true;
						(*pT)->bf = LH;
						break;
					case RH:
						*taller = false;
						(*pT)->bf = EH;
						break;
				}
			}
		}else{
			if(AVLTreeInsert(&((*pT)->rchild),e,taller) == false)
				return false;
			if(*taller){
				switch((*pT)->bf){
					case LH:
						*taller = false;
						(*pT)->bf = EH;
						break;
					case EH:
						*taller = true;
						(*pT)->bf = RH;
						break;
					case RH:
						rightBanlance(pT);
						*taller = false;
						break;
				}
			}
		}
	}
	return true;
}

statu_t AVLTreeDelete(AVLTree *pT,ElemType_t e,bool *lower)
{
	if(pT == NULL || (*pT) == NULL)
		return false;
	if((*pT)->key > e){
		if(AVLTreeDelete(&((*pT)->lchild),e,lower) == false)
			return false;
		if(*lower){
			switch((*pT)->bf){
				case LH:
					(*pT)->bf = EH;
					*lower = true;
					break;
				case EH:
					(*pT)->bf = RH;
					*lower = false;
					break;
				case RH:
					rightBanlance(pT);
					*lower = true;
					break;
			}
		}
	}else if((*pT)->key < e){
		if(AVLTreeDelete(&((*pT)->rchild),e,lower) == false)
			return false;
		if(*lower){
			switch((*pT)->bf){
				case LH:
					*lower = true;
					leftBanlance(pT);
					break;
				case EH:
					*lower = false;
					(*pT)->bf = LH;
					break;
				case RH:
					*lower = true;
					(*pT)->bf = EH;
					break;
			}
		}
	}else{
		if((*pT)->lchild != NULL && (*pT)->rchild != NULL){
			pAVLTNode pNode = AVLTreeFindMin((*pT)->rchild);
			(*pT)->key = pNode->key;
			AVLTreeDelete(&((*pT)->rchild),pNode->key,lower);   //take care! not delete e
			if(*lower){
				switch((*pT)->bf){
					case LH:
						*lower = true;
						leftBanlance(pT);
						break;
					case EH:
						*lower = false;
						(*pT)->bf = LH;
						break;
					case RH:
						*lower = true;
						(*pT)->bf = EH;
						break;
				}
			}
		}else{
			pAVLTNode tmp = *pT;
			if((*pT)->lchild){
				*pT = (*pT)->lchild;
			}else if((*pT)->rchild){
				*pT = (*pT)->rchild;
			}else{
				*pT = NULL;
			}
			*lower = true;
			free(tmp);
			tmp = NULL;
		}
	}
	return true;
}

void AVLTreeInOrderTraverse(AVLTree T)
{
	if(T != NULL){
		AVLTreeInOrderTraverse(T->lchild);
		printf("%d\n",T->key);
		AVLTreeInOrderTraverse(T->rchild);
	}
}

pAVLTNode AVLTreeFind(AVLTree T,ElemType_t e)
{
	if(T == NULL)
		return NULL;
	if(T->key == e){
		return T;
	}else if(T->key > e){
		return AVLTreeFind(T->lchild,e);
	}else{
		return AVLTreeFind(T->rchild,e);
	}
}

pAVLTNode AVLTreeFindMax(AVLTree T)
{
	if(T == NULL)
		return NULL;
	if(T->rchild == NULL)
		return T;
	return AVLTreeFindMax(T->rchild);
}

pAVLTNode AVLTreeFindMin(AVLTree T)
{
	if(T == NULL)
		return NULL;
	if(T->lchild == NULL)
		return T;
	return AVLTreeFindMin(T->lchild);
}

int AVLTreeDepth(AVLTree T)
{
	int depth = 0;
	if(T != NULL){
		int leftDepth = AVLTreeDepth(T->lchild);
		int rightDepth = AVLTreeDepth(T->rchild);
		depth = (leftDepth>rightDepth) ? leftDepth+1 : rightDepth+1;
	}
	return depth; 
}

int AVLTreeSize(AVLTree T)
{
	if(T != NULL){
		return 1 + AVLTreeSize(T->lchild) + AVLTreeSize(T->rchild);
	}
	return 0;
}

void printAVLTree(AVLTree T)
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
		printAVLTree(T->lchild);
		printAVLTree(T->rchild);
	}
}

static void displayMenu(void)
{
	printf("-----------------------Menu-------------------------\n");
	printf("-      1. insert item         2.  delete item      -\n");
	printf("-      3. find item           4.  get size         -\n");
	printf("-      5. find max            6.  find min         -\n");
	printf("-      7. get depth           8.  traverse tree    -\n");
	printf("-      9. show menu           10. printTree        -\n");
	printf("----------------------------------------------------\n\n");
}

void AVLTreeDemo(void)
{
	int tmp;
	ElemType_t element;
	AVLTree myAVLTree = NULL;

	displayMenu();
	while(1){
		printf("\nplease choose action to do:");
		scanf("%d",&tmp);
		printf("\n");
		switch(tmp){
			case 1:
			{
				bool taller;	
				printf("please input the element you want to insert:");
				scanf("%d",&element);
				printf("\n");
				if(AVLTreeInsert(&myAVLTree,element,&taller))
					printf("element %d had been inserted\n",element);
				break;
			}
			case 2:
			{
				bool lower;
				printf("please input the element you want to delete:");
				scanf("%d",&element);
				printf("\n");
				if (AVLTreeDelete(&myAVLTree,element,&lower))
					printf("element %d had been deleted\n",element);
				break;
			}
			case 3:
			{
				printf("please input the element you want to find:");
				scanf("%d",&element);
				printf("\n");
				if(!AVLTreeFind(myAVLTree,element)){
					printf("not found\n");
				}else{
					printf("found\n");
				}
				break;
			}
			case 4:
			{
				printf("size of AVLTree:%d\n",AVLTreeSize(myAVLTree));
				break;
			}
			case 5:
			{
				pAVLTNode pTmpNode =  AVLTreeFindMax(myAVLTree);
				if(!pTmpNode){
					printf("no element\n");
				}else{
					printf("max element:%d\n",pTmpNode->key);
				}
				break;
			}
			case 6:
			{
				pAVLTNode pTmpNode = AVLTreeFindMin(myAVLTree);
				if(!pTmpNode){
					printf("no element\n");
				}else{
					printf("min element:%d\n",pTmpNode->key);
				}
				break;
			}
			case 7:
			{
				printf("Depth of AVLTree:%d\n",AVLTreeDepth(myAVLTree));
				break;
			}
			case 8:
			{
				printf("traverse AVLTree:\n");
				AVLTreeInOrderTraverse(myAVLTree);	
				break;
			}
			case 9:
			{
				displayMenu();
				break;
			}
			case 10:
			{
				printAVLTree(myAVLTree);
				break;
			}
			default:
			printf("illegal cmd\n");
			break;
		}
	}
}



int main(void)
{
	AVLTreeDemo();
	for(;;);
	return 0;
}