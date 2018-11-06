/****************************************************************************
*  Includes
*****************************************************************************/

#include "AMGraph.h"
#include "stack.h"
#include "queue.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"

/****************************************************************************
*  Macro definition
*****************************************************************************/

#define GRAPH_TYPE_DEFAULT   DG
#define INF                  (0xFFFFFFFF)
#define INDICATE_INFO        "graph haven't been created,please create list firstly"


/****************************************************************************
*  Functions
*****************************************************************************/

int GraphVerticesNum(pAMGraph pMat)
{
	return (pMat == NULL) ? -1 : pMat->numV;
}

int GraphEdgeNum(pAMGraph pMat)
{
	return (pMat == NULL) ? -1 : pMat->numE; 
}

pAMGraph createGraph(GraphType type)
{
	pAMGraph pMat = (pAMGraph)malloc(sizeof(AMGraph));
	if(pMat == NULL)
		return NULL;
	pMat->type = type;
	pMat->numV = 0;
	pMat->numE = 0;
	for(int i=0;i<MAX_VERTICES_NUM;i++){
		pMat->vertices[i] = 0;
		for(int j=0;j<MAX_VERTICES_NUM;j++){
			if(type == DG || type == UDG)
				pMat->Edge[i][j] = 0;
			else if(type == DN || type == UDN)
				pMat->Edge[i][j] = INF;
			else
				return NULL;
		}
	}
	return pMat;
}

void destroyGraph(pAMGraph *pMat)
{
	if(pMat != NULL && *pMat != NULL){
		free(*pMat);
		*pMat = NULL;
	}
}

StatusType GraphAddVertices(pAMGraph pMat,VerticeType *pV,int num)
{
	int n = 0;
	bool repeat = false;	
	if(pMat == NULL || pV == NULL || num <= 0)
		return -1;
	for(int i=0;i<num;i++){
		repeat = false;
		for(int j=0;j<pMat->numV;j++){
			if(pMat->vertices[j] == pV[i]){
				repeat = true;
				break;
			}
		}
		if(!repeat){
			pMat->vertices[pMat->numV++] = pV[i];
			n++;
		}
	}
	return n;
}

StatusType GraphAddEdge(pAMGraph pMat,VerticeType pV[2],EdgeType weight)
{
	if(pMat == NULL || pV == NULL)
		return -1;
	if(pV[0] == pV[1])
		return -2;
	for(int i=0;i<pMat->numV;i++){
		if(pMat->vertices[i] == pV[0]){
			for(int j=0;j<pMat->numV;j++){
				if(pMat->vertices[j] == pV[1]){
					switch(pMat->type){
						case DG:
						{
							if(pMat->Edge[i][j] == 0){			
								pMat->Edge[i][j] = 1;
								pMat->numE++;
							}
							break;
						}
						case UDG:
						{
							if(pMat->Edge[i][j] == 0){
								pMat->Edge[i][j] = pMat->Edge[j][i] = 1;
								pMat->numE++;
							}
							break;
						}
						case DN:
						{
							if(pMat->Edge[i][j] == INF){
								pMat->Edge[i][j] = weight;
								pMat->numE++;
							}
							break;
						}
						case UDN:
						{
							if(pMat->Edge[i][j] == INF){
								pMat->Edge[i][j] = pMat->Edge[j][i] = weight;
								pMat->numE++;
							}
							break;
						}
					}
					return 0;
				}
			}
		}
	}
	return -3;
}

void GraphPrintVertices(pAMGraph pMat)
{
	if(pMat != NULL){
		for(int i =0;i<pMat->numV;i++){
			if(i % 10 == 0)
				printf("\n");
			printf("%d\t",pMat->vertices[i]);
		}
	}
}

void GraphPrintEdges(pAMGraph pMat)
{
	if(pMat != NULL){
		for(int i=0;i<pMat->numV;i++){
			for(int j=0;j<pMat->numV;j++){
				switch(pMat->type){
					case DG:
					{
						if(pMat->Edge[i][j] != 0)
							printf("(%d,%d)\t",pMat->vertices[i],pMat->vertices[j]);
						break;
					}
					case UDG:
					{
						if(pMat->Edge[i][j] != 0 && i>j)
							printf("(%d,%d)\t",pMat->vertices[i],pMat->vertices[j]);
						break;
					}
					case DN:
					{
						if(pMat->Edge[i][j] != INF)
							printf("(%d,%d)\t",pMat->vertices[i],pMat->vertices[j]);
						break;
					}
					case UDN:
					{
						if(pMat->Edge[i][j] != INF && i>j)
							printf("(%d,%d)\t",pMat->vertices[i],pMat->vertices[j]);
					}
				}
			}
		}
	}
}

void GraphDFS(pAMGraph pMat)
{
	if(pMat != NULL && pMat->numV > 0){
		char *visited;
		int k,j;
		EdgeType w = (pMat->type == DG || pMat->type == UDG) ? 0 : INF;
		
		visited = (char*)malloc(pMat->numV);
		if(visited == NULL)
			return;
		memset(visited,0x0,pMat->numV);
		Stack s;
		StackInit(&s);
		for(int i=0;i<pMat->numV;i++){
			if(visited[i] != 1){
				StackPush(&s,&i);
				visited[i] = 1;
				printf("%d-->",pMat->vertices[i]);
				while(!StackIsEmpty(&s)){
					StackGetTop(&s,&k);
					for(j=0;j<pMat->numV;j++){
						if(pMat->Edge[k][j] != w && visited[j] == 0){
							k = j;
							StackPush(&s,&k);
							printf("%d-->",pMat->vertices[k]);
							visited[k] = 1;
							break;  
						}
					}
					if(j == pMat->numV)
						StackPop(&s,&k);
				}
			}
		}
		printf("NULL\n");
		free(visited);
	}
}

