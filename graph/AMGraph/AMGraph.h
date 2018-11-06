#ifndef _AM_GRAPH_H
#define _AM_GRAPH_H

#ifdef __cplusplus
extern "C"{
#endif


/****************************************************************************
*  Type definition
*****************************************************************************/

typedef unsigned int VerticeType;
typedef unsigned int EdgeType;
typedef int StatusType;

typedef enum GraphType{
	DG = 0,
	UDG = 1,
	DN = 2,
	UDN = 3,
}GraphType;

#define MAX_VERTICES_NUM    (10)
typedef struct AMGraph
{
	VerticeType vertices[MAX_VERTICES_NUM];
	EdgeType Edge[MAX_VERTICES_NUM][MAX_VERTICES_NUM];
	int numV;
	int numE;
	GraphType type;
}AMGraph,*pAMGraph;

/****************************************************************************
*  Declaration
*****************************************************************************/
int GraphVerticesNum(pAMGraph pMat);
int GraphEdgeNum(pAMGraph pMat);
pAMGraph createGraph(GraphType type);
void destroyGraph(pAMGraph *pMat);
StatusType GraphAddVertices(pAMGraph pMat,VerticeType *pV,int num);
StatusType GraphAddEdge(pAMGraph pMat,VerticeType pV[2],EdgeType weight);
void GraphPrintVertices(pAMGraph pMat);
void GraphPrintEdges(pAMGraph pMat);
void GraphDFS(pAMGraph pMat);
void GraphBFS(pAMGraph pMat);
void GraphDemo(void);

#ifdef __cplusplus
}
#endif

#endif
