#include "Algorithm.h"
#include <algorithm>
#include <iostream>
using namespace std;
int _ZXXXE::partition(int a[], int low, int high)
{
    if (low > high)
        return -1;
    int i = low, j = high;
    int tmp = a[i];
    while (i < j)
    {
        while (i < j && tmp <= a[j])
            --j;
        a[i] = a[j];
        while (i < j && a[i] <= tmp)
            ++i;
        a[j] = a[i];
    }
    a[i] = tmp;
    return i;
}

void _ZXXXE::qsort(int a[], int low, int high)
{
    if (low > high)
        return;
    int i = low, j = high;
    int tmp = a[i];
    while (i < j)
    {
        while (i < j && tmp <= a[j])
            --j;
        a[i] = a[j];
        while (i < j && a[i] <= tmp)
            ++i;
        a[j] = a[i];
    }
    a[i] = tmp;
    qsort(a, low, i - 1);
    qsort(a, i + 1, high);
}

int _ZXXXE::kBigNo(int a[], int low, int high, int k)
{
    if (low > high || k < low || k > high)
        return -1;
    int i = low, j = high;
    int tmp = a[i];
    while (i < j)
    {
        while (i < j && tmp >= a[j])
            --j;
        a[i] = a[j];
        while (i < j && a[i] >= tmp)
            ++i;
        a[j] = a[i];
    }
    a[i] = tmp;
    PRINT_CONTEX(a, 0, 13);
    if (i < k)
        return kBigNo(a, i + 1, high, k);
    if (k < i)
        return kBigNo(a, low, i - 1, k);
    return a[i];
}

void _ZXXXE::printConbinationRec(int n, int k, int r, int cur, int *arr)
{
    arr[r] = cur;
    if (r == k)
    {
        for (int i = 1; i <= k; ++i)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
        return;
    }
    for (int i = cur + 1; i <= n; ++i)
    {
        printConbinationRec(n, k, r + 1, i, arr);
    }
}

void PrintConbinationRec(int n, int k)
{
    int *arr = new int[k + 1];
    for (int i = 1; i <= n - k + 1; ++i)
    {
        _ZXXXE::printConbinationRec(n, k, 1, i, arr);
    }
    delete[] arr;
}
