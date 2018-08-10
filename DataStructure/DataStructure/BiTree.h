#pragma once
template <typename T>
struct BiNode
{
    T data = T();
    BiNode *lc = nullptr;
    BiNode *rc = nullptr;
};
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
    auto InOrder()const->void;
    auto PostOrder()const->void;
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
inline auto BiTree<T>::InOrder() const -> void
{
    DebugFunc;
    inOrder(m_root);
}

template<typename T>
inline auto BiTree<T>::PostOrder() const -> void
{
    DebugFunc;
    postOrder(m_root);
}