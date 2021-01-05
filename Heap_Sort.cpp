#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100

typedef int RcdType;
typedef struct
{
    RcdType r[MAXSIZE+1];
    int length; 
}SqList;
typedef SqList HeapType;

void Swap (RcdType i, RcdType j)
{
    int tmp = i;
    i = j;
    j = tmp;
}

int LT (RcdType a, RcdType b)
{
    if (a<b) return 1;
    else return 0;
}

int GT (RcdType a, RcdType b)
{
    if (a>b) return 1;
    else return 0;
}

void HeapAdjust (HeapType &H, int s, int m)//本函数用来调整s到m的堆
{
    int rc = H.r[s];
    for (int j=2*s; j<m; j*=2)//沿着s的子树开始调整
    {
        if (j<m && LT(H.r[j], H.r[j+1])) j++;
        if (!LT(rc, H.r[j])) break;
        H.r[s] = H.r[j];
        s = j;
    }
    H.r[s] = rc;
}

void HeapSort (HeapType &H) //构造大顶堆
{
    for (int i=H.length/2; i>0; i--)//从最底下的双亲结点开始制造堆
    {
        HeapAdjust (H, i, H.length);
    }
    for (int i=H.length; i>1; i--)
    {
        Swap (H.r[1], H.r[i-1]);
        HeapAdjust(H, 1, i-1);
    }
}
int main()
{

}