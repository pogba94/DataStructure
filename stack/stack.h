#ifndef _STACK_H
#define _STACK_H

#ifdef __cplusplus
extern "C"{
#endif

/****************************************************************************
*  Typde definnition
*****************************************************************************/

typedef int ElemType_t;
typedef struct stack
{
	ElemType_t *base;
	ElemType_t *top;
	int stackSize; 
}Stack;
typedef int statu_t;

/****************************************************************************
*  Declaration
*****************************************************************************/

statu_t StackInit(Stack *stack);
statu_t StackDestroy(Stack **pStack);
statu_t StackClear(Stack *stack);
statu_t StackGetLen(Stack *stack);
statu_t StackIsEmpty(Stack *stack);
statu_t StackGetTop(Stack *stack,ElemType_t *e);
statu_t StackPush(Stack *stack,ElemType_t *e);
statu_t StackPop(Stack *stack,ElemType_t *e);
statu_t StackTraverse(Stack *stack);
void StackDemo(void);


#ifdef __cplusplus
}
#endif

#endif