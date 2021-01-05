#include <stdio.h>
#include <stdlib.h>
#define LIST_INIT_SIZE 2
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define DEFAULT 1
typedef int Status;
typedef int Elemtype;
typedef Elemtype *Rat;

Status Put(Rat R)//打印R所储存的有理数
{

    if (R[0]<0)
    {
        R[1] = -R[1];
        R[0] = -R[0];
    }
    printf("%d/%d\n",R[1],R[0]);
    return OK;
}

Status gcd(Rat &R)//求最大公因数，并直接改写R，传出
{
    Elemtype a, b, c = DEFAULT;
    if (R[1] == 0) return OK;
    else if (R[0] == R[1]) 
    {
        R[0] = 1;
        R[1] = 1;
        return OK;
    }
    else if (R[0] > R[1])
    {
        a = R[0];
        b = R[1];
    }
    else 
    {
        a = R[1];
        b = R[0];
    }
    while (c != 0)
    {
        c = a % b;
        a = b;
        b = c;
    }
    R[0] /=  a;
    R[1] /=  a;
    return OK;
}

Status InitRat(Rat &R, Elemtype v1, Elemtype v2)
{
    if(v1 <= 0) exit(ERROR);//不允许分母为负数或者0
    R = (Elemtype*) malloc (LIST_INIT_SIZE * sizeof(Elemtype));
    if(!R) exit(OVERFLOW);
    R[0] = v1;
    R[1] = v2;
    return OK;
}

Status PlusRat(Rat &R, Rat R1, Rat R2)
{
    printf("%d/%d + %d/%d = ",R1[1],R1[0],R2[1],R2[0]);
    R[0] = R1[0] * R2[0];
    R[1] = (R1[0] * R2[1]) + (R2[0] * R1[1]);
    gcd(R);
    Put(R);
    return OK;
}

Status SubtractRat(Rat &R, Rat R1, Rat R2)
{
    printf("%d/%d - %d/%d = ",R1[1],R1[0],R2[1],R2[0]);
    R[0] = R1[0] * R2[0];
    R[1] = R1[1] * R2[0] - R2[1] * R1[0];
    gcd(R);
    Put(R);
    return OK;
}

Status MultiplyRat(Rat &R, Rat R1, Rat R2)
{
    printf("%d/%d * %d/%d = ",R1[1],R1[0],R2[1],R2[0]);
    R[0] = R1[0] * R2[0];
    R[1] = R2[1] * R1[1];
    gcd(R);
    Put(R);
    return OK;
}

Status DevideRat(Rat &R, Rat R1, Rat R2)
{
    printf("%d/%d ÷ %d/%d = ",R1[1],R1[0],R2[1],R2[0]);
    Elemtype temp = R2[1];
    R2[1] = R2[0];
    R2[0] = temp;
    MultiplyRat(R, R1, R2);
    /*
    R[0] = R1[0] * R2[1];
    R[1] = R2[1] * R1[0];
    gcd(R);
    Put(R);
    */
    return OK;
}

Status DestroyRat (Rat &R)
{
    free(R);
    R =NULL;
    return OK;
}

int main()
{
    Elemtype v1, v2;
    printf("请先初始化两个数，并确保分母大于等于零：\n");
    printf("第一个数的分母分子分别是：");
    scanf("%d%d",&v1, &v2);
    printf("已经创建一个有理数！%d/%d\n",v2,v1);
    Rat R1;
    InitRat(R1, v1, v2);
    printf("第二个数的分母分子分别是：");
    scanf("%d%d",&v1, &v2);
    printf("已经创建一个有理数！%d/%d\n",v2,v1);
    Rat R2;
    InitRat(R2, v1, v2);
    Rat R;//这个用来显示结果
    InitRat(R, DEFAULT, DEFAULT);
    printf("下面进行加法运算");
    PlusRat(R, R1, R2);
    printf("下面进行减法运算");
    SubtractRat(R, R1, R2);
    printf("下面进行乘法运算");
    MultiplyRat(R, R1, R2);
    printf("下面进行除法运算");
    DevideRat(R, R1, R2);
    DestroyRat(R1);
    DestroyRat(R2);
    DestroyRat(R);
    printf("测试完成^ ^\n");
    system("pause");
    return 0;
}