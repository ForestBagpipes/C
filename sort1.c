#include <stdio.h>
#include <stdlib.h>
void maopao(int a[], int n) //冒泡升序排序（直接）
{
    int i = 0, j = 0, tmp = 0;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n-i; j++)
        {
            if (a[j] > a[j + 1])
            {
                tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
        }
    }
    for (i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}
void xuanze(int a[], int n) //选择降序排序（直接）
{
    int max = 0, i = 0, j = 0, tmp = 0;
    for (i = 0; i < n; i++)
    {
        max = i;
        for (j = i; j < n; j++)
        {
            if (a[j] > a[max])
            {
                max = j;
            }
        }
        if (max != i)
        {
            tmp = a[i];
            a[i] = a[max];
            a[max] = tmp;
        }
    }
    for (i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}
void charu(int a[], int n) //插入升序排序（直接）
{
    for (int i = 1; i < n ; i++)
    {
        int end = i - 1;
        int key = a[i];
        while (end >= 0 && a[end] >= key)
        {
            a[end + 1] = a[end];
            end--;
        }
        a[end + 1] = key;
    }
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}
int main()
{
    int a[9] = {5, 9, 5, 3, 6, 2, 1, 4, 7};
    int n = 9;
    printf("冒泡升序直接法：");
    maopao(a, n);
    printf("\n");
    printf("选择降序直接法：");
    xuanze(a, n);
    printf("\n");
    printf("插入升序直接法：");
    charu(a, n);
    printf("\n");
    return 0;
}