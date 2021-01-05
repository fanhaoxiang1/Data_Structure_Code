#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define N 1000
#define INF INT_MAX
#define MAX_VERTEX_NUM 20
typedef int ElemType;
typedef int VexNode;

typedef struct QNode
{
    int data;
    QNode *next ;
}QNode, *Queue;

void EnQueue (Queue &Q, int i);
void DeQueue (Queue &Q, int &i);
int IsEmpty (Queue &Q);
typedef struct
{
    VexNode ArcBox[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int vexnum, arcnum;
}Graph;

//DFS判断有无回路
void DFS (VexNode v ,int visited[], Graph G, void *Visit(VexNode))
{
    Visit(v);
    visited[v] += 1;
    for (int i=0; i<G.vexnum; i++)
    {
        visited[i] += 1;
        if (G.ArcBox[v][i]!=0&&G.ArcBox[v][i]!=INF&&!visited[i])
        DFS(i, visited, G, Visit);
    }
    for (int i=0; i<=G.arcnum; i++)
    {
        if (visited[i]>2)
        printf("有回路");
    }
}

void BFS (VexNode v, int visited[], Graph G, void *Visit(VexNode), Queue &Q)
{
    Visit(v);
    visited[v] = 1;
    while (!IsEmpty(Q))
    {
        DeQueue(Q,v);
        for (int i=0; i<G.vexnum; i++)
        {
            if (G.ArcBox[v][i]!=0&&G.ArcBox[v][i]!=INF&&!visited[i])
            Visit(v);
            EnQueue(Q, v);
        }
    }
}