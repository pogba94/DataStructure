#ifndef _QUEUE_H
#define _QUEUE_H

#ifdef __cplusplus
extern "C"{
#endif

/****************************************************************************
*  Macro definition
*****************************************************************************/

#define QUEUE_MAX_SIZE     (5)

/****************************************************************************
*  Typde definnition
*****************************************************************************/

typedef int ElemType_t;
typedef struct Queue{
	ElemType_t data[QUEUE_MAX_SIZE];
	int front;
	int rear;
	int counter;
}Queue;
typedef int statu_t;

/****************************************************************************
*  Declaration
*****************************************************************************/

Queue* QueueCreate(void);
void QueueInit(Queue *queue);
statu_t QueueIsEmpty(Queue *queue);
statu_t QueueIsFull(Queue *queue);
statu_t QueuePush(Queue *queue,ElemType_t e);
statu_t QueuePushMult(Queue *queue,ElemType_t *arr,int n);
statu_t QueuePop(Queue *queue,ElemType_t *e);
statu_t QueuePopMult(Queue *queue,ElemType_t *arr,int n);
statu_t QueueFront(Queue *queue,ElemType_t *e);
statu_t QueueBack(Queue *queue,ElemType_t *e);
statu_t QueueGetSize(Queue *queue,int *size);
void QueueTraverse(Queue *queue);
void queueDemo(void);

#ifdef __cplusplus
}
#endif

#endif