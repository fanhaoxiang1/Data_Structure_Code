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
}Graph;//������һ������ͼ

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
    printf("%s��û��ƥ���\n", e);
    system("pause");
    exit(-1);
}
//ͳһ��׼���Լ����Լ��ľ�����INF
void InitGraph (Graph &G)
{
    printf("�����뾰����\n");
    scanf("%d",&G.vexnum);
    for (int i=0; i<G.vexnum; i++)
    {
        printf("�������%d��������\n",i+1);
        fflush(stdin);
        G.vexs[i].name = (char *) malloc (sizeof(char)*MAX_NAME_LEN);
        G.vexs[i].info = (char *) malloc (sizeof(char)*MAX_INFO_LEN);
        gets(G.vexs[i].name);
        printf("������%s�ľ�����Ϣ\n",G.vexs[i].name);
        fflush(stdin);
        gets(G.vexs[i].info);
    }//��ʼ��������Ϣ
    for (int i=0; i<G.vexnum; i++)
    {
        for (int j=0; j<G.vexnum; j++)
        {
            G.arcs[i][j].weight = INF;
        }
    }//��ʼ�������ڽӾ���
    printf("������ߵ�����\n");
    scanf("%d",&G.arcnum);
    for (int i=0; i<G.arcnum; i++)
    {
        printf("�������%d���ߵ���������\n",i+1);
        char *e1 = (char *) malloc (sizeof(char)*MAX_NAME_LEN);
        char *e2 = (char *) malloc (sizeof(char)*MAX_NAME_LEN);;
        fflush(stdin);
        gets(e1);
        gets(e2);
        int s1, s2;
        FindVex (G, e1, s1); FindVex(G, e2, s2);
        printf("�����������ߵ�Ȩֵ\n");
        scanf("%d",&G.arcs[s1][s2].weight);
        G.arcs[s2][s1].weight = G.arcs[s1][s2].weight;
    }
}//��ʼ�����

void SceneryList (Graph G)
{
    printf("ѧУ�����¾���\n");
    int i = 0;
    while (i<G.vexnum)
    {
        printf("%d %s\n", i+1, G.vexs[i].name);
        i++;
    }
}

void InfoProvider (Graph G)
{
    printf("����Ҫ�鿴�ĸ��������Ϣ��\n");
    fflush(stdin);
    char *temp = (char *) malloc (sizeof(char)*MAX_NAME_LEN);
    gets(temp);
    //���ǵ��û�������������Ҳ����������
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
            //��·����-1,û·��������������0
            if (G.arcs[i][j].weight<INF) way[i][j]=-1;
            else way[i][j] = 0;
        }
    }//��ʼ��
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
    //�������������ǲ���ͨ��״̬֤���Ѿ����������н�㣨�����ϳ���
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
    printf("�����������ڵ�\n");
    fflush(stdin);
    gets(e1);
    FindVex(G, e1, s1);
    printf("��������Ҫȥ�ĵط�\n");
    fflush(stdin);
    gets(e2);
    FindVex(G, e2, s2);
    int cnt = 0;
    int path[MAX_VERTEX_NUM];
    //��ʼ��
    for(int i=0; i<G.vexnum; i++) path[i] = -1;
    GetPath(G, s1, s2, path, cnt, dist, way);
    //������ӡ
    int ind = 0;
    printf("���·���ǣ�%s  ",G.vexs[s1].name);
    while(path[ind]!=-1)
    {
        printf("%s  ",G.vexs[path[ind++]].name);
    }
    printf("%s\n�ܼ�·��%d��\n", G.vexs[s2].name, dist[s1][s2]);
}

int main()
{
    Graph G;
    int dist[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int way[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int choice;
    while(1)
    {
        printf("------���ϴ�ѧ����ϵͳ prod.by �����2019051364------\n");
        printf("1.��ʼ����Ϣ 2.�����б� 3.������ 4.�������� 0.�˳�\n");
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