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

typedef struct
{
    VertexType adjvex;
    VRType lowcost;
}Closedge[MAX_VERTEX_NUM];
//adjvex[i] = k;
//lowcost[i] = w;意思是顶点i和顶点k之间的权值为w

int Minimum(Closedge closedge, Graph G)
{
    int min = INF;
    int ind;
    for (int i=0; i<G.vexnum; i++)
    {
        if (closedge[i].lowcost!=0 && closedge[i].lowcost<min)
        {
            min = closedge[i].lowcost;
            ind = i;
        }
    }
    return ind;
}
int Prim (Graph G, char e)//从顶点e开始构建最小生成树
{
    int u;
    FindVex (G, e, u);
    Closedge closedge;  
    for (int j=0; j<G.vexnum; j++)
    {
        closedge[j].adjvex = u;
        closedge[j].lowcost = G.arcs[u][j].weight;
    }
    closedge[u].lowcost = 0;//完成初始化，将U加入顶点集
    for (int i=1; i<G.vexnum; i++)
    {
        int k = Minimum(closedge, G);
        closedge[k].lowcost = 0; 
        //找到最短
        //更新表格
        for (int j=0; j<G.vexnum; j++)
        {
            if (G.arcs[k][j].weight < closedge[j].lowcost)
            {
                closedge[j].adjvex = G.vexs[k];
                closedge[j].lowcost = G.arcs[k][j].weight;
            }
        }
        //最后检查是否全部都在树中
        for (int i=1; i<G.vexnum; i++)
        {
            if (closedge[i].lowcost != 0 ) return 0;
        }
        return 1;
    }
}

//kruskal算法先修知识：并查集
//如果Vset[i] = Vset[j]则i与j同处于同一个连通分量中


typedef struct
{
    VertexType from;
    VertexType to;
    VRType cost;
}VertexSet[MAX_VERTEX_NUM];

void SortEdges (Graph G, VertexSet vs);
int kruskal (Graph G)
{
    VertexSet vs;
    SortEdges (G, vs);//对所有边进行排序
    int Vset[G.vexnum];
    for (int i=0; i<G.vexnum; i++)
    {
        Vset[i] = i;
    }//初始化Vset，让所有等于本身
    for (int i=0; i<G.arcnum; i++)
    {
        if (Vset[vs[i].from] != Vset[vs[i].to])
        {
            Vset[vs[i].from] = Vset[vs[i].to];
        }
    }
    for (int i=1; i<G.vexnum; i++)
    {
        if (Vset[i] != Vset[i-1]) return 0;
    }
    return 1;
}