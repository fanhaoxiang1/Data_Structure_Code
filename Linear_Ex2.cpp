#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LIST_INCREMENT 10
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define DEFAULT 1
typedef int Status;

typedef struct Score
{
    float digital_logic;
    float data_structure;
    float graph_algebra;
    float probability_theory;
}Score;

typedef struct Student
{
    long no;
    char name[20];
    Score score;
}Student, ElemType;

typedef struct ManagementSystem
{
    ElemType *elem;
    int length;
    int size;
}SqList;

Status WhetherMoreSize (SqList &S)
{
    if (S.size <= S.length)
    {
        ElemType *base = (ElemType *) realloc (S.elem,
        sizeof(ElemType)*(S.size+LIST_INCREMENT));
        if (!base) exit(OVERFLOW);
        S.size += LIST_INCREMENT;
        S.elem = base;
    }
    return OK;
}
Status InitSqList (SqList &S)
{
    char y;
    printf("此操作将会重置整个系统并从头开始录入，确定请输入y\n");
    fflush(stdin);
    y = getchar();
    if (y != 'y')
    {
        printf("操作取消\n");
        return ERROR;
    }
    int init_list_size;
    printf("请输入目前学生的人数\n");
    scanf("%d",&init_list_size);
    S.elem = (ElemType *) malloc (sizeof(ElemType) * init_list_size * 2);
    //为了避免总是分配，分配大一点的空间
    if (!S.elem) exit(OVERFLOW);
    S.length = 0;
    S.size = 2 * init_list_size;
    printf("初始化成功！\n");
    return OK;
}
Status Averange(SqList S, int index)
{
    float averange;
    averange =(S.elem[index].score.digital_logic +
        S.elem[index].score.data_structure + S.elem[index].score.graph_algebra +
        S.elem[index].score.probability_theory) / 4;
    printf("平均分%.2f",averange);
    return OK;
}

Status GetOneInSqList (SqList S, int index)
{
    printf("%d %ld %s\n数字逻辑:%.2f数据结构:%.2f图论:%.2f概率论:%.2f ",index+1, S.elem[index].no,
        S.elem[index].name, S.elem[index].score.digital_logic,
        S.elem[index].score.data_structure, S.elem[index].score.graph_algebra,
        S.elem[index].score.probability_theory);
    Averange(S, index);
    printf("\n");
    return OK;
}
Status PutOneInSqList (SqList &S,int x)
{
    
    printf("学号和姓名是：\n");
    scanf("%ld",&S.elem[x].no);
    fflush(stdin);
    scanf("%s",&S.elem[x].name);
    printf("请依次输入他的数字逻辑、数据结构、图论、概率论的分数\n");
    scanf("%f%f%f%f",&S.elem[x].score.digital_logic,
    &S.elem[x].score.data_structure,&S.elem[x].score.graph_algebra,
    &S.elem[x].score.probability_theory);
    S.length += 1;
    return OK;
}
Status PutInSqList (SqList &S)
{
    char y;
    printf("开始录入：\n");
    while(1)
    {
        WhetherMoreSize(S);//判断容量是否充足
        printf("第%d个同学，",S.length+1);
        PutOneInSqList(S,S.length);
        printf("录入完成，是否输入下个同学？是则输入y\n");
        fflush(stdin);
        y = getchar();
        if (y !='y')
        break;
    }
    return OK;
}

Status GetFromSqlist (SqList S)
{
    printf("全班成绩表\n");
    int index = 0;
    while(index < S.length)
    {
        GetOneInSqList(S,index);
        index++;
    }
    printf("以上为全班成绩\n");
    return OK;
}

Status InsertSqList(SqList &S)
{
    int x;
    printf("你要在第几个位置插入？");
    scanf("%d",&x);
    WhetherMoreSize(S);
    int p = 0;
    if (p>S.length) exit(ERROR);
    int q = S.length;
    while(q>p)
    {
        S.elem[q] = S.elem[q-1];
        q--;
    }
    PutOneInSqList(S,x-1);
    return OK;
}

Status SearchInSqList(SqList S)
{
    printf("你需要查找的关键词是：");
    char search[20];
    fflush(stdin);
    scanf("%s",search);
    int p = 0;
    int flag = 0;
    while (flag == 0 && p<S.length)
    {
        if (strcmp(S.elem[p].name, search) == 0 || atof(search)==S.elem[p].no)
        flag = 1;
        else    p++;
    }
    if (p>=S.length)
    {
        printf("没有结果！");
        return OK;
    }
    GetOneInSqList(S,p);
    return OK;
}

Status DeleteOneInSqList(SqList &S)
{
    int i;
    printf("你要删除哪一个人?");
    scanf("%d",&i);
    int p = i;
    while(p<=S.length)
    {
        S.elem[p-1] = S.elem[p];
        p++;
    }
    S.length--;
    return OK;
}
Status Menu(SqList &S)
{
    system("cls");
    int choice;
    printf("           成绩管理系统prod.by范昊翔2019051364\n");
    printf("--------------------------------------------------------------\n");
    printf("1.成绩录入 2.输出成绩表和每门课成绩 3.插入成绩 4.删除成绩 5.查询\n");
    printf("你要执行那个功能?     0.退出\n");
    scanf("%d",&choice);
    switch (choice)
    {
    case 0:
        printf("感谢您的使用!");
        exit(OK);
        break;
    case 1:
        if(InitSqList(S)==0)
        break;
        PutInSqList(S);
        break;
    case 2:
        GetFromSqlist(S);
        system("pause");
        break;
    case 3:
        InsertSqList(S);
        break;
    case 4:
        DeleteOneInSqList(S);
        break;
    case 5:
        SearchInSqList(S);
        system("pause");
    default:
        break;
    }
    return OK;
}

int main()
{
    SqList myclass;
    while (1) Menu(myclass);
    return 0;
}