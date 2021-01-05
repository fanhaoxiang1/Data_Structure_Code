#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX_NUM 20
typedef int VertexType;

typedef struct ArcBox
{
    int index;
    ArcBox *next;
}ArcBox;

typedef struct VexNode
{
    VertexType data;
    ArcBox *next;
}Graph[MAX_VERTEX_NUM];

int FindVex (Graph G, int n, int e)
{
    for (int i=0; i<n; i++)
    {
        if (G[i].data == e) return G[i].data;
    }
    return -1;
}

int InitGraph (Graph G, int n)
{
    printf("请依次输入n个头节点");
    for (int i=0; i<n; i++)
    {
        scanf("%d", &G[i].data);
        G[i].next = NULL;
    }//初始化头节点
    while(1)
    {
        printf("请输入边");
        VertexType v1,v2;
        scanf("%d%d", &v1, &v2);
        if (v1||v2) return 0;//输入0结束
        int s1, s2;
        s1 = FindVex (G, n, v1);
        s2 = FindVex (G, n, v2);
        ArcBox *temp = G[s1].next;
        ArcBox *arc = (ArcBox *) malloc (sizeof(ArcBox));
        arc->next = temp;
        arc->index = s2;
        G[s1].next = arc;
    }
    return 1;
}