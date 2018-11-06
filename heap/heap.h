#ifndef _HEAP_H
#define _HEAP_H

#ifdef __cplusplus
extern "C"{
#endif

/****************************************************************************
*  Type definition
*****************************************************************************/

typedef int ElemType_t;
typedef enum heapType{
	BIG_TOP = 0,
	SMALL_TOP = 1,
}heapType;

typedef struct BHeap
{
	ElemType_t *data;
	int capacity;
	int size;
	heapType type;
}BHeap,*pBHeap;

typedef int statu_t;

/****************************************************************************
*  Declaration
*****************************************************************************/

pBHeap createBHeap(void);
void destroyBHeap(pBHeap *pheap);
statu_t BHeapIsFull(pBHeap heap);
statu_t BHeapIsEmpty(pBHeap heap);
statu_t BHeapPush(pBHeap heap,ElemType_t e);
statu_t BHeapPop(pBHeap heap,ElemType_t *e);
void BHeapBuild(ElemType_t* arr,int size,heapType type);
int BHeapSize(pBHeap heap);
int BHeapCapacity(pBHeap heap);
void BHeapPrint(pBHeap heap);
void BHeapSortPrint(pBHeap heap);
void BHeapDemo(void);

#ifdef __cplusplus
}
#endif

#endif