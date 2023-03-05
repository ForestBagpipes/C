#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 50
#define OK 1
#define ERROR 0
typedef int Status;
typedef int Elemtype;
typedef struct NodeLIST
{
    Elemtype date[MAXSIZE];
    int num;
} SeqList;

SeqList *Create() //创建线性表
{
    SeqList *head;
    head = (SeqList *)malloc(sizeof(SeqList));
    head->num = 0;
    return head;
}
Status Adddate(SeqList *L, int n, int i) //对线性表进行添加数据操作
{
    int k = 0;
    if (L->num == MAXSIZE)
    {
        return ERROR;
    }
    if (i < 1 || i > L->num + 1)
    {
        return ERROR;
    }
    for (k = L->num - 1; k >= i - 1; k--)
    {
        L->date[k + 1] = L->date[k];
    }
    L->date[i - 1] = n;
    L->num++;
    return OK;
}
Status OutputDate(SeqList *L) //对线性表进行输出操作
{
    int i;
    for (i = 0; i < L->num; i++)
    {
        printf("%d ", L->date[i]);
    }
    printf("\n");
    return OK;
}
Status DeleteDate(SeqList *L, int i) //对线性表进行删除第几位元素操作
{
    int k = 0, j = 0;
    if (L->num == 0)
    {
        return ERROR;
    }
    if (i < 1 || i > L->num + 1)
    {
        return ERROR;
    }
    for (k = i - 1; k < L->num; k++)
    {
        L->date[k] = L->date[k + 1];
    }
    L->num--;
    return OK;
}
Status Quchong(SeqList *L) //对线性表进行去重操作
{
    int i;
    for (i = 1; i < L->num; i++)
    {
        if (L->date[i - 1] == L->date[i])
        {
            DeleteDate(L, i);
            i--;
        }
    }
    return OK;
}
Status Reverse(SeqList *L) //对线性表进行逆置操作
{
    int c[MAXSIZE];
    int i;
    for (i = 0; i < L->num; i++)
    {
        c[i] = L->date[i];
    }
    for (i = 0; i < L->num; i++)
    {
        L->date[i] = c[L->num - i - 1];
    }
    return OK;
}
Status Mov(SeqList *L, char p, int n) //对线性表进行左右移动操作
{
    int c[MAXSIZE];
    int i;
    int j;
    for (i = 0; i < L->num; i++)
    {
        c[i] = L->date[i];
    }
    if (n > L->num || n < 0)
    {
        return ERROR;
    }
    if (p == 'L' || p == 'l')
    {
        j = -1;
        for (i = 0; i < L->num; i++)
        {
            L->date[(i + L->num + j * n) % L->num] = c[i];
        }
    }
    else if (p == 'R' || p == 'r')
    {
        j = 1;
        for (i = 0; i < L->num; i++)
        {
            L->date[(i + L->num + j * n) % L->num] = c[i];
        }
    }
    else
    {
        printf("输入有误");
    }
    return OK;
}
Status sort(SeqList *L) //升序；
{
    int i, j;
    int tmp;
    int c[MAXSIZE];
    for (i = 0; i < L->num; i++)
    {
        c[i] = L->date[i];
    }
    for (i = 0; i < L->num; i++)
    {
        for (j = 0; j < L->num - i; j++)
        {
            if (c[j] > c[j + 1])
            {
                tmp = c[j];
                c[j] = c[j + 1];
                c[j + 1] = tmp;
            }
        }
    }
    for (i = 0; i < L->num; i++)
    {
        L->date[i] = c[i];
    }
    return OK;
}
Status link(SeqList *L1, SeqList *L2) //对两个排好序的线性表进行连接操作
{
    if (L1->num + L2->num > MAXSIZE)
    {
        printf("超出范围");
        return ERROR;
    }
    else
    {
        int c[MAXSIZE];
        memset(c, sizeof(int) * MAXSIZE, 0);
        int i = 0, j = 0, k = 0;
        while (i < L1->num && j < L2->num)
        {
            if (L1->date[i] < L2->date[j])
            {
                c[k] = L1->date[i];
                k++;
                i++;
            }
            else
            {
                c[k] = L2->date[j];
                k++;
                j++;
            }
        }
        while (i < L1->num)
        {
            c[k] = L1->date[i];
            k++;
            i++;
        }
        while (j < L2->num)
        {
            c[k] = L2->date[j];
            k++;
            j++;
        }
        L1->num = k;
        for (i = 0; i < L1->num; i++)
        {
            L1->date[i] = c[i];
        }
        return OK;
    }
}
int main()
{
    SeqList *List, *List1;
    int n = 0;
    List = Create();
    int a[9] = {2, 3, 3, 3, 9, 10, 12, 14, 14};
    int b[9] = {1, 3, 7, 8, 11, 12, 15, 16, 19};
    int i;
    printf("插入如下元素作顺序线性表：\n");
    for (i = 1; i <= 9; i++)
    {
        printf("%d ", a[i - 1]);
        Adddate(List, a[i - 1], i);
    }
    printf("\n");
    printf("此时线性表元素为：\n");
    OutputDate(List);
    printf("想要删除的元素值为多少？\n");
    scanf("%d", &n);
    for (i = 1; i <= List->num; i++)
    {
        if (List->date[i - 1] == n)
        {
            DeleteDate(List, i);
            i--;
        }
    }
    printf("此时线性表元素为：\n");
    OutputDate(List);
    printf("对该已排好序的线性表去重操作后，结果为：\n");
    Quchong(List);
    OutputDate(List);
    printf("对该线性表进行逆置操作后，结果为：\n");
    Reverse(List);
    OutputDate(List);
    printf("对该线性表循环左移还是右移？(左移输入L或l,右移输入R或r)\n");
    char pos;
    fflush(stdin);
    scanf("%c", &pos);
    printf("移动几位？\n");
    int len;
    fflush(stdin);
    scanf("%d", &len);
    printf("移动后结果：\n");
    Mov(List, pos, len);
    OutputDate(List);
    printf("将移动后线性表重排序:\n");
    sort(List);
    OutputDate(List);
    printf("再创一个升序顺序线性表,其元素如下：\n");
    List1 = Create();
    for (i = 1; i <= 9; i++)
    {
        Adddate(List1, b[i - 1], i);
    }
    OutputDate(List1);
    printf("将两个表格相连，结果为:\n");
    link(List, List1);
    OutputDate(List);
    return 0;
}