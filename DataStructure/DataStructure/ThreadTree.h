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
#define VISIT(node)                 {   \
        if (node)                       \
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
    // This function generate a tree by preorder sequences.
    auto Generate(ConstPtr begin, ConstPtr end);
    // This function must be called after function PreThread().
    auto PreOrder();
    auto PreThread();
    // This function must be called after function InThread().
    auto InOrder();
    auto InThread();
    // The body of this function is empty, because PostThread() is noneffective.
    auto PostOrder();
    auto PostThread();
private:
    const unsigned MAXSIZE = 100;
private:
    auto preThread(NodePtr &node, NodePtr &pre);
    auto inThread(NodePtr &node, NodePtr &pre);
    auto postThread(NodePtr &node, NodePtr &pre);
private:

    void free(NodePtr &node);
    NodePtr m_root = nullptr;
};

template<typename T>
inline ThreadTree<T>::~ThreadTree()
{
    free(m_root);
}

template<typename T>
inline auto ThreadTree<T>::Generate(ConstPtr begin, ConstPtr end)
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
inline auto ThreadTree<T>::PreThread()
{
    if (!m_root)
        return;
    NodePtr pre = nullptr;
    preThread(m_root, pre);
    pre->rc = nullptr;
    pre->rtag = 1;
}

template<typename T>
inline auto ThreadTree<T>::PreOrder()
{
    DebugFunc;
    auto firstNode = [=] {
        return m_root;
    };
    auto nextNode = [](NodePtr node) {
        if (node->ltag == 0)
            return node->lc;
        return node->rc;
    };
    for (auto p = firstNode(); p; p = nextNode(p))
    {
        VISIT(p);
    }
}

template<typename T>
inline auto ThreadTree<T>::InThread()
{
    if (!m_root)
        return;
    NodePtr pre = nullptr;
    inThread(m_root, pre);
    pre->rc = nullptr;
    pre->rtag = 1;
}

template<typename T>
inline auto ThreadTree<T>::InOrder()
{
    DebugFunc;
    auto firstNode = [](NodePtr node) {
        while (node->ltag == 0)
            node = node->lc;
        return node;
    };
    auto endNode = [](NodePtr node) {
        while (node->rtag == 0)
            node = node->rc;
        return node;
    };
    auto nextNode = [&](NodePtr node) {
        if (node->rtag == 1)
            return node->rc;
        return firstNode(node->rc);
    };
    auto preNode = [&](NodePtr node) {
        if (node->ltag == 1)
            return node->lc;
        return endNode(node->lc);
    };
    for (auto p = firstNode(m_root); p; p = nextNode(p))
    {
        VISIT(p);
    }
}

template<typename T>
inline auto ThreadTree<T>::PostThread()
{
    if (!m_root)
        return;
    NodePtr pre = nullptr;
    postThread(m_root, pre);
    pre->rc = nullptr;
    pre->rtag = 1;
}

template<typename T>
inline auto ThreadTree<T>::PostOrder()
{}

template<typename T>
inline auto ThreadTree<T>::preThread(NodePtr & node, NodePtr & pre)
{
    if (!node)
        return;
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
    if (node->ltag == 0)
        preThread(node->lc, pre);
    if (node->rtag == 0)
        preThread(node->rc, pre);
}

template<typename T>
inline auto ThreadTree<T>::inThread(NodePtr & node, NodePtr & pre)
{
    if (!node)
        return;
    inThread(node->lc, pre);
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
    inThread(node->rc, pre);
}

template<typename T>
inline auto ThreadTree<T>::postThread(NodePtr & node, NodePtr & pre)
{
    if (!node)
        return;
    inThread(node->lc, pre);
    inThread(node->rc, pre);
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