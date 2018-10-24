#include "stdio.h"
#include "stdlib.h"

#define QUEUE_MAX_SIZE     (5)

typedef int ElemType_t;
typedef struct Queue{
	ElemType_t data[QUEUE_MAX_SIZE];
	int front;
	int rear;
	int counter;
}Queue;
typedef int statu_t;

#define INDICATE_INFO "Queue haven't been created,please create firstly"

Queue* QueueCreat(void)
{
	Queue *queue;
	queue = (Queue*)malloc(sizeof(Queue));
	return queue==NULL?NULL:queue;
}

void QueueInit(Queue *queue)
{
	if(queue != NULL){
		queue->front = queue->rear = queue->counter = 0;
	}	
}

statu_t QueueIsEmpty(Queue *queue)
{
	if(queue == NULL)
		return -1;
	return (queue->counter == 0);
}

statu_t QueueIsFull(Queue *queue)
{
	if(queue == NULL)
		return -1;
	return (queue->counter == QUEUE_MAX_SIZE);
}

statu_t QueuePush(Queue *queue,ElemType_t e)
{
	if(queue == NULL)
		return -1;
	if(QueueIsFull(queue))
		return -2;
	queue->data[queue->rear] = e;
	queue->rear++;
	queue->rear %= QUEUE_MAX_SIZE;
	queue->counter++;
	return 0;
}

statu_t QueuePushMult(Queue *queue,ElemType_t *arr,int n)
{
	int i = 0;
	if(queue == NULL)
		return -1;
	while(!QueueIsFull(queue) && i<n){
		QueuePush(queue,arr[i++]);
	}
	return i;
}

statu_t QueuePop(Queue *queue,ElemType_t *e)
{
	if(queue == NULL)
		return -1;
	if(QueueIsEmpty(queue))
		return -2;
	*e = queue->data[queue->front];
	queue->front++;
	queue->front %= QUEUE_MAX_SIZE;
	queue->counter--;
	return 0;
}

statu_t QueuePopMult(Queue *queue,ElemType_t *arr,int n)
{
	int i = 0;
	if(queue == NULL)
		return -1;
	while(!QueueIsEmpty(queue) && i<n){
		QueuePop(queue,arr+i);
		i++;
	}
	return i;
}

statu_t  QueueFront(Queue *queue,ElemType_t *e)
{
	if(queue == NULL)
		return -1;
	if(QueueIsEmpty(queue))
		return -2;
	*e = queue->data[queue->front];
	return 0;
}

statu_t QueueBack(Queue *queue,ElemType_t *e)
{
	if(queue == NULL)
		return -1;
	if(QueueIsEmpty(queue))
		return -2;
	*e = (queue->rear == 0) ? queue->data[QUEUE_MAX_SIZE-1] : queue->data[queue->rear-1];
	return 0;
}

statu_t QueueGetSize(Queue *queue,int *size)
{
	if(queue == NULL)
		return -1;
	*size = queue->counter;
	return 0;
}

void QueueTraverse(Queue *queue)
{
	if(queue != NULL && !QueueIsEmpty(queue)){
		int p = queue->front;
		int n = 0;
		while(n < queue->counter){
			if(n % 10 == 0)
				printf("\n");
			printf("%d\t",queue->data[p]);
			p++;
			p %= QUEUE_MAX_SIZE;
			n++;
		}
		printf("\n\n");
	}
}

void displayMenu(void)
{
	printf("-----------------------Menu--------------------------\n");
	printf("-      1.  create queue        2.  get size         -\n");
	printf("-      3.  push                4.  pop              -\n");
	printf("-      5.  check empty         6.  check full       -\n");
	printf("-      7.  get front           8.  get rear         -\n");
	printf("-      9.  traverse queue      10. show menu        -\n");
	printf("-      11. mult push           12. mult pop         -\n");
	printf("-----------------------------------------------------\n\n");
}

