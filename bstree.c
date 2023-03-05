#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAXSIZE 2000
int n[MAXSIZE];
int count = 0;
int s = 0; //记录比较次数

//定义二叉查找树结构体
typedef struct bst
{
    int date;
    struct bst *lchild;
    struct bst *rchild;
} bst;

//二叉查找树插入操作
bst *insert(int x, bst *F)
{
    if (!F)
    {
        F = (bst *)malloc(sizeof(bst));
        F->date = x;
        F->lchild = NULL;
        F->rchild = NULL;
    }
    else if (F->date > x)
    {
        F->lchild = insert(x, F->lchild);
    }
    else if (F->date < x)
    {
        F->rchild = insert(x, F->rchild);
    }
    return F;
}

//二叉查找树查找操作，找到后返回结点指针
bst *search(int x, bst *F)
{
    if (F == NULL) //查找失败
    {
        s++;
        return NULL;
    }
    else if (F->date == x)
    {
        s++;
        return F;
    }
    else if (x > F->date)
    {
        s++;
        return search(x, F->rchild);
    }
    else if (x < F->date)
    {
        s++;
        return search(x, F->lchild);
    }
}

//二叉查找树删除最小关键字结点操作
bst *deletemin(bst *F)
{
    if (F == NULL)
    {
        return NULL;
    }
    else if(F->lchild ==NULL)
    {
        return F;
    }
    else 
    {
        return deletemin(F->lchild);
    }
}

//二叉查找树删除操作
bst *delete (int x, bst *F)
{
    bst *tmp;
    if (F != NULL)
    {
        if (x < F->date)
        {
            F->lchild = delete (x, F->lchild);
        }
        else if (x > F->date)
        {
            F->rchild = delete (x, F->rchild);
        }
        else if(F->lchild&&F->rchild)
        {
            tmp = deletemin(F->rchild);
            F->date = tmp->date;
            F->rchild = delete(F->date,F->rchild);
        }
        else
        {
            tmp = F;
            if(F->lchild == NULL)
            {
                F = F->rchild;
            }
            else if(F->rchild == NULL)
            {
                F = F->lchild;
            }
            free(tmp);
        }
        return F;
    }
}

//二叉查找树排序操作（实际即为二叉查找树中序遍历操作）
void sort(bst *F, int a[])
{
    if (F != NULL)
    {
        sort(F->lchild, a);
        a[count++] = F->date;
        sort(F->rchild, a);
    }
}

void sort1(bst *F, int a[])
{
    if (F)
    {
        sort1(F->lchild, a);
        printf("%d ", F->date);
        sort1(F->rchild, a);
    }
}

//折半查找算法
int binsearch(int a[], int len, int x)
{
    int beg = 0;
    int end = len - 1;
    int mid;
    while (beg <= end)
    {
        mid = (beg + end) / 2;
        if (a[mid] == x)
        {
            s++;
            return mid;
        }
        else if (a[mid] > x)
        {
            s++;
            end = mid - 1;
        }
        else if (a[mid] < x)
        {
            s++;
            beg = mid + 1;
        }
    }
    return -1; //查找失败
}

