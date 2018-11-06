/****************************************************************************
*  Includes
*****************************************************************************/

#include "stdio.h"
#include "stdlib.h"
#include "stack.h"

/****************************************************************************
*  Macro definition
*****************************************************************************/

#define STACK_INIT_SIZE    (10)
#define STACK_INC_SIZE     (5)

/****************************************************************************
*  Functions
*****************************************************************************/

statu_t StackInit(Stack *stack)
{
	ElemType_t *data;
	
	if(stack == NULL)
		return -1;
	data = (ElemType_t*)malloc(sizeof(ElemType_t) * STACK_INIT_SIZE);
	if(data == NULL)
		return -2;
	stack->base = data;
	stack->top = data;
	stack->stackSize = STACK_INIT_SIZE;
	return 0;
}

statu_t StackDestroy(Stack **pStack)
{
	if(pStack == NULL)
		return -1;
	free((*pStack)->base);
	free(*pStack);
	*pStack = NULL;
	return 0;
}

statu_t StackClear(Stack *stack)
{
	if(stack == NULL)
		return -1;
	stack->top = stack->base;
	return 0;
}

statu_t StackGetLen(Stack *stack)
{
	if(stack == NULL)
		return -1;
	return stack->top - stack->base;
}

statu_t StackIsEmpty(Stack *stack)
{
	if(stack == NULL)
		return -1;
	return stack->top == stack->base;
}

statu_t StackGetTop(Stack *stack,ElemType_t *e)
{
	if(stack == NULL || e == NULL)
		return -1;
	if(stack->top == stack->base)
		return -2;
	*e = *(stack->top -1);
	return 0;
}

statu_t StackPush(Stack *stack,ElemType_t *e)
{
	ElemType_t *p;
	if(stack == NULL || e == NULL)
		return -1;
	if(stack->top - stack->base == stack->stackSize){
		p = (ElemType_t*)realloc(stack->base,(stack->stackSize+STACK_INC_SIZE)*sizeof(ElemType_t));
		if(p == NULL)
			return -2;
		stack->base = p;
		stack->top = stack->base + stack->stackSize;
		stack->stackSize += STACK_INC_SIZE;
	}
	*stack->top = *e;
	stack->top++;
	return 0;
}

statu_t StackPop(Stack *stack,ElemType_t *e)
{
	if(stack == NULL || e == NULL)
		return -1;
	if(StackIsEmpty(stack))
		return -2;
	stack->top--;
	*e = *stack->top;
	return 0;
}

statu_t StackTraverse(Stack *stack)
{
	ElemType_t *p;
	int n = 0;

	if(stack == NULL)
		return -1;
	p = stack->top;
	while(p - stack->base){
		if(n%10 == 0)
			printf("\n");
		printf("%d\t",*(--p));
		n++;
	}
	printf("\n");
	return 0;
}

