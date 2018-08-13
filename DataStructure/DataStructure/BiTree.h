#pragma once
template <typename T>
struct BiNode
{
    T data = T();
    BiNode *lc = nullptr;
    BiNode *rc = nullptr;
};
constexpr unsigned MAXSIZE = 100;
#define VISIT(node)           { \
    if (node)                   \
        DebugVar(node->data); }

template <typename T>
class BiTree
{
    TYPE_ALIAS(T);
    NODE_TYPE_ALIAS(BiNode<T>);
public:
    enum OrderEnum { Pre, In, Post };
    BiTree() = default;
    auto Generate(ConstPtr begin, ConstPtr end)->void;
    auto Order(OrderEnum o)const->void;
    auto PreOrder()const->void;
    auto PreOrder2()const->void;
    auto InOrder()const->void;
    auto InOrder2()const->void;
    auto PostOrder()const->void;
    auto PostOrder2()const->void;
    auto LevelOrder()const->void;
    ~BiTree();
private:
    auto preOrder(ConstNodePtr node)const->void;
    auto inOrder(ConstNodePtr node)const->void;
    auto postOrder(ConstNodePtr node)const->void;
    void free(NodePtr &node);
    NodePtr m_root = nullptr;
};

template<typename T>
inline BiTree<T>::~BiTree()
{
    free(m_root);
}

template<typename T>
auto BiTree<T>::preOrder(ConstNodePtr node) const -> void
{
    if (!node)
        return;
    DebugVar(node->data);
    preOrder(node->lc);
    preOrder(node->rc);
}

template<typename T>
auto BiTree<T>::inOrder(ConstNodePtr node) const -> void
{
    if (!node)
        return;
    inOrder(node->lc);
    DebugVar(node->data);
    inOrder(node->rc);
}

template<typename T>
auto BiTree<T>::postOrder(ConstNodePtr node) const -> void
{
    if (!node)
        return;
    postOrder(node->lc);
    postOrder(node->rc);
    DebugVar(node->data);
}

template<typename T>
void BiTree<T>::free(NodePtr & node)
{
    if (node)
    {
        free(node->lc);
        free(node->rc);
        DebugVar(node->data);
        delete node;
        node = nullptr;
    }
}

template<typename T>
auto BiTree<T>::Generate(ConstPtr begin, ConstPtr end) -> void
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
inline auto BiTree<T>::Order(OrderEnum o) const -> void
{
    switch (o)
    {
    case OrderEnum::In:
        InOrder(); return;
    case OrderEnum::Post:
        PostOrder(); return;
    case BiTree::OrderEnum::Pre:
        PreOrder(); return;
    }
}

template<typename T>
inline auto BiTree<T>::PreOrder() const -> void
{
    DebugFunc;
    preOrder(m_root);
}

template<typename T>
inline auto BiTree<T>::PreOrder2() const -> void
{
    DebugFunc;
    if (!m_root)
        return;
    NodePtr s[MAXSIZE];
    int top = -1;
    s[++top] = m_root;
    while (top > -1)
    {
        NodePtr p = s[top];
        VISIT(s[top]);
        --top;
        if (p->rc)
            s[++top] = p->rc;
        if (p->lc)
            s[++top] = p->lc;
    }
}

template<typename T>
inline auto BiTree<T>::InOrder() const -> void
{
    DebugFunc;
    inOrder(m_root);
}

template<typename T>
auto BiTree<T>::InOrder2() const -> void
{
    DebugFunc;
    if (!m_root)
        return;
    NodePtr s[MAXSIZE];
    int top = -1;
    s[++top] = m_root;
    NodePtr p = m_root->lc;
    while (top > -1 || p)
    {
        if (p)
        {
            s[++top] = p;
            p = p->lc;
        }
        else
        {
            p = s[top--];
            VISIT(p);
            p = p->rc;
        }
    }
}

template<typename T>
inline auto BiTree<T>::PostOrder() const -> void
{
    DebugFunc;
    postOrder(m_root);
}

template<typename T>
inline auto BiTree<T>::PostOrder2() const -> void
{
    DebugFunc;
    if (!m_root)
        return;
    NodePtr s1[MAXSIZE], s2[MAXSIZE];
    int top1 = -1, top2 = -1;
    s1[++top1] = m_root;
    while (top1 > -1)
    {
        NodePtr p = s1[top1--];
        s2[++top2] = p;
        if (p->lc)
            s1[++top1] = p->lc;
        if (p->rc)
            s1[++top1] = p->rc;
    }
    while (top2 > -1)
    {
        VISIT(s2[top2]);
        --top2;
    }

}

template<typename T>
inline auto BiTree<T>::LevelOrder() const -> void
{
    if (!m_root)
        return;
    NodePtr q[MAXSIZE];
    int head = 0, rear = -1;
    NodePtr p = m_root;
    q[++rear] = m_root;
    while (rear - head > -1)
    {
        p = q[head++];
        VISIT(p);
        if (p->lc)
            q[++rear] = p->lc;
        if (p->rc)
            q[++rear] = p->rc;
    }
}
