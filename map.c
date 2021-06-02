#include "TWJ/list.h"
#include "TWJ/tree.h"
#include "TWJ/map.h"
#include "TWJ/menu.h"

void CreateMGraph(MGraph *G,int edgeData[MaxVerNum][MaxVerNum]){
	int i,j;
	G->vnum =  25;
	G->enumw = 40;
	for (i = 0; i < G->vnum-15; ++i){
		G->vexs[i].number = i + 1;
		G->vexs[i].mark = 0;
		strcpy(G->vexs[i].region,"低端区");
		strcpy(G->vexs[i].info,"联想");
		G->vexs[i].price = 6;
		
	}
	for (i = G->vnum-15; i < G->vnum; ++i){
		G->vexs[i].number = i + 1;
		G->vexs[i].mark = 0;
		strcpy(G->vexs[i].region,"高端区");
		strcpy(G->vexs[i].info,"华硕");
		G->vexs[i].price = 12;
	}
	for (i = 0; i < G->vnum; ++i){
		for (j = 0; j < G->vnum; ++j){
			G->edges[i][j] = edgeData[i][j];
		}
	}
	return;
}//创建图

void initEdge(int edgeData[MaxVerNum][MaxVerNum]){
	int i,j;
	int n = 0;
	for (i = 0; i < MaxVerNum; ++i){
		for (j = 0; j < MaxVerNum; ++j){
			edgeData[i][j] = INFINITY;
		}
	}
	while(n <= 20){
			for (i = 0 + n,j = 1 + n; i < 4 + n; ++i,++j){
			edgeData[i][j] = edgeData[j][i] = 7;
		}
		n += 5;
	}
	n = 0;
	while(n <= 4){
			for (i = 0 + n, j = 5 + n; i < 20 + n; i += 5, j += 5){
			edgeData[i][j] = edgeData[j][i] = 7;
		}
		n++;
	}
	return;
}//初始化边信息

int PromptInput_Table(User *user){
	system("clear");
	int dist[MaxVerNum];
	char flag;
	MGraph *graph = (MGraph *)malloc(sizeof(MGraph));
	int seat;
	TableFromFile(graph);
	BFSTraverseAL_Print(graph);
	printf("请选择位置\n");
	while(1){
			scanf("%d",&seat);
			if (graph->vexs[seat - 1].mark == 0){
				graph->vexs[seat - 1].mark = 1;
				user->seat = seat;
				printf("选择成功 !\n");
				ShortestPath(graph,dist,seat);
				break;
			}else{
				printf("位置已有人 !\n");
				printf("请重新选择 !\n");

			}
	}
	BFSTraverseAL_File(graph);
	free(graph);
	printf("\n");
	printf("请按任意键返回\n");
	getchar();
	getchar();
	system("clear");
	return seat;
}

void TableToFile(VertexType vexs){

	FILE *fp;
	fp = fopen("Data/table.txt","a");
	if (fp != NULL){
		fprintf(fp, "%d\t", vexs.number);
		fprintf(fp, "%s\t", vexs.region);
		fprintf(fp, "%s\t", vexs.info);
		fprintf(fp, "%d\t", vexs.mark);
		fprintf(fp, "%f\n", vexs.price);
		
		fclose(fp);
	}else{
		printf("文件保存失败 ！\n");
	}
}

void BFS_Tube_File(MGraph *G,int i,int flag[]){
	int j,k = 0;
	int Q[MaxVerNum],front,rear;
	front = 0; rear = -1;
	TableToFile(G->vexs[i]);			//保存顶点到文件中
	flag[i] = 1;
	rear++; Q[rear] = i;
	while(front <= rear){
		i = Q[front]; front++;
		for (j = 0; j < G->vnum; ++j){
			if (G->edges[i][j] == 1 && !flag[j]){
				TableToFile(G->vexs[j]);
				flag[j] = 1;
				rear++; Q[rear] = j;
			}
		}
	}
}

