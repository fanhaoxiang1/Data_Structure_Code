Status InsertInOrder(sqlist &L, Elemtype e)
{
    if (L.listsize < L.length + 1)
    {
        newbase = (Elemtype *)realloc(L.elem,
        (L.listsize + LISTINCREMENT) * sizeof(Elemtype));
        L.elem = newbase;
        L.listsize += LISTINCREMENT;
    }
    Elemtype *p = S.elem[0];
    if (!newbase) exit(OVERFLOW);
    int i = 0, j = L.length - 1;
    while(L.elem[i]<e)
    {
        ++i;
    }
    //我要插入的位置，是第i个元素
    while(j>i)
    {
        S.elem[j+1] = S.elem[j--];
    }
    //要移动i后面的所有元素,从最后开始移动
    S.elem[i] = e;
    S.length++;
    return OK;
}

Status DeleteInRange (Llist &L, Elemtype x, Elemtype y)//x-y中链表删除元素（看错题QAQ）
{
    //带有头结点的链表
    Node *p_prior = L;//记录p的前一个结点，方便连接链表
    Node *p = L.next;
    while(p || p->data < x )//防止是空链表
    {
        if (p->next=NULL) exit(ERROR);//访问到链表尾立即弹出
        p_prior = p;
        p = p->next;
    }
    Node *q_prior = p_prior->next;//需要记录q的前一个结点，方便free掉空间
    if (!p->next) 
    {
        p_prior->next = NULL;
        free(p);
        exit(OK);
    }//防止p是链表最后一个元素
    Node *q = q->next;
    while(q || q->data <= y)
    {   
        free(q_prior);
        q_prior = q;
        q = q.next;
    }//p节点是需要删掉的第一个结点，q_prior是需要删掉的最后一个结点
    p_prior->next = q; 
    return OK;
}

Status DeleteRangeSqlist(sqlist &S, Elemtype x, Elemtype y)
{
    if (x>y) exit(ERROR);//确保合法
    int i = 0, j = S.length;
    while (S.elem[i]<x)
    {
        if (i==S.length-1) return OK;//到结尾都没有x，则什么都不删除
        ++i;
    }
    i = j;
    while(S.elem[j]>=x)
    {
        if (j==S.length-1)
        {
            S.length = i + 1;//调整顺序表大小，后面的全部元素删除
            return OK;
        }
        ++j;
    }
    int length_now = S.length - (j - i);//先记录下更新表后的长度
    while(j<=S.length-1)
    {
        S.elem[i] = S.elem[j++];
    }
    S.length = length_now;//更新长度
    return OK;
}

Status DeleteRangeSqlistFast(sqlist &S, Elemtype x, Elemtype y)
{
    int i = 0, j;
    while(S.elem[i]<x) ++i;//找头
    j = i + 1;
    while(j<S.length && j<=y) ++j;//找尾
    //k = i;
    while(j<S.length)//删除
    {
        S.elem[i++] = S.elem[j++];
    }
    S.length = i;
    return OK;
}

Status DelThenCat(Node *heada, Node *headb, int i, int j, int len)
{
    if(len == 0) exit(OK);
    Node *p = heada;
    Node *q = headb;
    int m = 0, n = 0;
    while (m<i && p->next!=NULL)//找到第i个元素的前一个元素
    {
        p = p->next;
    }
    while (n<i && q->next!=NULL)//找到第j个元素的前一个元素
    {
        q = q->next;
    }
    
    if (p->next == NULL || q->next == NULL) exit(ERROR);
    Node *head = p, *tail = p;
    while (len>0 && p->next !=NULL)//找到i+len-1的结点位置
    {
        tail = tail->next;
        --len;
    }
    if (p->next == NULL) exit(ERROR);
    //开始删除并且移动
    p->next = tail->next;
    tail->next = q->next;
    q->next = head;
    return OK;
}