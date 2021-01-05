#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#define INF (INT_MAX/3)
#define MAX_VERTEX_NUM 6
#define MAX_NAME_LEN 64
#define MAX_INFO_LEN 128
typedef int VRType;

typedef struct VertexType
{
    char *name;
    char *info;
}VertexType;

typedef struct ArcCell
{
    VRType weight;
}ArcCell, ArcMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct Graph
{
    ArcMatrix arcs;
    VertexType vexs[MAX_VERTEX_NUM];
    int vexnum, arcnum;
}Graph;//定义了一个无向图

void FindVex (Graph G, char *e, int &s)
{
    for (int i=0; i<G.vexnum; i++)
    {
        if (strcmp(G.vexs[i].name, e)==0)
        {
            s = i;
            return;
        }
    }
    printf("%s并没有匹配项！\n", e);
    system("pause");
    exit(-1);
}
//统一标准：自己到自己的距离是INF
void InitGraph (Graph &G)
{
    printf("请输入景点数\n");
    scanf("%d",&G.vexnum);
    for (int i=0; i<G.vexnum; i++)
    {
        printf("请输入第%d个景点名\n",i+1);
        fflush(stdin);
        G.vexs[i].name = (char *) malloc (sizeof(char)*MAX_NAME_LEN);
        G.vexs[i].info = (char *) malloc (sizeof(char)*MAX_INFO_LEN);
        gets(G.vexs[i].name);
        printf("请输入%s的景点信息\n",G.vexs[i].name);
        fflush(stdin);
        gets(G.vexs[i].info);
    }//初始化景点信息
    for (int i=0; i<G.vexnum; i++)
    {
        for (int j=0; j<G.vexnum; j++)
        {
            G.arcs[i][j].weight = INF;
        }
    }//初始化整个邻接矩阵
    printf("请输入边的数量\n");
    scanf("%d",&G.arcnum);
    for (int i=0; i<G.arcnum; i++)
    {
        printf("请输入第%d条边的两个顶点\n",i+1);
        char *e1 = (char *) malloc (sizeof(char)*MAX_NAME_LEN);
        char *e2 = (char *) malloc (sizeof(char)*MAX_NAME_LEN);;
        fflush(stdin);
        gets(e1);
        gets(e2);
        int s1, s2;
        FindVex (G, e1, s1); FindVex(G, e2, s2);
        printf("请输入这条边的权值\n");
        scanf("%d",&G.arcs[s1][s2].weight);
        G.arcs[s2][s1].weight = G.arcs[s1][s2].weight;
    }
}//初始化完毕

void SceneryList (Graph G)
{
    printf("学校有如下景点\n");
    int i = 0;
    while (i<G.vexnum)
    {
        printf("%d %s\n", i+1, G.vexs[i].name);
        i++;
    }
}

void InfoProvider (Graph G)
{
    printf("您需要查看哪个景点的信息？\n");
    fflush(stdin);
    char *temp = (char *) malloc (sizeof(char)*MAX_NAME_LEN);
    gets(temp);
    //考虑到用户可能输入中文也可能输入编号
    if (temp[0]>'0' && temp[0]<'9')
    {
        printf("%s\n", G.vexs[int(temp)].info);
    }
    else
    {
        int s;
        FindVex (G, temp, s);
        printf("%s\n", G.vexs[s].info);
    }
}

void ShortestRoad (Graph G, int dist[MAX_VERTEX_NUM][MAX_VERTEX_NUM], int way[MAX_VERTEX_NUM][MAX_VERTEX_NUM])
{
    for (int i=0; i<G.vexnum; i++)
    {
        for (int j=0; j<G.vexnum; j++)
        {
            dist[i][j] = G.arcs[i][j].weight;
            //有路就是-1,没路或者自身到自身都是0
            if (G.arcs[i][j].weight<INF) way[i][j]=-1;
            else way[i][j] = 0;
        }
    }//初始化
    for (int k=0; k<G.vexnum; k++)
    {
        for (int i=0; i<G.vexnum; i++)
        {
            for (int j=0; j<G.vexnum; j++)
            {
                if (dist[i][k]+dist[k][j]<dist[i][j] && i!=j)
                {
                    dist[i][j] = dist[i][k]+dist[k][j];
                    way[i][j] = k;
                }
            }
        }
    }
}

void GetPath (Graph G, int i, int j, int path[], int &cnt, int dist[MAX_VERTEX_NUM][MAX_VERTEX_NUM], int way[MAX_VERTEX_NUM][MAX_VERTEX_NUM])
{
    //当自身到自身，就是不连通的状态证明已经遍历完所有结点（方案废除）
    if (way[i][j]==-1) return;
    int k = way[i][j];
    GetPath(G, i, k, path, cnt, dist, way);
    path[cnt++] = k;
    GetPath(G, k, j, path, cnt, dist, way);
}

void PrintRoad (Graph G, int dist[MAX_VERTEX_NUM][MAX_VERTEX_NUM], int way[MAX_VERTEX_NUM][MAX_VERTEX_NUM])
{
    char *e1 = (char *) malloc (sizeof(char)*MAX_NAME_LEN);
    char *e2 = (char *) malloc (sizeof(char)*MAX_NAME_LEN);
    int s1, s2;
    printf("请输入您所在地\n");
    fflush(stdin);
    gets(e1);
    FindVex(G, e1, s1);
    printf("请输入您要去的地方\n");
    fflush(stdin);
    gets(e2);
    FindVex(G, e2, s2);
    int cnt = 0;
    int path[MAX_VERTEX_NUM];
    //初始化
    for(int i=0; i<G.vexnum; i++) path[i] = -1;
    GetPath(G, s1, s2, path, cnt, dist, way);
    //计数打印
    int ind = 0;
    printf("最短路径是：%s  ",G.vexs[s1].name);
    while(path[ind]!=-1)
    {
        printf("%s  ",G.vexs[path[ind++]].name);
    }
    printf("%s\n总计路程%d米\n", G.vexs[s2].name, dist[s1][s2]);
}

int main()
{
    Graph G;
    int dist[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int way[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int choice;
    while(1)
    {
        printf("------暨南大学导游系统 prod.by 范昊翔2019051364------\n");
        printf("1.初始化信息 2.景点列表 3.景点简介 4.导航程序 0.退出\n");
        scanf("%d", &choice);
        switch (choice)
        {
            case 0: exit(-1);
            case 1:
                    {
                        InitGraph(G);
                        ShortestRoad(G, dist, way);
                    }
                    break;
            case 2: SceneryList(G);
                    break;
            case 3: InfoProvider(G);
                    break;
            case 4: PrintRoad (G, dist, way);
                    break;
            default:
                    break;
        }
    }
    return 0;
}

//debugged,Nov.20th,11:30