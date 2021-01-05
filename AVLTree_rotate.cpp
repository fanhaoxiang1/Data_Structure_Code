#include <stdio.h>
#include <stdlib.h>
#define LH (+1)
#define EH (0)
#define RH (-1)
#define INVALID (-2)
typedef char* ElemType;
typedef int Status;

typedef struct BSTNode
{
    ElemType data;
    int bf;//平衡因子
    struct BSTNode *lchild, *rchild;
}BSTNode, *BSTree;

int EQ (ElemType e1, ElemType e2)
{
    if (e1==e2) return 1;
    else return 0;
}

int LT (ElemType e1, ElemType e2)
{
    if (e1<e2) return 1;
    else return 0;
}

int GT (ElemType e1, ElemType e2)
{
    if (e1>e2) return 1;
    else return 0;
}

void R_Rotate (BSTree &p)//p最后返回的是新的根节点
{
    BSTree lc = p->lchild;
    p->lchild = lc->rchild;
    lc->rchild = p;
    p = lc;
}

void L_Rotate (BSTree &p)
{
    BSTree lc = p->rchild;
    p->rchild = lc->lchild;
    lc->lchild = p;
    p = lc;
}

void LeftBalance (BSTree &T)//判断是ll还是lr情况
{
    BSTree lc = T->lchild;
    switch (lc->bf)
    {
        case LH: T->bf = EH; lc->bf = EH; R_Rotate(T); break;
        //由于其他结点与其子节点的先后关系都没有发生改变，所以并不会改变顺序
        case RH: BSTree rd = lc->rchild;//要做两件事：修改T和它左孩子的bf，先左旋，后右旋
        switch (rd->bf)//
        {
            case LH: T->bf = RH; lc->bf = EH; break;//瓜分rd这棵树，rd->l给lc,ld->r给T
            case EH: T->bf = EH; lc->bf = EH; break;
            case RH: T->bf = EH; lc->bf = LH; break;
        }
        L_Rotate (T->lchild);
        R_Rotate (T);
    }
}

void RightBalance (BSTree &T)//判断是ll还是lr情况
{
    BSTree rc = T->rchild;
    switch (rc->bf)
    {
        case RH: T->bf = EH; rc->bf = EH; L_Rotate(T); break;
        case LH: BSTree ld = rc->lchild;
        switch (ld->bf)
        {
            case RH: T->bf = LH; rc->bf = EH; break;
            case EH: T->bf = EH; rc->bf = EH; break;
            case LH: T->bf = EH; rc->bf = RH; break;
        }
        R_Rotate (T->rchild);
        L_Rotate (T);
    }
}

Status InsertAVL (BSTree &T, ElemType e, int &taller)//taller反映长高与否，Status方便递归调用，以判断终止条件
{
    if (!T)
    {
        BSTree T = (BSTree) malloc (sizeof(BSTNode));
        T->data = e;
        T->lchild = NULL;
        T->rchild = NULL;
        T->bf = EH;
        taller = 1;
        return 1;
    }//空树的构建
    else
    {
        if (EQ(e, T->data))//不会遍历到新插入的结点上的
        {
            taller = 0;
            return 0;
        }//如果已经存在，则不插入
        if (LT(e, T->data))
        {
            if (!InsertAVL (T->lchild, e, taller)) return 0;//递归插入左子树，如果插入了，则返回上一层递归。上一层递归之前的递归将不会再return 1
            //换句话说，return 1代表着搜索过程的终结，检查平衡过程的开始。
            if (taller)//注意taller和bf的区别，也要注意taller和return值的区别
            //bf反映了树目前是否平衡，return反映了是否已经插入操作完成。
            //taller提供了跳出递归的第二种方式
            //如：进行了n层递归，在第n层递归完成了插入，taller要set为1。跳入第n-1层递归进行平衡判断操作（就是接下来的）
            //剩下的n-1层都是与插入结点相关的祖先（以及双亲）结点，需要依次判断平衡是否被破坏
            //如果被破坏了，下层的taller肯定改变，从而影响上层结点
            {
                switch (T->bf)
                {
                    case LH: LeftBalance(T); taller = 0; break;//原本bf=+1,现在变成+2，左右失衡，进行左平衡操作，之后后左右子树等高
                    case EH: T->bf = LH; taller = 1; break; //原本等高，现在左边变高
                    case RH: T->bf = EH; taller = 0; break; //原本右子树高，现在左子树+1，变成等高
                }
            }
        }
        else
        {
            if (!InsertAVL (T->rchild, e, taller)) return 0;
            if (taller)
            {
                switch (T->bf)
                {
                    case LH: T->bf = EH; taller = 0; break;
                    case EH: T->bf = RH; taller = 1; break;
                    case RH: RightBalance(T); taller = 0; break;
                }
            }
        }
    }
    return 1;
}

