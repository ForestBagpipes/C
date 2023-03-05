#include <stdio.h>
#include <stdlib.h>
void maopao(int a[], int n) //递归实现冒泡升序排序
{
    int i = 0, tmp = 0;
    if (n == 1)
    {
        printf("%d ", a[n - 1]);
        return;
    }
    else
    {
        for (i = 0; i < n; i++)
        {
            if (a[i] > a[i + 1])
            {
                tmp = a[i];
                a[i] = a[i + 1];
                a[i + 1] = tmp;
            }
        }
        maopao(a, n - 1);
        printf("%d ", a[n - 1]);
    }
}
void xuanze(int a[], int n) //递归实现选择降序排序
{
    int min = n - 1, i = 0;
    if (n == 1)
    {
        printf("%d ", a[n - 1]);
        return;
    }
    else
    {
        for (i = 0; i < n; i++)
        {
            if (a[i] < a[min])
            {
                min = i;
            }
        }
        int tmp = 0;
        if (min != n - 1)
        {
            tmp = a[n - 1];
            a[n - 1] = a[min];
            a[min] = tmp;
        }
        xuanze(a, n - 1);
        printf("%d ", a[n - 1]);
    }
}
void charu(int a[], int n) //递归实现插入升序排序
{
    int end = 0, key = 0;
    if (n == 1)
    {
        return;
    }
    else
    {
        charu(a, n - 1);
        key = a[n - 1];
        end = n - 2;
        while (end >= 0 && key < a[end])
        {
            a[end + 1] = a[end];
            end--;
        }
        a[end + 1] = key;
    }
}
int main()
{
    int a[9] = {2, 9, 5, 5, 6, 4, 7, 3, 8};
    int n = 9;
    printf("冒泡升序递归法：");
    maopao(a, n);
    printf("\n");
    printf("选择降序递归法：");
    xuanze(a, n);
    printf("\n");
    printf("插入升序递归法：");
    charu(a, n);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}