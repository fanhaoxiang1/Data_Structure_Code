#include <stdio.h>
#include <stdlib.h>

typedef struct BiTNode
{
    BiTNode *lchild;
    BiTNode *rchild;
    int data; 
}BiTNode, *BiTree;

int BSTSearch (BiTree T, int num, BiTree &p)//查找到了返回1，并且修改指针p到找到的结点
//没查找到返回0，并且指针p指向其双亲结点。在函数外，初始记得让p指向NULL；
{
    if (!T)
    {
        return 0;
    }//此时，若没有结点，p已经停留在上一层中，即他们的双亲结点。
    else if (T==NULL || T->data==num)
    {
        p = T;
        return 1;
    } 
    else if (num>T->data) return BSTSearch(T->rchild, num, p);
    else return BSTSearch(T->lchild, num, p);
}

void BSTAdd (BiTree T, int num)
{
    BiTree p = NULL;
    int result = BSTSearch(T, num, p);
    if (result==1) return;
    BiTree q = (BiTree) malloc (sizeof(BiTNode));
    q->data = num;
    q->lchild = NULL;
    q->rchild = NULL;
    if (num<p->data) p->lchild = q;
    else p->rchild = q;
    return;
}

int BSTDelete (BiTree &p, int num)//一开始在主函数中应该让p指向T
//这个算法和需要替换点的双亲结点无关，为了保证双亲结点和被删除的结点之间的关系，应该保证p的地址不变
//这是一个牛批的思想，被删除结点的双亲结点f->address 先用p=address(来自于被删除结点)，在神不知鬼不觉的将p->lchild或者p->rchild接上去