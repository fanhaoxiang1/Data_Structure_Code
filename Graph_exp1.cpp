#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define INF (INT_MAX/2)
#define MAX_VERTEX_NUM 6
typedef int VRType;
typedef char VertexType;

typedef struct ArcCell
{
    VRType weight;
}ArcCell, ArcMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct Graph
{
    ArcMatrix arcs;
    VertexType vexs[MAX_VERTEX_NUM];
    int vexnum, arcnum;
}Graph;//定义了一个有向图

void FindVex (Graph G, VertexType e, int &s)
{
    for (int i=0; i<G.vexnum; i++)
    {
        if (G.vexs[i] == e)
        {
            s = i;
            return;
        }
    }
    printf("%c并没有匹配项！\n", e);
    system("pause");
    exit(-1);
}
//degbuged,10:54

void InitGraph (Graph &G)
{
    printf("请输入结点数\n");
    scanf("%d",&G.vexnum);
    printf("请输入他们的信息\n");
    char *temp;
    temp = (char*) malloc (sizeof(char)*G.vexnum);
    scanf("%s",temp);
    for (int i=0; i<G.vexnum; i++) G.vexs[i] = temp[i];//初始化顶点j
    for (int i=0; i<G.vexnum; i++)
    {
        for (int j=0; j<G.vexnum; j++)
        {
            G.arcs[i][j].weight = INF;
        }
    }//初始化整个邻接矩阵
    printf("请输入有向边的数量\n");
    scanf("%d",&G.arcnum);
    for (int i=0; i<G.arcnum; i++)
    {
        printf("请输入第%d条边的起点和终点\n",i+1);
        char e1, e2;
        fflush(stdin);
        scanf("%c%c", &e1, &e2);//这里要格外检查，不知道行不行
        int s1, s2;
        FindVex (G, e1, s1); FindVex(G, e2, s2);
        printf("请输入这条边的权值\n");
        scanf("%d",&G.arcs[s1][s2].weight);
    }
}
//debugged,10:54

void FindShortestRoad (Graph G, char v0, int P[], int D[])
//P记录所经过的路径的向量，记得初始化为INF，D为代价向量，记得初始化为INF
{
    int final[G.vexnum];
    for (int i=0; i<G.vexnum; i++)
    {
        final[i] = 0;
    }
    int v;
    FindVex (G, v0, v);
    D[v] = 0;
    P[v] = v;
    for (int i=0; i<G.vexnum; i++)//初始化
    {
        if (G.arcs[v][i].weight<INF)
        {
            D[i] = G.arcs[v][i].weight;
            P[i] = v;
        }
    }
    final[v] = 1;
    for (int i=1; i<G.vexnum; i++)//每次找个最小的，直到找完全部为止
    {
        int min = INF;
        for (int w=0; w<G.vexnum; w++)
        {
            if (!final[w] && D[w]<min)
            {
                v = w;
                min = D[w];
            }
        }
        final[v] = 1;
        for (int w=0; w<G.vexnum; w++)
        {
            if(!final[w] && min+G.arcs[v][w].weight<D[w])
            {
                D[w] = min + G.arcs[v][w].weight;
                P[w] = v;
            }
        }
    }
}//P[w]记录的是它上一个顶点
//debugged,11:35

void PrintRoad (Graph G, char e,int P[], int D[])
{
    int v;
    FindVex(G, e, v);
    for (int i=0; i<G.vexnum; i++)//开始打印最短路径，从第1个开始
    {
        if (i==v) printf("点%c到自身的距离为0\n", e);
        else if(D[i]>=INF) printf("点%c到点%c没有路径！\n", e, G.vexs[i]);
        else
        {
            printf("点%c到点%c的距离为%d\n",G.vexs[v],G.vexs[i],D[i]);
            printf("其路径为\n");
            int j = P[i];
            printf("%c <- ", G.vexs[i]);
            while (j!=v)
            {
                printf("%c <- ",G.vexs[j]);
                j = P[j];
            }
            printf("%c\n", G.vexs[v]);
        }
        
    }
}
//debugged,11:44

int main()
{
    Graph G;
    InitGraph(G);
    char c;
    printf("你要找哪个点到其他点的最短路径？\n");
    fflush(stdin);
    scanf("%c",&c);
    int P[G.vexnum];
    int D[G.vexnum];
    for (int i=0; i<G.vexnum; i++)
    {
        P[i] = INF;
        D[i] = INF;
    }
    FindShortestRoad(G, c, P, D);
    PrintRoad(G, c, P, D);
    system("pause");
    return 0;
}