int main()
{
    int i, j, k;
    int tmp;
    int num[MAXSIZE];
    memset(num, 0, sizeof(num));
    for (i = 0; i < 1024; i++)
    {
        num[i] = i * 2 + 1;
    }

    bst *F1, *F2;
    F1 = NULL;
    F2 = NULL;
    for (i = 0; i < 1024; i++) //生成第一组数据的BST结构
    {
        F1 = insert(num[i], F1);
    }
    printf("第一组数据为0-2048间的奇数的升序排序\n");
    srand(time(NULL));
    for (i = 0; i < 1000; i++) //生成1024个数的随机序列
    {
        j = rand() % 1024;
        k = rand() % 1024;
        tmp = num[j];
        num[j] = num[k];
        num[k] = tmp;
    }
    for (i = 0; i < 1024; i++) //生成第二组数据的BST结构
    {
        F2 = insert(num[i], F2);
    }
    printf("第二组数据为0-2048间的奇数的随机排序\n");
    double suc = 0;  //查找成功的平均查找长度
    double fail = 0; //查找失败的平均查找长度
    bst *t;
    for (i = 0; i < 1024; i++)
    {
        s = 0;
        t = search(i * 2 + 1, F1);
        suc = suc + s;
    }
    suc = suc / 1024;
    printf("\n第一组BST结构查找成功的平均查找长度为: %f \n", suc);
    for (i = 0; i < 1024; i++)
    {
        s = 0;
        t = search(i * 2 + 2, F1);
        fail = fail + s;
    }
    fail = fail / 1024;
    printf("第一组BST结构查找失败的平均查找长度为: %f \n", fail);
    suc = 0;
    fail = 0;
    for (i = 0; i < 1024; i++)
    {
        s = 0;
        t = search(i * 2 + 1, F2);
        suc = suc + s;
    }
    suc = suc / 1024;
    printf("\n第二组BST结构查找成功的平均查找长度为: %f \n", suc);
    for (i = 0; i < 1024; i++)
    {
        s = 0;
        t = search(i * 2 + 2, F2);
        fail = fail + s;
    }
    fail = fail / 1024;
    printf("第二组BST结构查找失败的平均查找长度为: %f \n", fail);

    int a1[MAXSIZE];
    int a2[MAXSIZE];
    memset(a1, 0, sizeof(a1));
    memset(a2, 0, sizeof(a2));
    count = 0;
    sort(F1, a1); //保存F1的中序遍历结果
    count = 0;
    sort(F2, a2); //保存F2的中序遍历结果
    suc = 0;
    fail = 0;
    for (i = 0; i < 1024; i++)
    {
        s = 0;
        tmp = binsearch(a1, 1024, i * 2 + 1);
        suc = suc + s;
    }
    suc = suc / 1024;
    printf("\n第一组折半查找成功的平均查找长度为: %f \n", suc);
    for (i = 0; i < 1024; i++)
    {
        s = 0;
        tmp = binsearch(a1, 1024, i * 2 + 2);
        fail = fail + s;
    }
    fail = fail / 1024;
    printf("第一组折半查找失败的平均查找长度为: %f \n", fail);
    suc = 0;
    fail = 0;
    for (i = 0; i < 1024; i++)
    {
        s = 0;
        tmp = binsearch(a2, 1024, i * 2 + 1);
        suc = suc + s;
    }
    suc = suc / 1024;
    printf("\n第二组折半查找成功的平均查找长度为: %f \n", suc);
    for (i = 0; i < 1024; i++)
    {
        s = 0;
        tmp = binsearch(a2, 1024, i * 2 + 2);
        fail = fail + s;
    }
    fail = fail / 1024;
    printf("第二组折半查找失败的平均查找长度为: %f \n", fail);

    bst *F = NULL;
    int a[MAXSIZE];
    int m;
    int len = 0; //保存数组长度
    printf("\n下面演示BST 插入（建立）、删除、查找和排序以及折半查找算法：\n");
    printf("演示数据为0-20中的奇数的随机排序\n");
    memset(num, 0, sizeof(num));
    memset(a, 0, sizeof(a));
    for (i = 0; i < 10; i++)
    {
        num[i] = i * 2 + 1;
    }
    for (i = 0; i < 10; i++) //生成1024个数的随机序列
    {
        j = rand() % 10;
        k = rand() % 10;
        tmp = num[j];
        num[j] = num[k];
        num[k] = tmp;
    }
    for (i = 0; i < 10; i++) //生成演示数据的BST结构
    {
        F = insert(num[i], F);
    }
    printf("生成演示数据的BST结构\n");
    printf("打印当前BST的中序遍历:\n");
    count = 0;
    sort(F, a);
    sort1(F, a);
    memset(a, 0, sizeof(a));
    printf("\n");
    m = rand() % 20;
    printf("\n生成要查找的随机数：%d\n", m);
    t = search(m, F);
    if (t)
    {
        printf("查找成功，%d 在BST结构中存在\n", m);
    }
    else
    {
        printf("查找失败！\n");
    }
    m = rand() % 20;
    printf("\n生成要删除的随机数：%d\n", m);
    t = search(m, F);
    if(t)
    {
        F = delete (m, F);
    }
    printf("打印当前BST的中序遍历:\n");
    count = 0;
    sort(F, a);
    sort1(F, a);
    memset(a, 0, sizeof(a));
    printf("\n");
    m = rand() % 20;
    printf("\n生成要插入的随机数：%d\n", m);
    F = insert(m, F);
    printf("打印当前BST的中序遍历:\n");
    count = 0;
    sort(F, a);
    sort1(F, a);
    printf("\n");
    m = rand() % 20;
    printf("\n生成要进行折半查找的随机数：%d\n", m);
    printf("对当前的BST生成的中序遍历序列进行折半查找:\n");
    for (i = 0; i < MAXSIZE; i++)
    {
        if (a[i] != 0 && a[i + 1] == 0)
        {
            len = i + 1;
            break;
        }
    }
    tmp = binsearch(a, len, m);
    if (tmp == -1)
    {
        printf("查找失败！\n");
    }
    else
    {
        printf("查找成功，且其在数组内对应下标为：%d\n", tmp);
    }
    system("pause");
    return 0;
}