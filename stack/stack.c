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
#define INDICATE_INFO "Stack haven't been created,please create firstly"

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

static void displayMenu(void)
{
	printf("-----------------------Menu--------------------------\n");
	printf("-      1.  stack init          2.  destroy stack    -\n");
	printf("-      3.  push                4.  pop              -\n");
	printf("-      5.  check empty         6.  get top          -\n");
	printf("-      7.  get length          8.  clear stack      -\n");
	printf("-      9.  stack traverse      10. show menu        -\n");
	printf("-----------------------------------------------------\n\n");
}

static void safeFlush(FILE *fp)
{
	int ch;
	while((ch = fgetc(fp)) != EOF && ch != '\n');
}

void StackDemo(void)
{
	int cmdId;
	Stack *myStack = NULL;
	statu_t status;

	displayMenu();
	while(1){
		cmdId = -1;
		safeFlush(stdin);
		printf("\nplease choose which action to do:");
		scanf("%d",&cmdId);
		printf("\n");
		switch(cmdId){
			case 1:
			{
				if(myStack != NULL){
					printf("Stack exsits\n");
					break;
				}
				myStack = (Stack*)malloc(sizeof(Stack));
				if(myStack == NULL){
					printf("create stack failed\n");
				}
				if(!StackInit(myStack)){
					printf("create stack success\n");
				}else{
					printf("create stack failed\n");
				}
				break;
			}
			case 2:
			{
				if(myStack == NULL){
					printf("%s\n",INDICATE_INFO);
				}else{
					StackDestroy(&myStack);
					printf("destroy stack");
				}
				break;
			}
			case 3:
			{
				if(myStack == NULL){
					printf("%s\n",INDICATE_INFO);
				}else{
					ElemType_t tmp;
					printf("please input item you want to push:");
					scanf("%d",&tmp);
					printf("\n");
					if(!StackPush(myStack,&tmp)){
						printf("push success\n");
					}else{
						printf("push failed\n");
					}
				}
				break;
			}
			case 4:
			{
				if(myStack == NULL){
					printf("%s\n",INDICATE_INFO);
				}else{
					ElemType_t e;
					status = StackPop(myStack,&e);
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
				if(myStack == NULL){
					printf("%s\n",INDICATE_INFO);
				}else{
					if(StackIsEmpty(myStack)){
						printf("stack is empty\n");
					}else{
						printf("stack is not empty\n");
					}
				}
				break;
			}
			case 6:
			{
				if(myStack == NULL){
					printf("%s\n",INDICATE_INFO);
				}else{
					ElemType_t e;
					status = StackGetTop(myStack,&e);
					if(!status){
						printf("top element: %d\n",e);
					}else{
						printf("nothing to pop\n");
					}
				}
				break;
			}
			case 7:
			{
				if(myStack == NULL){
					printf("%s\n",INDICATE_INFO);
				}else{
					printf("length of stack: %d\n",StackGetLen(myStack));
				}
				break;
			}
			case 8:
			{
				if(myStack == NULL){
					printf("%s\n",INDICATE_INFO);
				}else{
					StackClear(myStack);
					printf("stack had been clear\n");
				}
				break;
			}
			case 9:
			{
				if(myStack == NULL){
					printf("%s\n",INDICATE_INFO);
				}else{
					printf("stack traverse:\n");
					StackTraverse(myStack);
				}
				break;
			}
			case 10:
			{
				displayMenu();
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
	StackDemo();
	for(;;);
	return 0;
}