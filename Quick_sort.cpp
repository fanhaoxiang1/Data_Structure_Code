#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100

typedef int RcdType;
typedef struct
{
    RcdType r[MAXSIZE+1];
    int length; 
}SqList;

void Swap (RcdType i, RcdType j)
{
    int tmp = i;
    i = j;
    j = tmp;
}

int Partition (SqList &L, int low, int high)
{
    while (low<high)
    {
        L.r[0] = L.r[low];
        while (low<high && L.r[0]<=L.r[high])
        {
            high--;
        }
        Swap(L.r[low], L.r[high]);
        while (low<high && L.r[0]>=L.r[low])
        {
            low++;
        }
        Swap(L.r[high], L.r[low]);   
    }
    L.r[low] = L.r[0];
    return low;
}

void QSort (SqList &L, int low, int high)
{
    if (low < high)
    {
        int pivotloc = Partition (L, low, high);
        QSort(L, low, pivotloc-1);
        QSort(L, pivotloc+1, high);
    }
}