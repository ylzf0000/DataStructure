#pragma once
#include <vector>
#include <iostream>

constexpr int MAXVNUM = 100;
constexpr int MAXENUM = 100;
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
    //MGraph(int vnum, ET **mat);
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
    ET m_edge[MAXENUM][MAXENUM];
    int m_vnum;
};

/************************************************************************/
/*    Class        : Adjacency List                                     */
/*    Template Type: Vertex Type and Edge Type                          */
/************************************************************************/
template<typename ET>
class ALGraph
{

public:
    struct ANode;
    struct VNode
    {
        ANode *first;
    };
    struct ANode
    {
        int adjvex;
        ANode *next;
        ET val;
    };

private:
    VNode  m_list[MAXVNUM];
    int m_vnum;
    int m_arcnum;
};

template<typename ET>
inline MGraph<ET>::MGraph()
{
    for (auto &c : m_edge)
        for (auto &v : c)
        {
            v = INF;
        }
    for (int i = 0; i < m_vnum; ++i)
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
    for (int i = 0; i < m_vnum; ++i)
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
    for (int i = 0; i < m_vnum; ++i)
    {
        if (m_edge[x][i] < INF)
            return i;
    }
    return -1;
}

template<typename ET>
inline auto MGraph<ET>::nextNeighbor(int x, int y)->int
{
    for (int i = y + 1; i < m_vnum; ++i)
    {
        if (m_edge[x][y] < INF)
        {
            return m_edge[x][y];
        }
    }
    return -1;
}

template<typename ET>
inline auto MGraph<ET>::edgeValue(int x, int y) -> ET &
{
    return m_edge[x][y];
}

template class MGraph<>;

template<typename ET>
template<unsigned N>
inline MGraph<ET>::MGraph(ET(&mat)[N][N])
{
    m_vnum = N;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
        {
            m_edge[i][j] = mat[i][j];
        }
}