void GraphBFS(pAMGraph pMat)
{
	if(pMat != NULL){
		char *visited;
		int k,j;
		EdgeType nil = (pMat->type == DG || pMat->type == UDG) ? 0 : INF;
		Queue *q;

		visited = (char*)malloc(pMat->numV);
		if(visited == NULL)
			return;
		q = QueueCreate();
		if(q == NULL)
			return;
		QueueInit(q);
		memset(visited,0x0,pMat->numV);
		for(int i=0;i<pMat->numV;i++){
			if(visited[i] != 1){
				QueuePush(q,i);
				printf("%d-->",pMat->vertices[i]);
				visited[i] = 1;
				while(!QueueIsEmpty(q)){
					QueuePop(q,&k);
					for(j=0;j<pMat->numV;j++){
						if(pMat->Edge[k][j] != nil && visited[j] == 0){
							QueuePush(q,j);
							printf("%d-->",pMat->vertices[j]);
							visited[j] = 1;
						}
					}
				}
			}
		}
		printf("NULL\n");
		free(visited);
	}
}
static void displayMenu(void)
{
	printf("-----------------------Menu---------------------------\n");
	printf("-      1. create graph         2.  destroy graph     -\n");
	printf("-      3. add vertices         4.  add edge          -\n");
	printf("-      5. print vertices       6.  print edges       -\n");
	printf("-      7. vertices num         8.  edges num         -\n");
	printf("-      9. BFS                  10. DFS               -\n");
	printf("-      11. displayMenu                               -\n");
	printf("------------------------------------------------------\n\n");
}

static void safeFlush(FILE *fp)
{
	int ch;
	while((ch = fgetc(fp)) != EOF && ch != '\n');
}

void GraphDemo(void)
{
	int cmdId;
	pAMGraph myGraph = NULL;

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
				int type;
				if(myGraph != NULL)
					printf("graph exsits\n");
				printf("please input the type of graph(0->DG,1->UDG,2->DN,3->UDN):");
				scanf("%d",&type);
				myGraph = createGraph(type);
				if(myGraph == NULL){
					printf("create graph failed");
				}else{
					printf("create graph succussfully\n");
				}
				break;
			}
			case 2:
			{
				if(myGraph == NULL)
				{
					printf("%s\n",INDICATE_INFO);
				}else{
					printf("destroy graph");
					destroyGraph(&myGraph);
				}
				break;
			}
			case 3:
			{
				if(myGraph == NULL)
				{
					printf("%s\n",INDICATE_INFO);
				}else{
					int verNum,n;
					VerticeType *verAdd;
					printf("please input the num of added vertices:");
					scanf("%d",&verNum);
					verAdd = (VerticeType*)malloc(sizeof(VerticeType)*verNum);
					if(verAdd == NULL){
						printf("malloc failed");
						break;
					}
					for(int i=0;i<verNum;i++){
						printf("please input the %dth vertices:",i);
						scanf("%d",&verAdd[i]);
					}
					if((n = GraphAddVertices(myGraph,verAdd,verNum)) > 0){
						printf("%d vertices had been added\n",n);
					}else{
						printf("add vertices failed\n");
					}
					free(verAdd);
				}
				break;
			}
			case 4:
			{
				if(myGraph == NULL)
				{
					printf("%s\n",INDICATE_INFO);
				}else{
					VerticeType vertex[2];
					EdgeType weight;
					printf("please input the head vertex:");
					scanf("%d",&vertex[0]);
					printf("please input the tail vertex:");
					scanf("%d",&vertex[1]);
					printf("please input weight of edge:");
					scanf("%d",&weight);
					if(!GraphAddEdge(myGraph,vertex,weight))
						printf("add edge(%d,%d) succussfully",vertex[0],vertex[1]);
				}
				break;
			}
			case 5:
			{
				if(myGraph == NULL)
				{
					printf("%s\n",INDICATE_INFO);
				}else{
					printf("print vertices of graph:\n");
					GraphPrintVertices(myGraph);
				}
				break;
			}
			case 6:
			{
				if(myGraph == NULL)
				{
					printf("%s\n",INDICATE_INFO);
				}else{
					printf("print edges of graph:\n");
					GraphPrintEdges(myGraph);
				}
				break;
			}
			case 7:
			{
				if(myGraph == NULL)
				{
					printf("%s\n",INDICATE_INFO);
				}else{
					printf("vertices num of graph:%d\n",myGraph->numV);
				}
				break;
			}
			case 8:
			{
				if(myGraph == NULL)
				{
					printf("%s\n",INDICATE_INFO);
				}else{
					printf("edges num of graph:%d\n",myGraph->numE);
				}
				break;
			}
			case 9:
			{
				if(myGraph == NULL)
				{
					printf("%s\n",INDICATE_INFO);
				}else{
					printf("BFS:\n");
					GraphBFS(myGraph);
				}
				break;
			}
			case 10:
			{
				if(myGraph == NULL)
				{
					printf("%s\n",INDICATE_INFO);
				}else{
					printf("DFS:\n");
					GraphDFS(myGraph);
				}
				break;
			}
			case 11:
			{
				displayMenu();
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
	GraphDemo();
	for(;;);
	return 0;
}

