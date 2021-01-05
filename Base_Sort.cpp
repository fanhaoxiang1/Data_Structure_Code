#include <stdio.h>
#include <stdlib.h>
#define MAX_NUM_OF_KEY 4
#define RADIX 10
#define MAX_SPACE 10000
typedef int KeysType;

typedef struct 
{
    KeysType keys[MAX_NUM_OF_KEY];
    int next;
}SLCell;
typedef struct 
{
    SLCell r[MAX_SPACE];
    int keynum;
    int recnum;
}SLList;

typedef int ArrType[RADIX];

void Distribute (SLList &L, int i, ArrType &f, ArrType &e)
{
    for (int j=0; j<RADIX; ++j)
    {
        f[j] = 0;
        e[j] = 0;
    }

    for (int p = L.r[0].next; p; p=L.r[p].next)
    {
        if (!f[L.r[p].keys[i]]) f[L.r[p].keys[i]] = p;
        int q = e[L.r[p].keys[i]];
        e[L.r[p].keys[i]] = p;
        L.r[q].next = p;
    }
}

void Collect (SLList &L, int i, ArrType f, ArrType e)
{
    int j;
    for (j=0; !f[j]; j++);//找第一个非空结点
    L.r[0].next = f[j];
    int t = e[j];
    while (j<RADIX)
    {
        for (++j; j<RADIX-1 && !f[j]; j++);
        if (f[j]) 
        {
            L.r[t].next = f[j];
            t = e[j];
        }
    }
    L.r[t].next = 0;    
}

void RadixSort (SLList &L)
{
    ArrType f;
    ArrType e;
    for (int i=0; i<L.recnum; i++) L.r[i].next = i+1;
    L.r[L.recnum].next = 0;
    for (int i=0; i<L.keynum; ++i)
    {
        Distribute(L, i, f, e);
        Collect (L, i, f, e);
    }
}
