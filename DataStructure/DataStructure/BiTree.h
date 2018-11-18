#pragma once
#include <functional>
#include "SqStack.h"
template <typename T>
struct BiNode
{
    T data = T();
    BiNode *lchild = nullptr;
    BiNode *rchild = nullptr;
    BiNode *parent = nullptr;
    BiNode(T _data, BiNode *_lc = nullptr, BiNode *_rc = nullptr):data(_data), lchild(_lc), rchild(_rc) {}
    //BiNode(const BiNode &node):data(node.data),lc
};
constexpr unsigned MAXSIZE = 1024;

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
    auto Width()const->int;
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
    /*为Node的parent指针赋值，并输出每个结点到根结点的路径*/
    auto SetParent()->void;
    /*输出树中值为X的层号*/
    int Level(T x);

private:
    int level(Node *node, T x);
    auto path(Node *node)->void;
    auto preOrder(Node *node, std::function<void(Node*)> cb)->void;
    auto setParent(Node *node)->Node*&;
    auto generateByPreAndIn(const T pre[], int l1, int r1, const T in[], int l2, int r2)->Node*;
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
    auto pre = preList.begin(), in = inList.begin();
    int r1 = (int)preList.size() - 1, r2 = (int)inList.size() - 1;
    m_root = generateByPreAndIn(pre, 0, r1, in, 0, r2);
}

template<typename T>
int BiTree<T>::level(Node * node, T x)
{
    if (!node)
        return 0;
    if (node->data == x)
        return 1;
    int lc = level(node->lchild, x);
    int rc = level(node->rchild, x);
    int c = lc > rc ? lc : rc;
    return (c > 0) ? c + 1 : 0;
}

template<typename T>
inline auto BiTree<T>::path(Node * node) -> void
{
    while (node)
    {
        VISIT(node);
        node = node->parent;
    }
}

template<typename T>
auto BiTree<T>::preOrder(Node * node, std::function<void(Node*)> cb) -> void
{
    if (!node)
        return;
    std::cout << node->data << "--------------------------------------\n";
    //VISIT(node);
    cb(node);
    preOrder(node->lchild, cb);
    preOrder(node->rchild, cb);
}

template<typename T>
inline auto BiTree<T>::setParent(Node * node) -> Node *&
{
    if (node->lchild)
        setParent(node->lchild) = node;
    if (node->rchild)
        setParent(node->rchild) = node;
    VISIT(node);
    return node->parent;
}

template<typename T>
auto BiTree<T>::generateByPreAndIn(const T pre[], int l1, int r1, const T in[], int l2, int r2) -> Node *
{
    /*改进版本，可能是自己写的最好的? */
    if (l1 > r1 || l2 > r2)
        return nullptr;
    Node *node = new Node{ pre[l1] };
    int pos;
    for (pos = l2; pos <= r2 && in[pos] != node->data; ++pos);
    node->lchild = generateByPreAndIn(pre, l1 + 1, l1 + pos - l2, in, l2, pos - 1);
    node->rchild = generateByPreAndIn(pre, l1 + pos - l2 + 1, r1, in, pos + 1, r2);
    return node;
}

template<typename T>
auto BiTree<T>::preOrder(ConstNodePtr node) const -> void
{
    if (!node)
        return;
    DebugVar(node->data);
    preOrder(node->lchild);
    preOrder(node->rchild);
}

template<typename T>
auto BiTree<T>::inOrder(ConstNodePtr node) const -> void
{
    if (!node)
        return;
    inOrder(node->lchild);
    DebugVar(node->data);
    inOrder(node->rchild);
}

template<typename T>
auto BiTree<T>::postOrder(ConstNodePtr node) const -> void
{
    if (!node)
        return;
    postOrder(node->lchild);
    postOrder(node->rchild);
    DebugVar(node->data);
}

template<typename T>
void BiTree<T>::free(NodePtr & node)
{
    if (node)
    {
        free(node->lchild);
        free(node->rchild);
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
        generate(node->lchild, ++begin, end);
        generate(node->rchild, ++begin, end);
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
        if ((!node->lchild) && (!node->rchild))
            ++count;
        preFunc(node->lchild, count);
        preFunc(node->rchild, count);
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
        int ld = depth(node->lchild);
        int rd = depth(node->rchild);
        return 1 + (ld > rd ? ld : rd);

    };
    return depth(m_root);
}

template<typename T>
inline auto BiTree<T>::Width() const -> int
{
    if (!m_root)
        return 0;
    NodePtr que[MAXSIZE];
    int front = 0, rear = 0;
    que[++rear] = m_root;
    NodePtr nextfirst = nullptr;
    int cnt = 0, width = 0;
    while (front != rear)
    {
        front = (front + 1) % MAXSIZE;
        NodePtr cur = que[front];
        if (cur == nextfirst)
        {
            Visit(cnt);
            width = cnt > width ? cnt : width;
            cnt = 0;
            nextfirst = nullptr;
        }
        ++cnt;
        nextfirst = (!nextfirst) ? (cur->lchild ? cur->lchild : cur->rchild) : nextfirst;
        if (cur->lchild)
        {
            rear = (rear + 1) % MAXSIZE;
            que[rear] = cur->lchild;
        }
        if (cur->rchild)
        {
            rear = (rear + 1) % MAXSIZE;
            que[rear] = cur->rchild;
        }
    }
    Visit(cnt);
    width = cnt > width ? cnt : width;
    return width;
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
        NodePtr lChild = node->lchild ? copyTree(node->lchild) : nullptr;
        NodePtr rChild = node->rchild ? copyTree(node->rchild) : nullptr;
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
        if (p->rchild)
            s[++top] = p->rchild;
        if (p->lchild)
            s[++top] = p->lchild;
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
    NodePtr p = m_root->lchild;
    while (top > -1 || p)
    {
        if (p)
        {
            s[++top] = p;
            p = p->lchild;
        }
        else
        {
            p = s[top--];
            VISIT(p);
            p = p->rchild;
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
        if (p->lchild)
            s1[++top1] = p->lchild;
        if (p->rchild)
            s1[++top1] = p->rchild;
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
        if ((!cur->lchild && !cur->rchild) || (pre && (pre == cur->lchild || pre == cur->rchild)))
        {
            VISIT(cur);
            pre = cur;
            s.Pop();
            continue;
        }
        if (cur->rchild)
            s.Push(cur->rchild);
        if (cur->lchild)
            s.Push(cur->lchild);
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
        if (p->lchild)
            q[++rear] = p->lchild;
        if (p->rchild)
            q[++rear] = p->rchild;
    }
}

template<typename T>
auto BiTree<T>::SetParent() -> void
{
    if (!m_root)
        return;
    setParent(m_root);
    auto &_1 = std::placeholders::_1;
    std::function<void(Node*)> fun = std::bind(&BiTree<T>::path, this, _1);
    preOrder(m_root, fun);
}

template<typename T>
inline int BiTree<T>::Level(T x)
{
    return level(m_root, x);
}

template class BiTree<char>;