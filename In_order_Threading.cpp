#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;
typedef int TElemType;

typedef struct BiThrNode
{
    TElemType data;
    struct BiThrNode *lchild, *rchild;
    int LTag, RTag;
}BiThrNode, *BiThrTree;

Status InThreading(BiThrTree &p, BiThrNode *pre)//递归方法
{
    if(p)
    {
        InThreading(p->lchild, pre);
        if (!p->lchild) //任务1：判断当前结点有没有左孩子
        {
            p->LTag = 1;
            p->lchild = pre;
        }
        if (!pre->rchild)//任务2：判断先前结点有没有右孩子
        {
            pre->LTag = 1;
            pre->rchild = p;
        }
        pre = p;
        InThreading(p->rchild, pre);
    }
    return 0;
}



Status InOrderThreading (BiThrTree &Thrt, BiThrTree T)
{
    if(!(Thrt = (BiThrTree)malloc(sizeof(BiThrNode)))) return ERROR;
    Thrt->LTag = 0; Thrt->lchild = T;//左指针指向树
    Thrt->RTag = 1; Thrt->rchild = Thrt;//右指针回指
    BiThrNode *pre = Thrt;//pre要记录前一个结点
    InThreading(T, pre);
    pre->RTag = 1;
    pre->rchild = Thrt;
    Thrt->rchild = pre;//规定头结点的后继要指向该节点
    return OK;
}