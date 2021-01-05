#include <stdio.h>
#include <stdlib.h>

typedef struct TNode
{
    int data;
    TNode *lchild;
    TNode *rchild;
}TNode, *BTree;