void BFSTraverseAL_File(MGraph *G){
	int i;
	FILE *fp;
	int flag[MaxVerNum] = {0};

	fp = fopen("Data/table.txt","w"); fclose(fp);	//清除原先tabledata的数据
	for (i = 0; i < G->vnum; ++i){
		if (!flag[i])
			BFS_Tube_File(G,i,flag);
	}
}


void TableFromFile(MGraph *G){
	FILE *fp;
	int i = 0,j;
	int edgeData[MaxVerNum][MaxVerNum];
	G->vnum =  25;
	initEdge(edgeData);
	fp = fopen("Data/table.txt", "r");
	if (fp != NULL)
	{
		while(!feof(fp)){
			fscanf(fp,"%d",&(G->vexs[i].number));
			fscanf(fp,"%s",G->vexs[i].region);
			fscanf(fp,"%s",G->vexs[i].info);
			fscanf(fp,"%d",&(G->vexs[i].mark));
			fscanf(fp,"%f",&(G->vexs[i].price));
			i++;
		}
		fclose(fp);
			for (i = 0; i < G->vnum; ++i){
				for (j = 0; j < G->vnum; ++j){
					G->edges[i][j] = edgeData[i][j];
				}
			}

	}else{
		printf("文件打开失败 ！\n");
	}
	return;
}

void BFS_Tube_Print(MGraph *G,int i,int flag[]){

	int j;
	int Q[MaxVerNum],front,rear;
	front = 0; rear = -1;
	printf("%d\t",G->vexs[i].number );
	printf("%s\t",G->vexs[i].region );
	printf("%s\t",G->vexs[i].info );
	if(G->vexs[i].mark == 1){
		printf("已有人 !\t\t");
	}else{
		printf("空 !\t\t");
	}
	printf("%.2f ￥\n",G->vexs[i].price );
	flag[i] = 1;
	rear++; Q[rear] = i;
	while(front <= rear){
		i = Q[front]; front++;
		for (j = 0; j < G->vnum; ++j){
			if (G->edges[i][j] == 1 && !flag[j]){
				printf("%d\t",G->vexs[i].number );
				printf("%s\t",G->vexs[i].region );
				printf("%s\t",G->vexs[i].info );
				if(G->vexs[i].mark == 1){
					printf("已有人 !\t\t");
				}else{
					printf("空 !\t\t");
				}
				printf("%.2f ￥\n",G->vexs[i].price );

				flag[j] = 1;
				rear++; Q[rear] = j;
			}
		}
	}
}

void BFSTraverseAL_Print(MGraph *G){
	int i;
	int flag[MaxVerNum] = {0};
	printf("座号\t区域\t信息\n");
	for (i = 0; i < G->vnum; ++i){
		if (!flag[i])
			BFS_Tube_Print(G,i,flag);
	}
}//对图遍历输出

void ShortestPath(MGraph *G,int D[MaxVerNum],int number){
	int i,j,k,min;
	int final[MaxVerNum] = {0};
	final[0] = 1;
	for (i = 0; i < G->vnum; ++i){
		D[i] = G->edges[0][i];
	}
	D[0] = 0;
	final[0] = 1;
	for (i = 1; i < G->vnum; ++i){
		min = INFINITY + 1;
		for (k = 0; k < G->vnum; ++k){
			if (final[k] == 0 && D[k]< min){
				j = k;
				min = D[k];
			}
		}
		final[j] = 1;
		for (k = 0; k < G->vnum; ++k){
			if (final[k] == 0 && (D[j] + G->edges[j][k] < D[k])){
				D[k] = D[j] + G->edges[j][k];
			}
		}
	}
	for (i = 1; i < G->vnum; ++i){
		if(D[i] < 10000 && G->vexs[i].number == number)
			printf("路程为:%d: \n",D[i] );
	}
	return;
		
}
