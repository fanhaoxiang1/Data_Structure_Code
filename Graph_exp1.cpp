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
}Graph;//������һ������ͼ

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
    printf("%c��û��ƥ���\n", e);
    system("pause");
    exit(-1);
}
//degbuged,10:54

void InitGraph (Graph &G)
{
    printf("����������\n");
    scanf("%d",&G.vexnum);
    printf("���������ǵ���Ϣ\n");
    char *temp;
    temp = (char*) malloc (sizeof(char)*G.vexnum);
    scanf("%s",temp);
    for (int i=0; i<G.vexnum; i++) G.vexs[i] = temp[i];//��ʼ������j
    for (int i=0; i<G.vexnum; i++)
    {
        for (int j=0; j<G.vexnum; j++)
        {
            G.arcs[i][j].weight = INF;
        }
    }//��ʼ�������ڽӾ���
    printf("����������ߵ�����\n");
    scanf("%d",&G.arcnum);
    for (int i=0; i<G.arcnum; i++)
    {
        printf("�������%d���ߵ������յ�\n",i+1);
        char e1, e2;
        fflush(stdin);
        scanf("%c%c", &e1, &e2);//����Ҫ�����飬��֪���в���
        int s1, s2;
        FindVex (G, e1, s1); FindVex(G, e2, s2);
        printf("�����������ߵ�Ȩֵ\n");
        scanf("%d",&G.arcs[s1][s2].weight);
    }
}
//debugged,10:54

void FindShortestRoad (Graph G, char v0, int P[], int D[])
//P��¼��������·�����������ǵó�ʼ��ΪINF��DΪ�����������ǵó�ʼ��ΪINF
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
    for (int i=0; i<G.vexnum; i++)//��ʼ��
    {
        if (G.arcs[v][i].weight<INF)
        {
            D[i] = G.arcs[v][i].weight;
            P[i] = v;
        }
    }
    final[v] = 1;
    for (int i=1; i<G.vexnum; i++)//ÿ���Ҹ���С�ģ�ֱ������ȫ��Ϊֹ
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
}//P[w]��¼��������һ������
//debugged,11:35

void PrintRoad (Graph G, char e,int P[], int D[])
{
    int v;
    FindVex(G, e, v);
    for (int i=0; i<G.vexnum; i++)//��ʼ��ӡ���·�����ӵ�1����ʼ
    {
        if (i==v) printf("��%c������ľ���Ϊ0\n", e);
        else if(D[i]>=INF) printf("��%c����%cû��·����\n", e, G.vexs[i]);
        else
        {
            printf("��%c����%c�ľ���Ϊ%d\n",G.vexs[v],G.vexs[i],D[i]);
            printf("��·��Ϊ\n");
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
    printf("��Ҫ���ĸ��㵽����������·����\n");
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