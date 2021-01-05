#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define INF INT_MAX
#define MAX_VERTEX_NUM 20
typedef enum {DG, DN, UDG, UDN} GraphKind;
typedef int VRType;
typedef char InfoType;
typedef char VertexType;
typedef int Status;

typedef struct ArcCell
{
    VRType adj;
    InfoType *Info;
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct MGraph
{
    VertexType vexs[MAX_VERTEX_NUM];
    AdjMatrix arcs;
    int vexnum, arcnum;
    GraphKind kind;
}MGraph;

//初始化无向网

int LocateVex (MGraph &G,VertexType c)
{
    int i = 0;
    while (i < G.vexnum)
    {
        if (G.vexs[i]==c) return i;
    }
    return -1;
}
Status CreateUDN (MGraph &G)
{
    int IncInfo;
    printf("请问各弧是否包含其他信息?若没有请输入0\n");
    scanf("%d",&IncInfo);
    printf("请输入当前顶点数量和弧数\n");
    scanf("%d%d",&G.vexnum,&G.arcnum);
    //初始化向量
    int i = 0, j = 0;
    for (; i<G.vexnum; i++)
    {
        fflush(stdin);
        scanf("%c",&G.vexs[i]);
    }
    for (i=0; i<G.vexnum; i++)
    {
        for (j=0; j<G.vexnum; j++)
        {
            G.arcs[i][j] = {INF, NULL};
        }
    }
    //构造邻接矩阵
    int k;
    for (k=0; k<G.arcnum; k++)
    {
        VertexType v1, v2;
        printf("请输入起点与终点\n");
        i = LocateVex(G, v1); j = LocateVex(G, v2);
        printf("请输入权值\n");
        scanf("%d",&G.arcs[i][j]);
        fflush(stdin);
        if (IncInfo) scanf("%s",G.arcs[i][j].Info);
        G.arcs[j][i] = G.arcs[i][j];
    }

}