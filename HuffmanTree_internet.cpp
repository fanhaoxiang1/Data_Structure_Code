#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define N 1000
#define INF INT_MAX
typedef int Status;
typedef int ElemType;

//结点结构体
typedef struct{
	int weight;
	int parent,lchild,rchild;
	char ch;//为了查找方便，将字符也放入结构体中
}HTNode, *HuffmanTree;
typedef char **HuffmanCode;
void SelectMin (HuffmanTree &HT, int i, int &s1, int &s2)
{
    int j;
    int min1 = INF, min2 = INF;
    for (j = 1; j<i; j++)
    {
        if (HT[j].weight < min1 && HT[j].parent==0)
        {
            min1 = HT[j].weight;
            s1 = j;
        }
    }
    for (j = 1; j<i; j++)
    {
        if (HT[j].weight < min2 && HT[j].parent==0 && j!=s1)
        {
            min2 = HT[j].weight;
            s2 = j;
        }
    }
}
//注意HuffmanTree空一行，HuffmanCode和str都没有空行！
void HuffmanCoding (HuffmanTree &HT, HuffmanCode &HC, int *w, int n, char *str)//w中存放n个数的权值，返回huffman编码到HC
{
    int m = n * 2 - 1;//总结点数
    HT = (HuffmanTree) malloc (sizeof(HTNode) * (m+1));//第一个表不存,所以要多一个。
    HT[0] = {0, 0, 0, 0,' '};
    for(int i = 1; i<=m; i++)
    {
        if (i<=n)
        {
            HT[i] = {w[i-1], 0, 0, 0, str[i-1]};//将w中的权值存入HT中
        }
        else HT[i] = {0, 0, 0, 0, ' '};//多余的结点则是全0
    }//初始化完毕
    for(int i=n+1; i<=m; i++)
    {
        int s1 = 0, s2 = 0;
        SelectMin(HT ,i ,s1, s2);//s1,s2是最小权值的序号
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
    //开始输出
    HC = (HuffmanCode) malloc ((n+1)*sizeof(char *));//分配存储n+1个数的数组，但这个HC中只存他们的指针，具体的HC[i]还没有初始化
    char *cd = (char *)malloc(n * sizeof(char));//分配了某一个字串cd的空间，大小是n-1个字符，但是肯定多了，这是最不优的二叉树上产生的。
    cd[n-1] = '\0';
    for (int i=1; i<=n; i++)
    {
        int start = n - 1;//由于求出来的码是逆向的，所以要从最后一位开始输入。
        int f;
        for (int c=i, f=HT[i].parent; f!=0;)//对于某一个结点，要开始找他的编码
        {
            if (HT[f].lchild == c) cd[--start] = '0';
            else cd[--start] = '1';
            c=f;
            f = HT[f].parent;
        }
        HC[i-1] = (char *) malloc ((n-start)*sizeof(char));
        strcpy(HC[i-1], &cd[start]);
    }
    //free(cd);//临时空间需要free掉
}
//以上没有问题10:58

void Encode (HuffmanCode &HC, char *str)
{
    FILE *fp;
    if(!(fp=fopen("CodeFile.txt","w+"))) printf("CodeFile.txt打开失败!");
	char encoding[N];
    printf("请输入需要编码的字符串\n");
	fflush(stdin);
    gets(encoding);
    int i = 0;
    while(encoding[i]!='\0')
    {
        for(int j=0;;j++)
        {
            if (encoding[i]==str[j])
            {
                fputs(HC[j],fp);//输出它对应的编码
                break;
            }
        }
        i++;
    }
	printf("编码完成，存入CodeFile.txt\n");
	fclose(fp);
}
//以上没有问题11:04

void Save (HuffmanCode &HC, char *str, int n)
{
	FILE *fp;
	fp = fopen("hfmTree.txt","w+");
	if(!fp)
	{
		printf("打开失败");
		exit(ERROR);
	}
    for (int i=0; i<n; i++)
    {
        fputc(str[i],fp);
    }
    fprintf(fp,"\n");
    for (int i=0; i<n; i++)
    {
        fputs(HC[i],fp);
        fprintf(fp,"\n");
        // fprintf(fp,"\0");
    }
	fclose(fp);
}
//以上没有问题11:44
void Read (HuffmanCode &HC, char *str, int n)
{
    HC = (HuffmanCode) malloc ((n+1)*sizeof(char *));
	FILE *fp;
    fp = fopen("hfmTree.txt","r");
    if(!fp)
	{
		printf("打开失败");
		exit(ERROR);
	}
    for (int i=0; i<n; i++)
    {
        str[i] = fgetc(fp);
    }
    char temp;//用来处理换行符
    temp = fgetc(fp);
    for (int i= 0; i<n; i++)
    {
        HC[i] = (char*) malloc (sizeof(char)*n);
        fgets(HC[i],n,fp);
        while(HC[i][0]=='\0'||HC[i][0]=='\n') fgets(HC[i],n,fp);
        int m;
        for (m=0; HC[i][m]!='\n'; m++)  {}
        HC[i][m] = '\0';
        // char * d= (char *)malloc((strlen(HC[i]-1))*sizeof(char));
        // memcpy(d,HC[i],strlen(HC[i]-1));
        // free(d);
    }
	fclose(fp);
}
//以上没有问题16:00

void Decoding(HuffmanCode &HC, char *str, int n)
{
    
    FILE *fp;
    FILE *fq;
    if(!(fp=fopen("CodeFile.txt","r"))) printf("CodeFile.txt打开失败!");
    if(!(fq=fopen("TextFile.txt","w+"))) printf("TextFile.txt打开失败!");
	char encoding[N];
    char temp;//用来存储临时字符
    char detect[n+1];//用来存储待匹配字符串
    char decode[N];

    temp=fgetc(fp);
    for(int i=0; temp=='0'||temp=='1'; i++)
    {
        detect[i] = temp;
        detect[i+1] = '\0';
        for (int j=0; j<n; j++)
        {
            if (strcmp(HC[j], detect)==0) 
            {
                printf("%c", str[j]);
                fprintf(fq,"%c",str[j]);
                detect[0] = '\0';
                i=-1;
            }
        }
        temp=fgetc(fp);
    }
	fclose(fp);
    fclose(fq);
    printf("\n");
}
//以上没有问题16:54

int main()
{
    HuffmanTree HT;
    HuffmanCode HC;
    int n;
    printf("请输入需要编码的数量\n");
    scanf("%d",&n);
    int w[n];
    char str[n+1];
    while(1)
    {
        printf("欢迎来到********编码译码系统**** prod.by 范昊翔 2019051364\n");
        printf("1.编码 2.写入hfmTree 3.编码到CodeFile 4.读入hfmTree 5.从CodeFile译码 0.退出\n");
        int d;
        scanf("%d",&d);
        switch(d)
        {
            case 1:
            {
                printf("请依次输入字符\n");
                fflush(stdin);
                gets(str);
                for (int i=0; i<n; i++)
                {
                    printf("请输入%c的权值\n",str[i]);
                    scanf("%d",&w[i]);
                }
                HuffmanCoding(HT, HC, w, n, str);
                printf("编制成功！\n");
                break;
            }
            case 2: Save(HC, str, n); break;
            case 3: Encode(HC, str); break;
            case 4: Read(HC, str, n); break;
            case 5: Decoding(HC, str, n);break;
            case 0: exit(0);
        }
    }
    return 0;
}

    
    
    // char str_new[n+1];
    // HuffmanCode HC_new;
    // Read(HC_new, str_new, n);
    // Decoding(HC, str, n);
    // return 0;

    // detect[0] = '\0';//初始化为空
    // fgets(decode,N,fp);
    // int r = 0;//记录移动到哪个位置
    // for (int i=1; decode[i]=='0'||decode[i]=='1'; i++)
    // {
    //     // detect[0]='\0';
    //     memcpy(detect, decode + r, i);
    //     for (int j=0; j<n; j++)
    //     {
    //         if (strcmp(detect, HC[j])==0)
    //         {
    //             printf("%c", str[j]);
    //             r += i;
    //         }
    //     }
    // }
