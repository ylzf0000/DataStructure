#include "Algorithm.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
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

void _ZXXXE::printConbination(int n, int k)
{
    int *stack = new int[k + 1];
    int top = k;
    for (int i = 1; i <= k; ++i)
        stack[i] = i;
    while (top >= 1)
    {
        while (stack[top] > top + n - k)
        {
            --top;
            ++stack[top];
        }
        if (top < 1)
            break;
        if (top == k)
        {
            for (int i = 1; i <= k; ++i)
                cout << stack[i] << " ";
            cout << endl;
            ++stack[top];
        }
        else
        {
            stack[top + 1] = stack[top] + 1;
            ++top;
        }
    }
    delete[] stack;
}

void _ZXXXE::printConbination2(int n, int k)
{
    int *stack = new int[k + 1];
    int top = k;
    for (int i = 1; i <= k; ++i)
        stack[i] = i;
    while (true)
    {
        for (int i = 1; i <= k; ++i)
            cout << stack[i] << " ";
        cout << endl;
        while (stack[top] >= top + n - k)
            --top;
        if (top < 1)
            break;
        ++stack[top];
        for (int i = top + 1; i <= k; ++i)
            stack[i] = stack[top] + i - top;
        top = k;
    }
    delete[] stack;
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

/*打印完全二叉树某一结点的子孙*/
void _ZXXXE::printDescendant(int a[], int n, int x)
{
    int width = 1;
    while (x <= n)
    {
        for (int i = 0; i < width && x + i <= n; ++i)
        {
            cout << a[x + i] << " ";
        }
        cout << endl;
        width *= 2;
        x *= 2;
    }
}

void _ZXXXE::printPermutation(int a[], int n, int k)
{
    if (k == n - 1)
    {
        PRINT_CONTEX(a, 0, n);
        return;
    }
    for (int i = k; i < n; ++i)
    {
        swap(a[k], a[i]);
        printPermutation(a, n, k + 1);
        swap(a[k], a[i]);
    }
}

void _ZXXXE::printPermutationDict(int n)
{
    int *a = new int[n];
    for (int i = 0; i < n; ++i)
        a[i] = i + 1;
    do
    {
        PRINT_CONTEX(a, 0, n);
    } while (nextPermutation(a, n));
    delete[] a;
}

void _ZXXXE::printPermutationDict(int a[], int n)
{
    do
    {
        PRINT_CONTEX(a, 0, n);
    } while (nextPermutation(a, n));
}

bool _ZXXXE::nextPermutation(int a[], int n)
{
    int p;
    for (p = n - 1; p >= 0 && a[p - 1] >= a[p]; --p);
    if (p == 0)
        return false;
    for (int i = p, j = n - 1; i < j; ++i, --j)
        swap(a[i], a[j]);
    int q;
    for (q = p; q < n && a[q] <= a[p - 1]; ++q);
    swap(a[p - 1], a[q]);
    return true;
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

void PrintPermutation(int n)
{
    int *a = new int[n];
    for (int i = 0; i < n; ++i)
        a[i] = i + 1;
    _ZXXXE::printPermutation(a, n, 0);
    delete[] a;
}

void PrintPermutationDict(int n)
{
    _ZXXXE::printPermutationDict(n);
}

void NSort(int a[], int n)
{
    PRINT_CONTEX(a, 1, n + 1);
    for (int i = 1; i <= n; ++i)
    {
        while (a[i] != i)
        {
            swap(a[i], a[a[i]]);
            PRINT_CONTEX(a, 1, n+1);
        }
    }
}

struct Node
{
    int data;
    Node *next;
};
/*将一个链表分为两个链表，一个包含奇数，另一个包含偶数*/
void func(Node *&a, Node *&b)
{
    b = new Node{ 0, nullptr };
    Node *p = a->next;
    Node *pa = a, *pb = b;
    while (p)
    {
        if (p->data % 2 == 0)
        {
            pb->next = p;
            pb = p;
        }
        else
        {
            pa->next = p;
            pa = p;
        }
        p = p->next;
    }
    pa->next = pb->next = nullptr;
}