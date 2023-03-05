#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAXSIZE 100
//测试用例 ABD##E##C#F##
typedef struct Bitree
{
    struct Bitree *left, *right;
    char data;
    int flag;
} BinNode;
BinNode *createtree(BinNode *p)
{
    char ch;
    scanf("%c", &ch);
    if (ch == '#')
    {
        return NULL;
    }
    else
    {
        p = (BinNode *)malloc(sizeof(BinNode));
        p->data = ch;
        p->flag = 0;
        p->left = createtree(p->left);
        p->right = createtree(p->right);
        return p;
    }
}
void show(BinNode *p)
{
    if (p == NULL)
    {
        return;
    }
    else
    {
        printf("%c ", p->data);
        if (p->left)
        {
            show(p->left);
        }
        if (p->right)
        {
            show(p->right);
        }
    }
}
void PreOrder_rec(BinNode *p) //先序遍历递归算法
{
    if (p == NULL)
    {
        return;
    }
    else
    {
        printf("%c ", p->data);
        PreOrder_rec(p->left);
        PreOrder_rec(p->right);
    }
}
void InOrder_rec(BinNode *p) //中序遍历递归算法
{
    if (p == NULL)
    {
        return;
    }
    else
    {
        InOrder_rec(p->left);
        printf("%c ", p->data);
        InOrder_rec(p->right);
    }
}
void PostOrder_rec(BinNode *p) //后序遍历递归算法
{
    if (p == NULL)
    {
        return;
    }
    else
    {
        PostOrder_rec(p->left);
        PostOrder_rec(p->right);
        printf("%c ", p->data);
    }
}
void PreOrder_nonrec(BinNode *p)
{
    BinNode *stack[MAXSIZE];
    int top = -1;
    if (p == NULL)
    {
        return;
    }
    while (top >= 0 || p)
    {
        while (p)
        {
            printf("%c ", p->data);
            stack[++top] = p;
            p = p->left;
        }
        if (top >= 0)
        {
            p = stack[top--]->right;
        }
    }
}
void InOrder_nonrec(BinNode *p)
{
    BinNode *stack[MAXSIZE];
    int top = -1;
    if (p == NULL)
    {
        return;
    }
    while (top >= 0 || p)
    {
        while (p)
        {
            stack[++top] = p;
            p = p->left;
        }
        if (top >= 0)
        {
            printf("%c ", stack[top]->data);
            p = stack[top--]->right;
        }
    }
}
void PostOrder_nonrec(BinNode *p)
{
    BinNode *stack[MAXSIZE];
    int top = -1;
    if (p == NULL)
    {
        return;
    }
    while (top >= 0 || p)
    {
        while (p)
        {
            stack[++top] = p;
            p->flag = 1;
            p = p->left;
        }
        while (top >= 0 && stack[top]->flag == 2)
        {
            printf("%c ", stack[top]->data);
            top--;
        }
        if (top >= 0)
        {
            p = stack[top]->right;
            stack[top]->flag = 2;
        }
    }
}
void levelorder(BinNode *p) //层序遍历
{
    BinNode *queue[MAXSIZE];
    if (p == NULL)
    {
        return;
    }
    int top = -1;
    int base = 0;
    BinNode *tmp = NULL;
    queue[++top] = p;
    while (top >= base)
    {
        tmp = queue[base++];
        printf("%c ", tmp->data);
        if (tmp->left)
        {
            queue[++top] = tmp->left;
        }
        if (tmp->right)
        {
            queue[++top] = tmp->right;
        }
    }
}
int iscomtree(BinNode *p)
{
    BinNode *queue[MAXSIZE];
    if (p == NULL)
    {
        return 1;
    }
    int top = -1;
    int base = 0;
    BinNode *tmp = NULL;
    queue[++top] = p;
    int n = 0;
    int f = 0;
    while (top >= base)
    {
        tmp = queue[base++];
        if (tmp->left)
        {
            queue[++top] = tmp->left;
        }
        else if (tmp->left == NULL && f == 0)
        {
            f = 1;
            n = top + 1;
        }
        if (tmp->right)
        {
            queue[++top] = tmp->right;
        }
        else if (tmp->right == NULL && f == 0)
        {
            f = 1;
            n = top + 1;
        }
    }
    if (n > top)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int depth(BinNode *p) //求二叉树深度
{
    if (!p)
    {
        return 0;
    }
    else
    {
        int l = depth(p->left);
        int r = depth(p->right);
        return l>r? (l+1):(r+1);
    }
}
int levelwid(BinNode* p,int dep)//求二叉树某一层的宽度
{
    if(!p)return 0;
    int w=0;
    if(dep==1)
    {
        return 1;
    }
    else
    {
        w = levelwid(p->left,dep-1)+levelwid(p->right,dep-1);
    }
    return w;
}
int width(BinNode *p)//求二叉树最大宽度
{
    if(!p) return 0;
    int wid=0;
    int i;
    int d=depth(p);
    int w[d];
    memset(w,0,sizeof(int)*d);
    for(i=0;i<d;i++)
    {
        w[i]=levelwid(p,i+1);
        if(w[i]>wid) wid =w[i];
    }
    return wid;
}
//测试用例 ABD##E##C#F##
int main()
{
    BinNode *root = NULL;
    int f = 1;   //判断是否是完全二叉树（1则是，0则不是）
    int wid = 0; //存储二叉树的宽度
    printf("正确输入二叉树：");
    root = createtree(root);
    printf("\n展示二叉树：");
    show(root);
    printf("\n");
    printf("先序递归遍历：");
    PreOrder_rec(root);
    printf("\n");
    printf("中序递归遍历：");
    InOrder_rec(root);
    printf("\n");
    printf("后序递归遍历：");
    PostOrder_rec(root);
    printf("\n");
    printf("先序非递归遍历：");
    PreOrder_nonrec(root);
    printf("\n");
    printf("中序非递归遍历：");
    InOrder_nonrec(root);
    printf("\n");
    printf("后序非递归遍历：");
    PostOrder_nonrec(root);
    printf("\n");
    printf("层序遍历：");
    levelorder(root);
    printf("\n");
    printf("是否是完全二叉树？ ");
    f = iscomtree(root);
    if (f == 1)
    {
        printf("是\n");
    }
    else
    {
        printf("不是\n");
    }
    wid = width(root);
    printf("该二叉树的宽度为: %d", wid);
    return 0;
}