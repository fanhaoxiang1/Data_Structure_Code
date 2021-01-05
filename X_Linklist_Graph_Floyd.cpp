#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define INF INT_MAX
#define MAX_VERTEX_NUM 20
typedef int InfoType; 
typedef int VertexType;
#define MAX 20

typedef struct ArcBox
{
    int tailvex, headvex;
    struct ArcBox *hlink, *tlink;
    int weight;
}ArcBox;

typedef struct VexNode
{
    char data;
    ArcBox *firstin, *firstout;
}VexNode;

typedef struct
{
    VexNode xlist[MAX_VERTEX_NUM];
    int vexnum, arcnum;
}Graph;

void InitGraph (Graph &G)
{
    char str[MAX_VERTEX_NUM];
    printf("依次输入G的顶点数和边数\n");
    scanf("%d%d",&G.vexnum, &G.arcnum);
    printf("依次输入G的顶点名\n");
    gets(str);
    //第一行空出来
    G.xlist[0] = {' ', NULL, NULL};
    for (int i=0; i<G.vexnum; i++) G.xlist[i+1].data = str[i];
    for (int i=0; i<G.arcnum; i++)
    {
        printf("依次输入第%d条边的起点、终点和权值",i);
        ArcBox *box;
        box = (ArcBox *)malloc(sizeof(ArcBox));
        scanf("%d%d%d", box->tailvex, box->headvex, box->weight);
        box->tlink = G.xlist[box->tailvex].firstout;
        box->hlink = G.xlist[box->headvex].firstin;
        G.xlist[box->tailvex].firstout = box;
        G.xlist[box->headvex].firstin = box;
    }
}//ez for me lol

typedef struct LGraph
{
    int ArcBox[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int vexnum, arcnum;
}LGraph;

void Floyd (LGraph &G, int **D, int **P)//D为最小距离矩阵，P为路径矩阵，定义-2为不连通，-1为直达
{
    D = (int **) malloc (sizeof(int *)*G.vexnum);
    P = (int **) malloc (sizeof(int *)*G.vexnum);
    for (int i=0; i<G.vexnum; i++)
    {
        D[i] = (int *) malloc (sizeof(int)*G.vexnum);
        P[i] = (int *) malloc (sizeof(int)*G.vexnum);
        for (int j=0; j<G.vexnum; j++) 
        {
            D[i][j] = G.ArcBox[i][j];//初始化
            if (D[i][j]==INF) P[i][j] = -2;
            else P[i][j] = -1;
        }
    }
    for (int k=0; k<G.vexnum; k++)//最外层是插入的点！！！
    {
        for (int i=0; i<G.vexnum; i++)
        {
            for (int j=0; j<G.vexnum; j++)
            {
                if (D[i][j]>D[i][k]+D[k][j])
                {
                    D[i][j] = D[i][k] + D[k][j];
                    P[i][j] = k;
                }
            }
        }
    }
}

void DFS (LGraph G, int v, void (*Visit)(int), int visited[MAX_VERTEX_NUM])
{
    Visit(v);
    visited[v] = 1;
    for (int w=0; w<G.vexnum; w++)
    {
        if(G.ArcBox[v][w]!=0&&G.ArcBox[v][w]!=INF&&!visited[w]) DFS(G, w, Visit, visited);
    }
}//对于唯一连通分支的DFS

void DFSTraverse (LGraph G, void (*Visit)(int))
{
    int visited[MAX_VERTEX_NUM] = {0};
    for (int v=0; v<G.vexnum; v++)
    {
        if (!visited[v]) DFS(G,v,Visit, visited);
    }
}//总的再看一眼