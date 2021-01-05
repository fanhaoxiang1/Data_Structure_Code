#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LIST_INIT_SIZE 10
#define LIST_INCREMENT 10
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define DEFAULT 1
typedef int Status;

//定义车辆信息的数据结构
typedef struct Car
{
    char id[20];
    int arrive;//到达时间
    int leave;//离开时间
    int pos;//应停区域,1表示停车场，0表示便道
    int no;//位置编号
}Car;
typedef Car ElemType;

//基本部分，定义顺序栈和链式队列
typedef struct SqStack
{
    ElemType *top;
    ElemType *base;
    int stacksize;
}SqStack;

Status InitStack (SqStack &S)
{
    S.base =NULL;
    S.top = NULL;
    S.base = (ElemType *) malloc (sizeof(ElemType) * LIST_INIT_SIZE);
    if (!S.base) exit(OVERFLOW);
    S.top = S.base;
    S.stacksize = LIST_INIT_SIZE;
    return OK;
}

Status Push(SqStack &S, ElemType &e, int &index)
{
    
    if (S.top-S.base==S.stacksize){
        S.base = (ElemType *) realloc (S.base, sizeof(ElemType) * (S.stacksize+LIST_INCREMENT));
        if (!S.base) exit(OVERFLOW);
        S.top = S.base + S.stacksize;
        S.stacksize += LIST_INCREMENT;
    }
    
    *S.top++ = e;
    index = S.top - S.base;
    return OK;
}

Status Pop(SqStack &S, ElemType &e)
{
    if(S.top <= S.base) return ERROR;
    else e = *--S.top;
    return OK;
}

Status DestroyStack(SqStack &S)
{
    free(S.base);
    return OK;
}

//通过检测车牌号判断车是否在停车场内
Status WhetherInStack(SqStack &S, char id1[], int &reply)
{
    int ind;//临时变量，无用
    reply = 0;//1是在，0是不在
    ElemType *p = S.base;
    while(p <= S.top)
    {
        if (strcmp(id1,p->id)==0) 
        {reply = 1; break;}
        p++;
    }
    return OK;
}

typedef struct Node
{
    ElemType data;
    struct Node *next;
}Node;

typedef struct LQueue
{
    Node *front;
    Node *rear;
    int length;
}LQueue;

Status InitLQueue (LQueue &L)
{
    L.front = (Node *) malloc (sizeof(ElemType));
    if (!L.front) exit(OVERFLOW);
    L.rear = L.front;
    L.front -> next = NULL;
    L.length = 0;
    return OK;
}

Status EnQueue (LQueue &L, ElemType &e, int &index)
{
    Node *node;
    node = (Node*) malloc (sizeof(ElemType));
    if (!node) exit(OVERFLOW);
    node->data = e;
    node->next = NULL;
    L.rear -> next = node;
    L.rear = node;
    index = ++L.length;
    return OK;
}

Status Dequeue (LQueue &L, ElemType &e)
{
    if (L.front == L.rear) return ERROR;
    Node *node = L.front->next;
    e = node->data;
    L.front ->next = node->next;
    if (L.rear == node) L.rear = L.front;
    L.length --;
    //free(node);
    return OK;
}

Status DestroyQueue (LQueue &L)
{
    while(L.front)
    {
        L.rear = L.front->next;
        free(L.front);
        L.front = L.rear;
    }
    return OK;
}

//进场流程处理
Status CarIn (SqStack &S, LQueue &Q, int n, Car &car)
{
    printf("欢迎光临，请输入你的车牌号：\n");
    fflush(stdin);
    scanf("%s",car.id);
    printf("请输入你的到达时间\n");
    scanf("%d",&car.arrive);
    if (S.top - S.base < n) 
    {
        car.pos = 1;
        Push(S, car, car.no);
    }
    else
    {
        car.pos = 0;
        EnQueue(Q, car, car.no);
    }
    return OK;
}

//进场信息提示
Status CarInformationOut(Car &car)
{
    printf("停车位置");
    if (car.pos == 1) printf("停车场");
    else printf("便道");
    printf(" %d号位\n",car.no);
    return OK;
}

//确定了car的车牌以及出停车场时间以后，出场停车流程
Status CarOut(SqStack &park, SqStack &wait, LQueue &Q, char id1[], int out, Car &car)
{
    int index = 0, temp;//index用来记录出栈个数;temp临时变量，无用
    int i = 0;
    Car carnow = {NULL};
    while(1)//让后面的车为退出让位置
    {
        Pop(park, carnow);
        if (strcmp(id1,carnow.id)==0) break;
        Push(wait, carnow, index);
    }
    car = carnow;
    car.leave = out;
    //Push(park, carnow, temp);
    while(i<index)//重新驶入
    {
        Pop(wait, carnow);
        Push(park, carnow, temp);
        i++;
    }
    if (Q.length!=0)//让队列中第一辆车入停车场
    {
        Dequeue(Q, carnow);
        carnow.pos = 1;
        carnow.arrive = out;
        Push(park, carnow, temp);

    }
    return OK;
}

//出场信息处理
Status CarLeftInformation(SqStack &S, SqStack &wait, LQueue &Q, Car &car)
{
    char id1[20];
    int out;//出场时间
    int reply;//判断是否进入停车场
    printf("请输入你的车牌：\n");
    fflush(stdin);
    scanf("%s", id1);
    WhetherInStack(S, id1, reply);
    if (reply == 0) printf("你未进入停车场，本次停车免费。\n");
    else
    {
        printf("你什么时候离开停车场？\n");
        scanf("%d",&out);
        CarOut(S, wait, Q, id1, out, car);
        printf("你于时刻%d进入停车场，%d离开\n共计%d小时，每小时2元，应付%d元\n",
        car.arrive, car.leave, car.leave-car.arrive, (car.leave-car.arrive)*2);
    }
    //查找这辆车
    printf("一路顺风！\n");
    return OK;
}

Status Menu(SqStack &park, SqStack &wait, LQueue &shortcut, Car &car, int length)
{
    int mode;
    printf("1.进场 2.出场  0.退出\n");
    scanf("%d", &mode);
    switch (mode)
    {
    case 0:
        printf("退出程序");
        exit(OK);
        break;
    case 1:
        CarIn(park, shortcut, length, car);
        CarInformationOut(car);
        break;
    case 2:
        CarLeftInformation(park, wait, shortcut, car);
        break;
    default:
        break;
    }
    return OK;
}

int main()
{
    int length;
    SqStack park, wait;
    LQueue shortcut;
    Car car;
    InitStack(park);
    InitStack(wait);
    InitLQueue(shortcut);
    printf("请输入停车场大小：");
    scanf("%d", &length);
    printf("停车场管理系统：prod.by 范昊翔 2019051364\n");
    while(1)
    {
        Menu(park, wait, shortcut, car, length);
    }
    return 0;
}