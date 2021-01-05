#include <stdio.h>
#include <stdlib.h>
#define LIST_INIT_SIZE 2
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define DEFAULT 1
typedef int Status;
typedef int ElemType;

typedef struct BiNode
{
    ElemType data;
    struct BiNode *lchild;
    struct BiNode *rchild;
}BiNode, *BiTree;

typedef struct Stack
{}Stack;
Status InitStack(Stack &S);
Status Push(Stack &S);
Status Pop(Stack &S);
Status PrintElement(ElemType e)
{
    printf("%d",e);
    return OK;
}

Status PreOrderTraverse(BiTree T, Status *Visit(ElemType e))
{
    BiTree p;
    p = T;
    Visit(p->data);
    while(p->lchild) PreOrderTraverse(p, Visit);
    while(p->rchild) PreOrderTraverse(p, Visit);
    return OK;
}

Status PreOrderTraverse2 (BiTree T, Status *Visit(ElemType e))
{
    Stack S;
    InitStack(S);
    while(!T||S)
    {

    }
}