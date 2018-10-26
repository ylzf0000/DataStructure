#pragma once
#include "stdafx.h"
#include <string>
#include <iostream>
#include "Graph.h"
template<class Con1, class Con2>
void Union(Con1 &a, const Con2 &b)
{
    for (const auto &v : b)
    {
        if (!a.Find(v))
            a << v;
    }
}

template<class Con>
void Merge(const Con &a, const Con &b, Con &c)
{
    c.Clear();
    auto pa = a.begin();
    auto pb = b.begin();
    while (pa != a.end() && pb != b.end())
    {
        if (*pa <= *pb)
        {
            c << *pa;
            ++pa;
        }
        else
        {
            c << *pb;
            ++pb;
        }
    }
    while (pa != a.end())
    {
        c << *pa;
        ++pa;
    }
    while (pb != b.end())
    {
        c << *pb;
        ++pb;
    }
}

template<typename G>
void DFSTraverse(const G &g)
{
    bool visited[MAX_G_VNUM] = { false };
    for (int i = 0; i < g.Vnum(); ++i)
        if (!visited[i])
        {
            _ZXXXE::DFS(g, i, visited);
        }
}

template<typename G>
void BFSTraverse(const G &g)
{
    bool visited[MAX_G_VNUM] = { false };
    for (int i = 0; i < g.Vnum(); ++i)
        if (!visited[i])
        {
            _ZXXXE::BFS(g, i, visited);
        }
}

//ÍØÆËÅÅÐò
template<typename G>
void TopSort(const G &g, int cur)
{
    bool visited[MAX_G_VNUM] = { false };
    int q[MAX_G_VNUM] = { 0 };
    int size = -1;
    _ZXXXE::TopologicalSort(g, cur, visited, q, size);
    for (int i = size; i >= 0; --i)
    {
        int cur = q[i];
        DebugVar(cur);
    }
}

template<unsigned N, typename T>
void HeapSort(T(&a)[N])
{
    PRINT_CONT(a);
    //_ZXXXE::heapSort(a, N);
    PRINT_CONT(a);
}

namespace _ZXXXE
{
    template<typename G>
    void DFS(const G &g, int cur, bool(&visited)[MAX_G_VNUM])
    {
        visited[cur] = true;
        DebugVar(cur);
        for (int i = g.firstNeighbor(cur); i != -1; i = g.nextNeighbor(cur, i))
        {
            if (!visited[i])
            {
                DFS(g, i, visited);
            }
        }
    }

    template<typename G>
    void TopologicalSort(const G &g, int cur, bool(&visited)[MAX_G_VNUM], int *queue, int &q_cur)
    {
        visited[cur] = true;
        for (int i = g.firstNeighbor(cur); i != -1; i = g.nextNeighbor(cur, i))
        {
            if (!visited[i])
            {
                TopologicalSort(g, i, visited, queue, q_cur);
            }
        }
        queue[++q_cur] = cur;
        //DebugVar(cur);
    }

    template<typename G>
    void BFS(const G &g, int cur, bool(&visited)[MAX_G_VNUM])
    {
        int q[MAX_G_VNUM] = { 0 };
        int front = 0, tail = -1;
        q[++tail] = cur;
        visited[cur] = true;
        DebugVar(cur);
        while (tail - front >= 0)
        {
            int node = q[++front];
            for (int i = g.firstNeighbor(node); i != -1; i = g.nextNeighbor(node, i))
            {
                if (!visited[i])
                {
                    visited[i] = true;
                    cur = i;
                    DebugVar(cur);
                    q[++tail] = i;
                }
            }
        }
    }

    //void shift(int a[], int left, int right)
    //{
    //    int tmp = a[left];
    //    int i = left;
    //    int j = i * 2 + 1;
    //    for (; j <= right; i = j, j = i * 2 + 1)
    //    {
    //        if (j + 1 <= right && a[j] < a[j + 1])
    //            ++j;
    //        if (tmp < a[j])
    //            a[i] = a[j];
    //        else
    //            break;
    //    }
    //    a[i] = tmp;
    //}

    //void heapSort(int a[], int n)
    //{
    //    for (int i = n / 2 - 1; i >= 0; --i)
    //    {
    //        shift(a, i, n - 1);
    //    }
    //    for (int i = 0; i < n - 1; ++i)
    //    {
    //        int j = n - i - 1;
    //        int tmp = a[0];
    //        a[0] = a[j];
    //        a[j] = tmp;
    //        shift(a, 0, j - 1);
    //    }
    //}

    //void kBigHeapSort(int a[], int n, int k)
    //{
    //    for (int i = n / 2 - 1; i >= 0; --i)
    //    {
    //        shift(a, i, n - 1);
    //    }
    //    for (int i = 0; i < k; ++i)
    //    {
    //        int j = n - i - 1;
    //        int tmp = a[0];
    //        a[0] = a[j];
    //        a[j] = tmp;
    //        shift(a, 0, j - 1);
    //    }
    //    DebugVar(a[n - k]);
    //}

    int partition(int a[], int low, int high);
    void qsort(int a[], int low, int high);
    int kBigNo(int a[], int low, int high, int k);
}

template<unsigned N>
int Partition(int(&a)[N])
{
    return _ZXXXE::partition(a, 0, N - 1);
}

template<unsigned N>
void Sort(int(&a)[N])
{
    _ZXXXE::qsort(a, 0, N - 1);
}

template<unsigned N>
int kBigNo(int(&a)[N], int k)
{
    return _ZXXXE::kBigNo(a, 0, N - 1, k - 1);
}