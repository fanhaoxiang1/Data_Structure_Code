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

//���ṹ��
typedef struct{
	int weight;
	int parent,lchild,rchild;
	char ch;//Ϊ�˲��ҷ��㣬���ַ�Ҳ����ṹ����
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
//ע��HuffmanTree��һ�У�HuffmanCode��str��û�п��У�
void HuffmanCoding (HuffmanTree &HT, HuffmanCode &HC, int *w, int n, char *str)//w�д��n������Ȩֵ������huffman���뵽HC
{
    int m = n * 2 - 1;//�ܽ����
    HT = (HuffmanTree) malloc (sizeof(HTNode) * (m+1));//��һ������,����Ҫ��һ����
    HT[0] = {0, 0, 0, 0,' '};
    for(int i = 1; i<=m; i++)
    {
        if (i<=n)
        {
            HT[i] = {w[i-1], 0, 0, 0, str[i-1]};//��w�е�Ȩֵ����HT��
        }
        else HT[i] = {0, 0, 0, 0, ' '};//����Ľ������ȫ0
    }//��ʼ�����
    for(int i=n+1; i<=m; i++)
    {
        int s1 = 0, s2 = 0;
        SelectMin(HT ,i ,s1, s2);//s1,s2����СȨֵ�����
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
    //��ʼ���
    HC = (HuffmanCode) malloc ((n+1)*sizeof(char *));//����洢n+1���������飬�����HC��ֻ�����ǵ�ָ�룬�����HC[i]��û�г�ʼ��
    char *cd = (char *)malloc(n * sizeof(char));//������ĳһ���ִ�cd�Ŀռ䣬��С��n-1���ַ������ǿ϶����ˣ�������ŵĶ������ϲ����ġ�
    cd[n-1] = '\0';
    for (int i=1; i<=n; i++)
    {
        int start = n - 1;//�������������������ģ�����Ҫ�����һλ��ʼ���롣
        int f;
        for (int c=i, f=HT[i].parent; f!=0;)//����ĳһ����㣬Ҫ��ʼ�����ı���
        {
            if (HT[f].lchild == c) cd[--start] = '0';
            else cd[--start] = '1';
            c=f;
            f = HT[f].parent;
        }
        HC[i-1] = (char *) malloc ((n-start)*sizeof(char));
        strcpy(HC[i-1], &cd[start]);
    }
    //free(cd);//��ʱ�ռ���Ҫfree��
}
//����û������10:58

void Encode (HuffmanCode &HC, char *str)
{
    FILE *fp;
    if(!(fp=fopen("CodeFile.txt","w+"))) printf("CodeFile.txt��ʧ��!");
	char encoding[N];
    printf("��������Ҫ������ַ���\n");
	fflush(stdin);
    gets(encoding);
    int i = 0;
    while(encoding[i]!='\0')
    {
        for(int j=0;;j++)
        {
            if (encoding[i]==str[j])
            {
                fputs(HC[j],fp);//�������Ӧ�ı���
                break;
            }
        }
        i++;
    }
	printf("������ɣ�����CodeFile.txt\n");
	fclose(fp);
}
//����û������11:04

void Save (HuffmanCode &HC, char *str, int n)
{
	FILE *fp;
	fp = fopen("hfmTree.txt","w+");
	if(!fp)
	{
		printf("��ʧ��");
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
//����û������11:44
void Read (HuffmanCode &HC, char *str, int n)
{
    HC = (HuffmanCode) malloc ((n+1)*sizeof(char *));
	FILE *fp;
    fp = fopen("hfmTree.txt","r");
    if(!fp)
	{
		printf("��ʧ��");
		exit(ERROR);
	}
    for (int i=0; i<n; i++)
    {
        str[i] = fgetc(fp);
    }
    char temp;//���������з�
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
//����û������16:00

void Decoding(HuffmanCode &HC, char *str, int n)
{
    
    FILE *fp;
    FILE *fq;
    if(!(fp=fopen("CodeFile.txt","r"))) printf("CodeFile.txt��ʧ��!");
    if(!(fq=fopen("TextFile.txt","w+"))) printf("TextFile.txt��ʧ��!");
	char encoding[N];
    char temp;//�����洢��ʱ�ַ�
    char detect[n+1];//�����洢��ƥ���ַ���
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
//����û������16:54

int main()
{
    HuffmanTree HT;
    HuffmanCode HC;
    int n;
    printf("��������Ҫ���������\n");
    scanf("%d",&n);
    int w[n];
    char str[n+1];
    while(1)
    {
        printf("��ӭ����********��������ϵͳ**** prod.by ����� 2019051364\n");
        printf("1.���� 2.д��hfmTree 3.���뵽CodeFile 4.����hfmTree 5.��CodeFile���� 0.�˳�\n");
        int d;
        scanf("%d",&d);
        switch(d)
        {
            case 1:
            {
                printf("�����������ַ�\n");
                fflush(stdin);
                gets(str);
                for (int i=0; i<n; i++)
                {
                    printf("������%c��Ȩֵ\n",str[i]);
                    scanf("%d",&w[i]);
                }
                HuffmanCoding(HT, HC, w, n, str);
                printf("���Ƴɹ���\n");
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

    // detect[0] = '\0';//��ʼ��Ϊ��
    // fgets(decode,N,fp);
    // int r = 0;//��¼�ƶ����ĸ�λ��
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
