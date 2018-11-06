/****************************************************************************
*  Includes
*****************************************************************************/

#include "heap.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"

/****************************************************************************
*  Macro definition
*****************************************************************************/

#define HEAP_INIT_SIZE (20)
#define HEAP_INC_SIZE  (10)
#define HEAP_TYPE_DEFAULT   SMALL_TOP
#define INDICATE_INFO "heap haven't been created,please create list firstly"

pBHeap createBHeap(void)
{
	pBHeap newBHeap = (pBHeap)malloc(sizeof(BHeap));
	if(newBHeap == NULL)
		return NULL;
	newBHeap->data = (ElemType_t*)malloc(sizeof(ElemType_t)*HEAP_INIT_SIZE);
	if(newBHeap->data == NULL)
		return NULL;
	memset(newBHeap->data,0x0,sizeof(ElemType_t)*HEAP_INIT_SIZE);
	newBHeap->capacity = HEAP_INIT_SIZE;
	newBHeap->size = 0;
	newBHeap->type = HEAP_TYPE_DEFAULT;
	return newBHeap;
}

void destroyBHeap(pBHeap *pheap)
{
	if(pheap != NULL && *pheap != NULL){
		free((*pheap)->data);
		free((*pheap));
		*pheap = NULL;
	}
}

statu_t BHeapIsFull(pBHeap heap)
{
	if(heap == NULL)
		return -1;
	return heap->size == heap->capacity;
}

statu_t BHeapIsEmpty(pBHeap heap)
{
	if(heap == NULL)
		return -1;
	return heap->size == 0;
}

static void swap(ElemType_t *a,ElemType_t *b)
{
	ElemType_t tmp = *a;
	*a = *b;
	*b = tmp;
}

static void BHeapAdjustUp(ElemType_t *arr,int x,heapType type)
{
	if(arr != NULL){
		for(int i=(x-1)/2;i>=0;i = (i-1)/2){
			if((type == BIG_TOP && arr[i]<arr[x]) || (type == SMALL_TOP && arr[i]>arr[x])){
				swap(arr+i,arr+x);
				x = i;
			}else{
				break;
			}
		}
	}
}

static void BHeapAdjustDown(ElemType_t *arr,int root,int size,heapType type)
{
	if(arr != NULL && size > 0 && root >=0){
		for(int i=root*2+1;i<size;i=2*i+1){
			if(type == BIG_TOP){
				if(i+1<size && arr[i+1]>arr[i]){
					i++;
				}
				if(arr[i]<=arr[(i-1)/2])
					break;
				else{
					swap(arr+i,arr+(i-1)/2);
				}
			}else if(type == SMALL_TOP){
				if(i+1<size && arr[i+1]<arr[i]){
					i++;
				}
				if(arr[i]>=arr[(i-1)/2])
					break;
				else{
					swap(arr+i,arr+(i-1)/2);
				}
			}
		}
	}
}

statu_t BHeapPush(pBHeap heap,ElemType_t e)
{
	if(heap == NULL)
		return -1;
	if(BHeapIsFull(heap)){
		ElemType_t *p;
		p = (ElemType_t*)realloc(heap->data,(heap->capacity+HEAP_INC_SIZE)*sizeof(ElemType_t));
		if(p == NULL)
			return -2;
		heap->data = p;
		heap->capacity += HEAP_INC_SIZE;
	}
	heap->data[heap->size] = e;
	heap->size++;
	BHeapAdjustUp(heap->data,heap->size-1,heap->type);
	return 0;
}

statu_t BHeapPop(pBHeap heap,ElemType_t *e)
{
	if(heap == NULL || e == NULL)
		return -1;
	if(heap->size == 0)
		return -2;
	*e = heap->data[0];
	heap->data[0] = heap->data[--heap->size];
	BHeapAdjustDown(heap->data,0,heap->size,heap->type);
	return 0;
}

void BHeapBuild(ElemType_t* arr,int size,heapType type)
{
	if(arr != NULL && size > 0){
		for(int i=(size-2)/2;i>=0;i--){
			BHeapAdjustDown(arr,i,size,type);
		}
	}
}

int BHeapSize(pBHeap heap)
{
	return (heap==NULL) ? -1 : heap->size;
}

int BHeapCapacity(pBHeap heap)
{
	return (heap==NULL) ? -1 : heap->capacity;
}

 
void BHeapPrint(pBHeap heap)
{
	if(heap != NULL){
		for (int i = 0; i < heap->size; ++i)
		{
			if(i % 10 == 0)
				printf("\n");
			printf("%d\t",heap->data[i]);
		}
	}
}

