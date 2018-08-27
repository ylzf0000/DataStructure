#pragma once
#include <functional>
#include "SqStack.h"
template <typename T>
struct BiNode
{
    T data = T();
    BiNode *lc = nullptr;
    BiNode *rc = nullptr;
    BiNode(T _data, BiNode *_lc = nullptr, BiNode *_rc = nullptr) :data(_data), lc(_lc), rc(_rc) {}
    //BiNode(const BiNode &node):data(node.data),lc
};
constexpr unsigned MAXSIZE = 100;

#ifndef VISIT
#define VISIT(node)           { \
    if (node)                   \
        DebugVar(node->data); }
#endif // !VISIT

template <typename T>
class BiTree
{
    TYPE_ALIAS(T);
    NODE_TYPE_ALIAS(BiNode<T>);
public:
    enum OrderEnum { Pre, In, Post };
    BiTree() = default;
    ~BiTree();
    auto GenerateByPreAndIn(std::initializer_list<T> preList, decltype(preList) inList)->void;
    auto Generate(ConstPtr begin, ConstPtr end)->void;
    /* Count the number of leaf nodes in this BiTree. */
    auto CountLeaf()const->int;
    auto Depth()const->int;
    auto Copy(BiTree &newTree)const;
    auto Order(OrderEnum o)const->void;
    auto PreOrder()const->void;
    auto PreOrder2()const->void;
    auto InOrder()const->void;
    auto InOrder2()const->void;
    auto PostOrder()const->void;
    auto PostOrder2()const->void;
    auto PostOrder3()const->void;
    auto LevelOrder()const->void;

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
    DebugFunc;
    free(m_root);
}

template<typename T>
inline auto BiTree<T>::GenerateByPreAndIn(std::initializer_list<T> preList, decltype(preList) inList) -> void
{
    using iter = typename std::initializer_list<T>::const_iterator;
    using funcType = std::function<void(iter, iter, iter, iter, NodePtr&, bool)>;
    /*сп╢Щ╦д╫Ь*/
    funcType gen = [=, &gen](iter preBegin, iter preEnd, iter inBegin, iter inEnd, 
        NodePtr &parent, bool left)
    {
        if (!(preBegin < preEnd) || !(inBegin < inEnd))
            return;
        auto val = *preBegin;
        DebugVar(val);
        NodePtr node = new Node{ val };
        if (!parent)
            parent = node;
        else
        {
            if (left)
                parent->lc = node;
            else
                parent->rc = node;
        }
        iter newInEnd1 = inBegin;
        while (newInEnd1 != inEnd && *newInEnd1 != val)
            ++newInEnd1;
        iter newPreBegin2;
        for (newPreBegin2 = preBegin + 1; newPreBegin2 != preEnd; ++newPreBegin2)
        {
            iter it;
            for (it = newInEnd1; it != inEnd && *it != *newPreBegin2; ++it);
            if (it != inEnd)
                break;
        }
        gen(preBegin + 1, newPreBegin2, inBegin, newInEnd1, node, true);
        gen(newPreBegin2, preEnd, newInEnd1 + 1, inEnd, node, false);
    };
    m_root = nullptr;
    gen(preList.begin(), preList.end(), inList.begin(), inList.end(), m_root, true);

    //PreOrder();
    //InOrder();
    //PostOrder();
    //InOrder2();
    //PostOrder2();
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
        //DebugVar(node->data);
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
inline auto BiTree<T>::CountLeaf() const -> int
{
    std::function<void(NodePtr, int&)> preFunc = [&preFunc]
    (NodePtr node, int &count) {
        if (!node)
            return;
        if ((!node->lc) && (!node->rc))
            ++count;
        preFunc(node->lc, count);
        preFunc(node->rc, count);
    };
    int n = 0;
    preFunc(m_root, n);
    return n;
}

template<typename T>
inline auto BiTree<T>::Depth() const -> int
{
    std::function<int(NodePtr)> depth = [&depth]
    (NodePtr node) {
        if (!node)
            return 0;
        int ld = depth(node->lc);
        int rd = depth(node->rc);
        return 1 + (ld > rd ? ld : rd);

    };
    return depth(m_root);
}

template<typename T>
inline auto BiTree<T>::Copy(BiTree & newTree) const
{
    auto copyNode = [](T val, NodePtr lc, NodePtr rc) {
        NodePtr newNode = new Node{ val,lc,rc };
        return newNode;
    };
    std::function<NodePtr(ConstNodePtr)> copyTree =
        [&copyNode, &copyTree](ConstNodePtr node)->NodePtr {
        if (!node)
            return nullptr;
        NodePtr lChild = node->lc ? copyTree(node->lc) : nullptr;
        NodePtr rChild = node->rc ? copyTree(node->rc) : nullptr;
        return copyNode(node->data, lChild, rChild);
    };
    if (!m_root)
        return;
    newTree.m_root = copyTree(m_root);
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
inline auto BiTree<T>::PostOrder3() const -> void
{
    DebugFunc;
    if (!m_root)
        return;
    SqStack<NodePtr> s;
    s.Push(m_root);
    NodePtr cur = nullptr;
    NodePtr pre = nullptr;
    while (!s.IsEmpty())
    {
        cur = s.Top();
        if ((!cur->lc && !cur->rc) || (pre && (pre == cur->lc || pre == cur->rc)))
        {
            VISIT(cur);
            pre = cur;
            s.Pop();
            continue;
        }
        if (cur->rc)
            s.Push(cur->rc);
        if (cur->lc)
            s.Push(cur->lc);
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

template class BiTree<int>;