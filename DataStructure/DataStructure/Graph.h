#pragma once

/************************************************************************/
/*    Class:         Adjacency Matrix                                   */
/*    Template Type: Vertex Type and Edge Type                          */
/************************************************************************/
template<typename VT, typename ET>
class MGraph
{
private:
    VT * m_vex;
    ET **m_edge;
    int m_vnum;
    int m_enum;
};

/************************************************************************/
/*    Class        : Adjacency List                                     */
/*    Template Type: Vertex Type and Edge Type                          */
/************************************************************************/
template<typename VT, typename ET>
class ALGraph
{
public:
    struct ANode;
    struct VNode
    {
        VT data;
        ANode *first;
    };
    struct ANode
    {
        int adjvex;
        ANode *next;
        ET data;
    };
private:
    VNode * m_list;
    int m_vnum;
    int m_arcnum;
};