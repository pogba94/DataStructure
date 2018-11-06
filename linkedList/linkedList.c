/****************************************************************************
*  Includes
*****************************************************************************/

#include "linkedList.h"
#include "stdio.h"
#include "stdlib.h"

/****************************************************************************
*  Macro definition
*****************************************************************************/

#define INDICATE_INFO "list haven't been created,please create list firstly"

/****************************************************************************
*  Function 
*****************************************************************************/

List ListCreate(void)
{
	pListNode head;
	head = (pListNode)malloc(sizeof(listNode));	
	if(head == NULL)
		return NULL;
	head->next = NULL;
	head->data = 0;
	return head;
}

statu_t ListIsEmpty(List list)
{
	if(list == NULL)
		return -1;
	return (list->next == NULL);
}

statu_t ListInsertItem(List list,int pos,elemType_t val)
{
	pListNode p,item;
	if(list == NULL || pos < 0)
		return -1;
	p = list;
	while(pos-- && p != NULL){
		p = p->next;
	}

	if(p == NULL)
		return -2;
	item = (pListNode)malloc(sizeof(listNode));
	if(item == NULL)
		return -3;
	item->next = p->next;
	item->data = val;
	p->next = item;
	return 0;
}

statu_t ListInsertItemTail(List list,elemType_t val)
{
	pListNode p,item;
	if(list == NULL)
		return -1;
	p = list->next;
	while(p->next != NULL){
		p = p->next;
	}
	item = (pListNode)malloc(sizeof(listNode));
	if(item == NULL)
		return -2;
	p->next = item;
	item->next = NULL;
	item->data = val;
	return 0;
}

statu_t ListTraverse(List list)
{
	pListNode p = NULL;
	int n = 0;
	if(list == NULL)
		return -1;
	p = list->next;
	while(p != NULL){
		if(n%10 == 0)
			printf("\n");
		printf("%d\t",p->data);
		p = p->next;
		n++;
	}
	printf("\n\n");
	return 0;
}

statu_t ListDestroy(List *list) 
{
	pListNode p = NULL,tmp;

	if(list == NULL || *list == NULL)
		return -1;
	p = *list;
	*list = NULL;
	while(p != NULL){
		tmp = p->next;
		free(p);
		p = tmp;
	}
	return 0;
}

int ListGetLen(List list)
{
	int len = 0;
	pListNode p;
	if(list != NULL){
		p = list->next;
		while(p != NULL){
			len++;
			p = p->next;
		}
	}
	return len;
}

pListNode ListFindItem(List list,elemType_t val)
{
	pListNode p = NULL;
	if(list != NULL){
		p = list->next;
		while(p != NULL && p->data != val){
			p = p->next;
		}	
	}
	return p;
}

statu_t ListDeleteItem(List list,elemType_t val)
{
	pListNode p1 = NULL,p2 = NULL;
	if(list == NULL)
		return -1;
	p1 = list;
	p2 = p1->next;
	while(p2 != NULL && p2->data != val){
		p1 = p2;
		p2 = p2->next; 
	}
	if(p2 == NULL)
		return -2;
	p1->next = p2->next;
	free(p2);
	return 0;
}

static void displayMenu(void)
{
	printf("-----------------------Menu------------------------\n");
	printf("-      1. create list         2. insert item      -\n");
	printf("-      3. delete item         4. get len          -\n");
	printf("-      5. check empty         6. destroy list     -\n");
	printf("-      7. traverse list       8. show menu        -\n");
	printf("---------------------------------------------------\n\n");
}

static void safeFlush(FILE *fp)
{
	int ch;
	while((ch = fgetc(fp)) != EOF && ch != '\n');
}

void ListDemo(void)
{
	int cmdId;
	List myList = NULL;

	displayMenu();
	while(1){
		cmdId = -1;
		safeFlush(stdin);
		printf("please choose which action to do:");
		scanf("%d",&cmdId);
		printf("\n");
		switch(cmdId){
			case 1:
			{
				if(myList != NULL){
					printf("list is exsit\n");
					break;
				}
				myList = ListCreate();
				if(myList == NULL){
					printf("create list failed\n");
				}else{
					printf("create list success\n");
				}
				break;
			}
			case 2:
			{
				if(myList == NULL){
					printf("%s\n",INDICATE_INFO);
				}else{
					int pos;
					elemType_t data;
					printf("please input the pos:");
					scanf("%d",&pos);
					printf("please input the value:");
					scanf("%d",&data);
					if(!ListInsertItem(myList,pos,data)){
						printf("insert item success\n");
					}else{
						printf("insert item failed\n");
					}
				}
				break;
			}
			case 3:
			{
				if(myList == NULL){
					printf("%s\n",INDICATE_INFO);
				}else{
					elemType_t data;
					printf("please input the value of item you want to delete:");
					scanf("%d",&data);
					printf("\n");
					if(!ListDeleteItem(myList,data)){
						printf("delete item success\n");
					}else{
						printf("delete item failed\n");
					}
				}
				break;
			}
			case 4:
			{
				if(myList == NULL){
					printf("%s\n",INDICATE_INFO);
				}else{
					printf("the length of list:%d\n",ListGetLen(myList));
				}
				break;
			}
			case 5:
			{
				if(myList == NULL){
					printf("%s\n",INDICATE_INFO);
				}else{
					int ret = ListIsEmpty(myList);
					if(ret){
						printf("list is empty\n");
					}else{
						printf("list is not empty\n");
					}
				}
				break;
			}
			case 6:
			{
				if(myList == NULL){
					printf("%s\n",INDICATE_INFO);
				}else{
					ListDestroy(&myList);
					printf("list had been destroyed\n");
				}
				break;
			}
			case 7:
			{
				if(myList == NULL){
					printf("%s\n",INDICATE_INFO);
				}else{
					printf("list traverse:\n");
					ListTraverse(myList);
				}
				break;
			}
			case 8:
			{
				displayMenu();
				break;
			}
			default:break;
		}
	}
}

void ListTest(void)
{
	int len = 0;
	List myList = NULL;
	elemType_t tmp = 0;

	printf("----------------linked list test----------------\n\n");
	myList = ListCreate();
	if(myList == NULL){
		printf("create list failed\n");
		return;
	}
	printf("check if list is empty(1->empty,0->not empty):%d\n",ListIsEmpty(myList));
	do{
		printf("\nplease input the value of %dTh element(end with -1):",len); 
		scanf("%d",&tmp);
		if(tmp != -1){
			ListInsertItem(myList,len++,tmp);
		}
	}while(tmp != -1);
	printf("\ntraverse the list:\n");
	ListTraverse(myList);
	printf("\n\nlength of list:%d\n",ListGetLen(myList));
	printf("\nplease choose to delete a item:");
	scanf("%d",&tmp);
	printf("delete item:%d\n",tmp);
	ListDeleteItem(myList,tmp);
	ListTraverse(myList);
	printf("\n\ndestroy list\n");
	ListDestroy(&myList);
}


int main(void)
{
	ListDemo();
	for(;;);
	return 0;
}