void BHeapSortPrint(pBHeap heap)
{
	if(heap != NULL && heap->size > 0){
		ElemType_t *buffer = (ElemType_t*)malloc(sizeof(ElemType_t)*heap->size);
		int size = heap->size;
		ElemType_t e;
		if(buffer == NULL)
			return;
		memcpy(buffer,heap->data,sizeof(ElemType_t)*size);
		for(int i=0;i<size;i++){
			BHeapPop(heap,&e);
			if(i % 10 == 0)
				printf("\n");
			printf("%d\t",e);
		}
		memcpy(heap->data,buffer,sizeof(ElemType_t)*size);
		heap->size = size;
		free(buffer);
	}
}

static void displayMenu(void)
{
	printf("-----------------------Menu--------------------------\n");
	printf("-      1.  create heap         2.  push             -\n");
	printf("-      3.  pop                 4.  get size         -\n");
	printf("-      5.  get capacity        6.  print heap       -\n");
	printf("-      7.  show menu           8.  get top          -\n");
	printf("-      9.  random push         10. convert          -\n");
	printf("-      11. sort print          12. destroy heap     -\n");
	printf("-----------------------------------------------------\n\n");
}

static void safeFlush(FILE *fp)
{
	int ch;
	while((ch = fgetc(fp)) != EOF && ch != '\n');
}

void BHeapDemo(void)
{
	int cmdId;
	ElemType_t element;
	pBHeap myBHeap = NULL;

	displayMenu();
	while(1){
		cmdId = -1;
		safeFlush(stdin);
		printf("\nplease choose action to do:");
		scanf("%d",&cmdId);
		printf("\n");
		switch(cmdId){
			case 1:
			{
				if(myBHeap != NULL)
					printf("heap exsits\n");
				else{
					myBHeap = createBHeap();
					if(myBHeap == NULL)
						break;
					printf("create heap successfully\n");
				}
				break;
			}
			case 2:
			{
				if(myBHeap == NULL){
					printf("%s\n",INDICATE_INFO);
				}else{
					printf("please input the element you want to push:");
					scanf("%d",&element);
					if(!BHeapPush(myBHeap,element))
						printf("push element %d successfully\n",element);
				}
				break;
			}
			case 3:
			{
				if(myBHeap == NULL){
					printf("%s\n",INDICATE_INFO);
				}else{
					if(!BHeapPop(myBHeap,&element))
						printf("pop %d successfully\n",element);
				}
				break;
			}
			case 4:
			{
				if(myBHeap == NULL){
					printf("%s\n",INDICATE_INFO);
				}else{
					printf("size of heap : %d\n", BHeapSize(myBHeap));	
				}
				break;
			}
			case 5:
			{
				if(myBHeap == NULL){
					printf("%s\n",INDICATE_INFO);
				}else{
					printf("capacity of heap : %d\n", BHeapCapacity(myBHeap));	
				}
				break;
			}
			case 6:
			{
				if(myBHeap == NULL){
					printf("%s\n",INDICATE_INFO);
				}else{
					printf("heap traverse:\n");
					BHeapPrint(myBHeap);	
				}
				break;
			}
			case 7:
			{
				displayMenu();
				break;
			}
			case 8:
			{
				if(myBHeap == NULL){
					printf("%s\n",INDICATE_INFO);
				}else{
					if(myBHeap->size > 0)
						printf("top of heap : %d\n",myBHeap->data[0]);	
				}
				break;
			}
			case 9:
			{
				ElemType_t min,max,mod,*dataSet;
				int num;
				printf("please input min val of data set:");
				scanf("%d",&min);
				printf("please input max val of data set:");
				scanf("%d",&max);
				printf("please input the size of data set:");
				scanf("%d",&num);
				if(min>max || num <=0){
					printf("illegal parameters\n");
					break;
				}
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
				for(int i=0;i<num;i++)
					BHeapPush(myBHeap,dataSet[i]);
				free(dataSet);
				break;
			}
			case 10:
			{
				myBHeap->type = (myBHeap->type == BIG_TOP) ? SMALL_TOP : BIG_TOP;
				BHeapBuild(myBHeap->data,myBHeap->size,myBHeap->type);
				printf("convert successfully\n");
				break;
			}
			case 11:
			{
				printf("print after sort:\n");
				BHeapSortPrint(myBHeap);
				break;
			}
			case 12:
			{
				printf("destroy heap\n");
				destroyBHeap(&myBHeap);
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

int main(void)
{
	BHeapDemo();
	for(;;);
	return 0;
}