Status DeleteAVL (BSTree &T, ElemType e, int &shorter)
{
    if (!T) 
    {
        shorter = 0;
        return 0;
    }//找到尽头也没找到，直接解除递归
    else
    {
        if (EQ(e, T->data))//要找它左子树的最右边代替它
        {
            shorter = 0;
            if(!T->lchild && !T->rchild)//左右都没有结点，也就是叶子结点，结束这次迭代后把他去掉
            {
                T->bf = INVALID;
                return -1;
            } 
            if(!T->lchild)//没有左节点，让data为下一个节点的data，并且继承下个结点的左右子树
            {
                T->data = T->rchild->data;
                T->lchild = T->rchild->lchild;
                T->rchild = T->rchild->rchild;
                return 1;
            }
            if(!T->rchild)//同上理
            {
                T->data = T->lchild->data;
                T->lchild = T->lchild->lchild;
                T->rchild = T->lchild->rchild;
                return 1;
            }
            else//左右都有结点，找中序遍历他的前一个结点，即左子树的最右结点的data赋予，然后继续调用删除程序，传入T->lchild和T原本的值
            {
                BSTree pnt = T->lchild;
                while(!pnt->rchild)
                {
                    pnt = pnt->rchild;
                }                   
                ElemType tmp = T->data;
                T->data = pnt->data;
                pnt->data = tmp;
                DeleteAVL(T->lchild, T->data, shorter);
                return 1;
            }
            
        }//如果已经存在，则不插入
        if (LT(e, T->data))
        {
            int k = DeleteAVL (T->lchild, e, shorter);
            if (k==-1)//倒数第二层递归，让此结点“结扎”
            {
                if(T->lchild->bf == -2) //判别是左节点还是右节点被切断
                {
                    free(T->lchild);
                    T->lchild = NULL;
                    return 1;
                }
                if(T->rchild->bf == -2) 
                {
                    free(T->rchild);
                    T->rchild = NULL;
                    return 1;
                }
                shorter = 1;
            }
            if (!k) return 0;//return 0:不再执行下面的过程，一般认为
            if (shorter)
            {
                switch (T->bf)
                {
                    case LH: T->bf = EH; shorter = 0; break;
                    case EH: T->bf = RH; shorter = 1; break; 
                    case RH: RightBalance(T); T->bf = EH; shorter = 0; break; 
                }
            }
        }
        else
        {
            int k = DeleteAVL (T->lchild, e, shorter);
            if (k==-1)//倒数第二层递归，让此结点“结扎”
            {
                if(T->lchild->bf == -2) //判别是左节点还是右节点被切断
                {
                    free(T->lchild);
                    T->lchild = NULL;
                    return 1;
                }
                if(T->rchild->bf == -2) 
                {
                    free(T->rchild);
                    T->rchild = NULL;
                    return 1;
                }
                shorter = 1;
            }
            if (!k) return 0;//递归删除左子树，如果删除了，则返回上一层递归。上一层递归将不再return。
            if (shorter)
            {
                switch (T->bf)
                {
                    case LH: LeftBalance(T); T->bf = EH; shorter = 0; break;
                    case EH: T->bf = LH; shorter = 1; break;
                    case RH: T->bf = EH; shorter = 0; break;
                }
            }
        }
    }
    return 1;
}