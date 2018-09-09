#pragma once
#include <vector>
#include <iostream>

constexpr int MAX_G_VNUM = 100;
constexpr int MAX_G_ENUM = 100;
constexpr int INF = 0x7FFFFFFF;

template<typename T = int>
struct Edge
{
    int x, y;
    T val;
    friend bool operator<(const Edge &a, const Edge &b)
    {
        a.val < b.val ? a : b;
    }
    friend std::ostream& operator<<(std::ostream &os, const Edge &e)
    {
        return os << "(" << e.x << ", " << e.y << ") : " << e.val << std::endl;
    }
};

/************************************************************************/
/*    Class:         Adjacency Matrix                                   */
/*    Template Type: Vertex Type and Edge Type                          */
/************************************************************************/
template<typename ET = int>
class MGraph
{
private:
    MGraph();
public:
    template<unsigned N>
    MGraph(ET(&mat)[N][N]);
    auto adjacent(int x, int y)->ET;
    auto neighbor(int x)->std::vector<Edge<ET>>;
    /*Function insertVertex and deleteVertex is empty.*/
    auto insertVertex(int x);
    auto deleteVertex(int x);
    auto addEdge(int x, int y, ET val = 1);
    auto removeEdge(int x, int y);
    auto firstNeighbor(int x)->int;
    auto nextNeighbor(int x, int y)->int;
    auto edgeValue(int x, int y)->ET&;
    int Vnum() const { return m_vnum; }
private:
    void Vnum(int val) { m_vnum = val; }
    ET m_edge[MAX_G_ENUM][MAX_G_ENUM];
    int m_vnum;
};
template class MGraph<>;
/************************************************************************/
/*    Class        : Adjacency List                                     */
/*    Template Type: Vertex Type and Edge Type                          */
/************************************************************************/
template<typename ET = int>
class ALGraph
{
public:
    struct ANode;
    struct VNode
    {
        ANode *first = nullptr;
    };
    struct ANode
    {
        int adjvex;
        ET val = 1;
        ANode *next = nullptr;
    };
    int Vnum() const { return m_vnum; }
public:
    template<unsigned N>
    ALGraph(ET(&mat)[N][N]);
    auto adjacent(int x, int y)->ET;
    auto neighbor(int x)->std::vector<Edge<ET>>;
    /*Function insertVertex and deleteVertex is empty.*/
    auto insertVertex(int x);
    auto deleteVertex(int x);
    auto addEdge(int x, int y, ET val = 1);
    auto removeEdge(int x, int y);
    auto firstNeighbor(int x)->int;
    auto nextNeighbor(int x, int y)->int;
    auto edgeValue(int x, int y)->ET&;
private:
    void Vnum(int val) { m_vnum = val; }
    VNode  m_list[MAX_G_VNUM];
    int m_vnum;
};
template class ALGraph<>;

template<typename ET>
inline MGraph<ET>::MGraph()
{
    for (auto &c : m_edge)
        for (auto &v : c)
        {
            v = INF;
        }
    for (int i = 0; i < Vnum(); ++i)
    {
        m_edge[i][i] = 0;
    }
}

//template<typename ET>
//inline MGraph<ET>::MGraph(int vnum, ET ** mat)
//{
//    for (int i = 0; t < vnum; ++i)
//        for (int j = 0; j < vnum; ++j)
//        {
//            m_edge[i][j] = mat[i][j];
//        }
//}

template<typename ET>
inline auto MGraph<ET>::adjacent(int x, int y) -> ET
{
    return m_edge[x][y];
}

template<typename ET>
inline auto MGraph<ET>::neighbor(int x) -> std::vector<Edge<ET>>
{
    DebugFunc;
    std::vector<Edge<ET>> vec;
    for (int i = 0; i < Vnum(); ++i)
    {
        int val = m_edge[x][i];
        if (val < INF && val != 0)
            vec.push_back({ x,i,val });
    }
    return vec;
}

template<typename ET>
inline auto MGraph<ET>::insertVertex(int x)
{
}

template<typename ET>
inline auto MGraph<ET>::deleteVertex(int x)
{
}

template<typename ET>
inline auto MGraph<ET>::addEdge(int x, int y, ET val)
{
    m_edge[x][y] = val;
}

template<typename ET>
inline auto MGraph<ET>::removeEdge(int x, int y)
{
    m_edge[x][y] = INF;
}

template<typename ET>
inline auto MGraph<ET>::firstNeighbor(int x) -> int
{
    for (int i = 0; i < Vnum(); ++i)
    {
        int val = m_edge[x][i];
        if (val < INF && val != 0)
            return i;
    }
    return -1;
}

template<typename ET>
inline auto MGraph<ET>::nextNeighbor(int x, int y)->int
{
    for (int i = y + 1; i < Vnum(); ++i)
    {
        int val = m_edge[x][i];
        if (val < INF && val != 0)
            return i;
    }
    return -1;
}

template<typename ET>
inline auto MGraph<ET>::edgeValue(int x, int y) -> ET &
{
    return m_edge[x][y];
}

template<typename ET>
template<unsigned N>
inline MGraph<ET>::MGraph(ET(&mat)[N][N])
{
    Vnum(N);
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
        {
            m_edge[i][j] = mat[i][j];
        }
}

template<typename ET>
inline auto ALGraph<ET>::adjacent(int x, int y) -> ET
{
    for (ANode * node = m_list[x].first; node; node = node->next)
    {
        if (node->adjvex == y)
            return node->val;
    }
    return INF;
}

template<typename ET>
inline auto ALGraph<ET>::neighbor(int x) -> std::vector<Edge<ET>>
{
    std::vector<Edge<ET>> vec;
    for (ANode *node = m_list[x].first; node; node = node->next)
    {
        vec.push_back({ x,node->adjvex,node->val });
    }
    return vec;
}

template<typename ET>
inline auto ALGraph<ET>::addEdge(int x, int y, ET val)
{
    ANode *lastFist = m_list[x].first;
    ANode *newNode = new ANode{ y, val, lastFist };
    m_list[x].first = newNode;
}

template<typename ET>
inline auto ALGraph<ET>::removeEdge(int x, int y)
{
    for (ANode *node = m_list[x].first, *pre = node; node;
        pre = node, node = node->next)
    {
        if (node->adjvex == y)
        {
            pre->next = node->next;
            delete node;
            node = node->next;
        }
    }
}

template<typename ET>
inline auto ALGraph<ET>::firstNeighbor(int x) -> int
{
    ANode *node = m_list[x].first;
    if (!node)
        return -1;
    return node->adjvex;
}

template<typename ET>
inline auto ALGraph<ET>::nextNeighbor(int x, int y) -> int
{
    static int lastX = x;
    static ANode *lastNode = m_list[x].first;
    for (ANode *node = lastNode; node; node = node->next)
    {
        if (node->adjvex == y)
        {
            if (!(node->next))
                break;
            lastX = x;
            lastNode = node;
            return node->next->adjvex;
        }
    }
    return -1;
}

template<typename ET>
inline auto ALGraph<ET>::edgeValue(int x, int y) -> ET &
{
    for (ANode *node = m_list[x].first; node; node = node->next)
    {
        if (node->adjvex == y)
            return node->val;
    }
}

template<typename ET>
template<unsigned N>
inline ALGraph<ET>::ALGraph(ET(&mat)[N][N])
{
    Vnum(N);
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
        {
            int val = mat[i][j];
            if (val == INF || val == 0)
                continue;
            ANode *lastFist = m_list[i].first;
            ANode *newNode = new ANode{ j, val, lastFist };
            m_list[i].first = newNode;
        }
}
