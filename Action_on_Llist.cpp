#include <stdio.h>
#include <stdlib.h>
#define LIST_INIT_SIZE 10
#define LIST_INCREMENT 10
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define DEFAULT 1
typedef int Status;
typedef int ElemType;

typedef struct SqList
{
    ElemType *elem;
    int length;
    int listsize;
}SqList;

Status SizeIncre(SqList &L)
{
    L.elem = (ElemType *)realloc(L.elem,(L.listsize + LIST_INCREMENT) * sizeof(ElemType));
    L.listsize += LIST_INCREMENT;
    if (!L.elem) exit(OVERFLOW);//防止数组过大
    return OK;
}

Status getSqlist(SqList L)
{
    int i = 0;
    printf("[ ");
    while(i<L.length)
    {
        printf("%d ",L.elem[i]);
        i++;
    }
    printf("]");
    return OK;
}

Status InitSqListByAnArray(SqList &L,ElemType array[], int arraysize)
{
    L.elem = (ElemType *) malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (!L.elem) exit(OVERFLOW);
    L.listsize = LIST_INIT_SIZE;
    L.length = 0;
    int p = 0;
    //printf("%d",arraysize);
    while (L.length + arraysize > L.listsize)
    {
        SizeIncre(L);
    }
    while (p<arraysize)
    {
        L.elem[p]= array[p];
        p++;
    }//用数组给顺序表初始化
    L.length += arraysize;
    //SizeIncre(L);
    return OK;
}

Status InsertSqList(SqList &L,ElemType a, ElemType x, ElemType y)
{
    if(L.length >= L.listsize) SizeIncre(L);
    int p = 0;
    while (L.elem[p]!=x || L.elem[p+1]!=y && p<L.length)
    {
        p++;
    }
    if (p>=L.length) exit(ERROR);
    int q = L.length;
    while(q>p)
    {
        L.elem[q] = L.elem[q-1];
        q--;
    }
    L.elem[p+1] = a;
    L.length++;
    return OK;
}

Status DeleteSqList(SqList &L, int i)
{
    int p = i;
    while(p<=L.length)
    {
        L.elem[p-1] = L.elem[p];
        p++;
    }
    L.length--;
    return OK;
}

typedef struct LNode
{
    ElemType data;
    struct LNode *next;
}LNode, *Linklist;

Status GetLinklist (Linklist L)
{
    LNode *p = L->next;
    printf("[ ");
    while (p!= NULL)
    {
        printf("%d ",p->data);
        p = p->next;
    }
    printf("]");
}

Status AddFirst (Linklist &L, ElemType x)
{
    LNode *Node;
    Node = (LNode*)malloc(sizeof(LNode));
    Node->data = x;
    Node->next = L->next;
    L->next = Node;
    return OK;
}

Status InitLlistbyArray (Linklist &L, ElemType array[],int length)
{
    while (length>0)
    {
        AddFirst(L,array[--length]);
    }
    return OK;
}

Status InsertLinklist (Linklist &L, ElemType a, ElemType x, ElemType y)
{
    LNode *p = L;
    LNode *q = L->next;
    while(p->data != x || q->data != y && q->next !=NULL)
    {
        p = p->next;
        q = q->next;
    }
    if (p->next = NULL) exit(ERROR);
    Linklist Node;
    Node = (Linklist)malloc(sizeof(LNode));
    Node->data = a;
    Node->next = q;
    p->next = Node;
    return OK;
}

Status DeleteLinklist (Linklist &L, int i)
{
    LNode *p = L;
    int j = 1;
    while(j<i)
    {
        p = p->next;
        j++;
    }
    LNode *q = p->next;
    p->next = p->next->next;
    free(q);
    return OK;
}

int main()
{
    ElemType arr[4] = {2,3,4,5};
    SqList L1;
    int as = sizeof(arr)/sizeof(ElemType);
    InitSqListByAnArray(L1,arr,as);
    getSqlist(L1);
    InsertSqList(L1,9,4,5);
    getSqlist(L1);
    DeleteSqList(L1,3);
    getSqlist(L1);
    printf("\n");
    LNode head = {0,NULL};
    Linklist L2 = &head;
    InitLlistbyArray(L2,arr,as);
    GetLinklist(L2);
    InsertLinklist(L2,9,4,5);
    GetLinklist(L2);
    DeleteLinklist(L2,3);
    GetLinklist(L2);
    printf("范昊翔 2019051364");
    system("pause");
    return 0;
}