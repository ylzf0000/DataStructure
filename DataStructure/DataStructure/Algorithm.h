#pragma once
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
void DFSTraverse(G &g)
{
    bool visited[MAX_G_VNUM] = { false };
    for (int i = 0; i < g.Vnum(); ++i)
        if (!visited[i])
        {
            _ZXXXE::DFS(g, i, visited);
        }
}

namespace _ZXXXE
{
    template<typename G>
    void DFS(G &g, int cur, bool(&visited)[MAX_G_VNUM])
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
}
