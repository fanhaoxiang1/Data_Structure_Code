#include <stdio.h>
#include <stdlib.h>
#define LIST_INIT_SIZE 3
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;
typedef int Elemtype;
typedef Elemtype *Triplet;

Status InitTriplet(Triplet &T, int v1, int v2,int v3)
{
    T = (Elemtype*)malloc(LIST_INIT_SIZE * sizeof(Elemtype));
    if (!T) exit(OVERFLOW);
    T[0] = v1;
    T[1] = v2;
    T[2] = v3;
    printf("初始化完成！元组为%d,%d,%d\n",T[0],T[1],T[2]);
    return OK;
}

Status Get(Triplet T)
{
    printf("T[0]=%d, T[1]=%d, T[2]=%d\n",T[0],T[1],T[2]);
    return OK;
}

Status Put(Triplet &T, int i, int v) //将第i个元素存为v
{
    if (i<1||i>3)
    return ERROR;
    else switch (i)
    {
    case 1:
        T[0] = v;
        break;
    case 2:
        T[1] = v;
        break;
    default:
        T[2] = v;
    }
    return OK;
}

Status Max(Triplet T, Elemtype &e)
{
    e = T[0];
    if (e<T[1])
    e = T[1];
    if (e<T[2])
    e = T[2];
    printf("最大值是%d\n",e);
    return OK;
}

Status DestroyTriplet(Triplet &T)
{
    free(T);
    return OK;
}

int main()
{
    Triplet t1;
    Elemtype v1, v2, v3;
    printf("请依次输入三个数以初始化\n");
    scanf("%d%d%d",&v1, &v2, &v3);
    InitTriplet(t1,v1,v2,v3);
    Get(t1);
    Elemtype c,v;
    printf("需要改变第几个数为何值？\n");
    scanf("%d%d",&c,&v);
    Put(t1,c,v);
    Get(t1);
    Elemtype e;
    Max(t1,e);
    DestroyTriplet(t1);
    system("pause");
    return 0;
}