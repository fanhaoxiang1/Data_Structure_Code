#include <stdio.h>
#include <stdlib.h>
#define LIST_INCREMENT 10
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define DEFAULT 1
typedef int Status;

typedef struct BiNode//一定要注意检查别人的代码和我的结构体是否统一，记得删掉
{
    int data;
    struct BiNode *lchild;
    struct BiNode *rchild;
}BiNode, *BiTree;

typedef BiTree ElemType;


typedef struct LNode
{
    ElemType data;
    struct LNode *next;
}LNode, *LinkList;


Status InsertTree (BiTree &T, int x)//这个是测试时用的，一定要删除。
{
    T = (BiTree) malloc (sizeof(BiNode));
    T->data = x;
    T->lchild = NULL;
    T->rchild = NULL;
    return OK;
}

Status InitLinkList (LinkList &L)//初始化链表
{
    L = (LinkList) malloc (sizeof(ElemType));
    L->next = NULL;
    return OK;
}

Status ListInsert (LinkList &L, int idx, ElemType e)//在第idx的位置插入元素e
{
    LNode *node;
    node = (LinkList) malloc (sizeof(ElemType));
    node->data = e;
    LNode *p = L;
    LNode *q;
    int i = 1;
    while(i<idx)
    {
        p = p->next;
        i++;
    }
    q = p->next;
    node->next = q;
    p->next = node;
    return OK;
}

Status ListDelete (LinkList &L, int idx)//删除第idx个元素
{
    LNode *p = L;
    int i = 1;
    while(i<idx)
    {
        p = p->next;
        i++;
    }
    LNode *q = p->next;
    p->next = q->next;
    //free(q);
    return OK;
}

Status ListSearch (LinkList &L, int &idx, BiTree &ptr, int x)//寻找链表中指定值x指针的结点，返回其本身和它所在的链表位置idx
{
    LNode *p = L->next;
    int i = 1;
    while(p!=NULL)
    {
        if (p->data->data == x) break;
        p = p->next;
        i++;
    }
    ptr = p->data;
    idx = i;
    return OK;
}

Status PrintLinkList (LinkList &L)//遍历打印整个链表所指向元素的data
{
    LNode *p = L->next;
    printf("(");
    while (p)
    {
        printf(" %d",p->data->data);
        p = p->next;
    }
    printf(" )\n");
    return OK;
}

//以下为测试功能的main函数，可以删除。
int main()
{
    LinkList L;
    BiTree a,b,c,d,e;
    int idx[2];
    InitLinkList(L);
    InsertTree(a,1);
    InsertTree(b,2);
    InsertTree(c,5);
    InsertTree(d,16);
    InsertTree(e,35);
    ListInsert(L,1,a);
    ListInsert(L,2,b);
    ListInsert(L,3,c);
    ListInsert(L,4,d);
    ListDelete(L,1);
    ListDelete(L,3);
    ListSearch(L,idx[0],2);
    ListSearch(L,idx[1],5);
    PrintLinkList(L);
}