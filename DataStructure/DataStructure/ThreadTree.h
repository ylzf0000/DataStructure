#pragma once
template <typename T>
struct ThreadNode
{
    T data = T();
    ThreadNode *lc = nullptr;
    ThreadNode *rc = nullptr;
    int ltag, rtag; //0 is child, 1 is pre or next
};

#ifndef VISIT
#define VISIT(node)                 { \
        if (node)                   \
            DebugVar(node->data);   }
#endif // VISIT

template <typename T>
class ThreadTree
{
    TYPE_ALIAS(T);
    NODE_TYPE_ALIAS(ThreadNode<T>);
public:
    ThreadTree() = default;
    ~ThreadTree();
    auto Generate(ConstPtr begin, ConstPtr end)->void;
    auto InOrder()->void;
    auto InOrder2()->void;
    auto FirstNode(NodePtr node);
    auto EndNode(NodePtr node);
    auto NextNode(NodePtr node);
    auto PreNode(NodePtr node);
private:
    const unsigned MAXSIZE = 100;
    auto inOrder(NodePtr &node, NodePtr &pre)->void;
    void free(NodePtr &node);
    NodePtr m_root = nullptr;
};

template<typename T>
inline ThreadTree<T>::~ThreadTree()
{
    free(m_root);
}

template<typename T>
inline auto ThreadTree<T>::Generate(ConstPtr begin, ConstPtr end) -> void
{
    std::function<void(NodePtr&, ConstPtr&, ConstPtr)>
        generate = [&generate](NodePtr &node, ConstPtr &begin, ConstPtr end)
    {
        if (begin >= end)
            return;
        if (*begin == Elem())
            return;
        node = new Node{ *begin };
        generate(node->lc, ++begin, end);
        generate(node->rc, ++begin, end);
    };
    generate(m_root, begin, end);
}

template<typename T>
inline auto ThreadTree<T>::InOrder() -> void
{
    if (!m_root)
        return;
    NodePtr pre = nullptr;
    inOrder(m_root, pre);
    pre->rc = nullptr;
    pre->rtag = 1;
}

// This function must be called after function InOrder().
template<typename T>
inline auto ThreadTree<T>::InOrder2() -> void
{
    DebugFunc;
    for (auto p = FirstNode(m_root); p; p = NextNode(p))
    {
        VISIT(p);
    }
    //for (auto p = EndNode(m_root); p; p = PreNode(p))
    //{
    //    VISIT(p);
    //}
}

template<typename T>
inline auto ThreadTree<T>::FirstNode(NodePtr node)
{
    while (node->ltag == 0)
        node = node->lc;
    return node;
}

template<typename T>
inline auto ThreadTree<T>::EndNode(NodePtr node)
{
    while (node->rtag == 0)
        node = node->rc;
    return node;
}

template<typename T>
inline auto ThreadTree<T>::NextNode(NodePtr node)
{
    if (node->rtag == 1)
        return node->rc;
    return FirstNode(node->rc);
}

template<typename T>
inline auto ThreadTree<T>::PreNode(NodePtr node)
{
    if (node->ltag == 1)
        return node->lc;
    return EndNode(node->lc);
}

template<typename T>
inline auto ThreadTree<T>::inOrder(NodePtr & node, NodePtr & pre) -> void
{
    if (!node)
        return;
    inOrder(node->lc, pre);
    VISIT(node);
    if (!node->lc)
    {
        node->lc = pre;
        node->ltag = 1;
    }
    if (pre && !pre->rc)
    {
        pre->rc = node;
        pre->rtag = 1;
    }
    pre = node;
    inOrder(node->rc, pre);
}

template<typename T>
inline void ThreadTree<T>::free(NodePtr & node)
{
    if (node)
    {
        if (node->lc && (node->ltag == 0))
            free(node->lc);
        if (node->rc && (node->rtag == 0))
            free(node->rc);
        DebugVar(node->data);
        delete node;
        node = nullptr;
    }
}

template class ThreadTree<int>;