void queueDemo(void)
{
	int tmp;
	Queue *myQueue = NULL;
	statu_t status;

	displayMenu();
	while(1){
		printf("\nplease choose which action to do:");
		scanf("%d",&tmp);
		printf("\n");
		switch(tmp){
			case 1:
			{
				if(myQueue != NULL){
					printf("Queue exsits\n");
					break;
				}
				myQueue = QueueCreat();
				QueueInit(myQueue);
				if(myQueue == NULL){
					printf("create Queue failed\n");
				}else{
					printf("create Queue success\n");
				}
				break;
			}
			case 2:
			{
				if(myQueue == NULL){
					printf("%s\n",INDICATE_INFO);
				}else{
					int size;
					QueueGetSize(myQueue,&size);
					printf("size of queue:%d\n",size);
				}
				break;
			}
			case 3:
			{
				if(myQueue == NULL){
					printf("%s\n",INDICATE_INFO);
				}else{
					printf("please input the value of item to be pushed:");
					scanf("%d",&tmp);
					printf("\n");
					status = QueuePush(myQueue,tmp);
					if(status){
						printf("push failed\n");
					}else{
						printf("push success\n");
					}
				}
				break;
			}
			case 4:
			{
				if(myQueue == NULL){
					printf("%s\n",INDICATE_INFO);
				}else{
					ElemType_t e;
					status = QueuePop(myQueue,&e);
					if(status){
						printf("pop failed\n");
					}else{
						printf("element %d had been pop\n",e);
					}
				}
				break;
			}
			case 5:
			{
				if(myQueue == NULL){
					printf("%s\n",INDICATE_INFO);
				}else{
					status = QueueIsEmpty(myQueue);
					if(status){
						printf("queue is empty\n");
					}else{
						printf("queue is not empty\n");
					}
				}
				break;
			}
			case 6:
			{
				if(myQueue == NULL){
					printf("%s\n",INDICATE_INFO);
				}else{
					status = QueueIsFull(myQueue);
					if(status){
						printf("queue is full\n");
					}else{
						printf("queue is not full\n");
					}
				}
				break;
			}
			case 7:
			{
				if(myQueue == NULL){
					printf("%s\n",INDICATE_INFO);
				}else{
					ElemType_t e;
					status = QueueFront(myQueue,&e);
					if(!status){
						printf("front element is : %d\n",e);
					}else{
						printf("get front element failed\n");
					}
				}
				break;
			}
			case 8:
			{
				if(myQueue == NULL){
					printf("%s\n",INDICATE_INFO);
				}else{
					ElemType_t e;
					status = QueueBack(myQueue,&e);
					if(!status){
						printf("back element is : %d\n",e);
					}else{
						printf("get back element failed\n");
					}
				}
				break;
			}
			case 9:
			{
				if(myQueue == NULL){
					printf("%s\n",INDICATE_INFO);
				}else{
					QueueTraverse(myQueue);
				}
				break;
			}
			case 10:
			{
				displayMenu();
				break;
			}
			case 11:
			{
				if(myQueue == NULL){
					printf("%s\n",INDICATE_INFO);
				}else{
					int num,i;
					ElemType_t *data;
					printf("please input the size:");
					scanf("%d",&num);
					if(num <= 0)
						break;
					data = (ElemType_t*)malloc(sizeof(ElemType_t)*num);
					if(data == NULL){
						printf("malloc failed\n");
					}
					for(i=0;i<num;i++){
						printf("please input the %d Th data:",i);
						scanf("%d",data+i);
					}
					status = QueuePushMult(myQueue,data,num);
					if(status>0){
						printf("push %d elements success\n",status);
					}else{
						printf("push failed\n");
					}
					free(data);
				}
				break;
			}
			case 12:
			{
				if(myQueue == NULL){
					printf("%s\n",INDICATE_INFO);
				}else{
					int num,i;
					ElemType_t *data;
					printf("please input the size:");
					scanf("%d",&num);
					if(num <= 0)
						break;
					data = (ElemType_t*)malloc(sizeof(ElemType_t)*num);
					if(data == NULL){
						printf("malloc failed\n");
					}
					status = QueuePopMult(myQueue,data,num);
					if(status>0){
						printf("pop %d elements success\n",status);
						for(i=0;i<status;i++){
							if(i%10 == 0)
								printf("\n");
							printf("%d\t",*(data+i));
						}
					}else{
						printf("pop failed\n");
					}
					free(data);
				}
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
	queueDemo();
	for(;;);
}