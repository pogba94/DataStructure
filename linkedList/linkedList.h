#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

#ifdef __cplusplus
extern "C"{
#endif

/****************************************************************************
*  Typde definnition
*****************************************************************************/

typedef int elemType_t;
typedef int statu_t;

typedef struct listNode
{
	elemType_t data;
	struct listNode *next;
}listNode,*pListNode;

typedef pListNode List;

/****************************************************************************
*  Declaration
*****************************************************************************/

List ListCreate(void);
statu_t ListIsEmpty(List list);
statu_t ListInsertItem(List list,int pos,elemType_t val);
statu_t ListInsertItemTail(List list,elemType_t val);
statu_t ListTraverse(List list);
statu_t ListDestroy(List *list); 
int ListGetLen(List list);
pListNode ListFindItem(List list,elemType_t val);
statu_t ListDeleteItem(List list,elemType_t val);
void ListDemo(void);
void ListTest(void);

#ifdef __cplusplus
}
#endif

#endif

