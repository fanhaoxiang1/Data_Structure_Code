#include <stdio.h>
#include <stdlib.h>
#define STACK_INIT_SIZE 10
#define STACK_INCREMENT 10
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define DEFAULT 1
typedef int Status;
typedef int ElemType;

typedef struct LNode
{
    ElemType data;
    struct LNode * next;
}LNode, *Linklist;

typedef struct LDeque
{
    LNode* rear;
}LDeque;

Status InitLDeque (LDeque &Q)
{
    LNode *tail;
    tail = (Linklist) malloc (sizeof(LNode));
    tail->data = NULL;
    tail->next = NULL;
    Q.rear = tail;
}

Status EnQueue (LDeque &Q, ElemType e)
{
    if (Q.rear->next == NULL) 
    {
        Q.rear->data = e;
        Q.rear->next = Q.rear;
        return OK;
    }
    LNode *Node;
    Node = (Linklist) malloc (sizeof(LNode));
    Node->data = e;
    Node->next = Q.rear->next;
    Q.rear->next = Node;
    Q.rear = Node;
    return OK;
}



Status DeQueue (LDeque &Q, ElemType &e)
{
    if (Q.rear->next == NULL) return ERROR;
    if (Q.rear->next == Q.rear)
    {
        e = Q.rear->data;
        Q.rear->data = NULL;
        return OK;
    }
    Linklist Node = Q.rear->next;
    e = Node->data;
    Q.rear->next = Node->next;
    free(Node);
    return OK;
}

int main()
{
    LDeque test;
    int e;
    InitLDeque(test);
    EnQueue(test, 1);
    EnQueue(test, 12);
    EnQueue(test, 15);
    EnQueue(test, 17);
    DeQueue(test,e);
    DeQueue(test,e);
    DeQueue(test,e);
    DeQueue(test,e);
    DeQueue(test,e);
}