#ifndef map_h
#define map_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

#define MaxVerNum 25	
#define INFINITY 10000
typedef struct tm timeform;

typedef struct _VertexType{
	int number;			//号数
	char region[30];	//区域
	char info[30];		//电脑信息
	int mark;			//标记
	float price;		//价格

}VertexType;

typedef int EdgeType;

typedef struct _MGraph{
	VertexType vexs[MaxVerNum];
	EdgeType edges[MaxVerNum][MaxVerNum];
	int vnum,enumw;
}MGraph;

void CreateMGraph(MGraph *G,int edgeData[MaxVerNum][MaxVerNum]);
void initEdge(int edgeData[MaxVerNum][MaxVerNum]);
int PromptInput_Table(User *user);

void TableToFile(VertexType vexs);
void BFS_Tube_File(MGraph *G,int i,int flag[]);
void BFSTraverseAL_File(MGraph *G);
void TableFromFile(MGraph *G);
void BFS_Tube_Print(MGraph *G,int i,int flag[]);
void BFSTraverseAL_Print(MGraph *G);

void ShortestPath(MGraph *G,int D[MaxVerNum],int number);


#endif