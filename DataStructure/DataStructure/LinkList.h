#pragma once
#include <string>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <functional>
#include "LinkBase.h"
template<typename T>
class LinkList
{
	TYPE_ALIAS(T);
	NODE_TYPE_ALIAS(SNode<T>);
public:
	LinkList();
	~LinkList();

	auto HeadCreate() -> void;
	auto TailCreate() -> void;

	auto Length() const -> int;
	auto Find(ConstRef e) const ->int;

	auto At(int i) const->ConstNodeRef;
	auto At(int i)->NodeRef;
	auto operator[](int i) const->ConstNodeRef;
	auto operator[](int i)->NodeRef;

	auto Insert(int i, ConstRef e) -> void;
	auto PushBack(ConstRef e) -> void;
	auto Remove(int i) -> void;
	auto PopBack(Ptr e = nullptr) -> void;

	auto IsEmpty() const -> bool;
	auto Clear() -> void;

	auto operator<<(ConstRef v)->LinkList&;

	auto begin()->NodePtr;
	auto begin() const->ConstNodePtr;
	auto end()->NodePtr;
	auto end() const->ConstNodePtr;

	auto Merge(LinkList &b)->void;
	auto MergeEx(LinkList &b)->void;
	auto Reverse()->void;
	auto ReversePrint()->void;
	auto Unique()->void;
	auto Sort()->void;
	auto Sort(std::function<bool(ConstRef, ConstRef)> comp)->void;
	template<template<class T> class Comp = std::less> auto TSort()->void;

	//auto Front() const->ConstRef;
	//auto Front()->Ref;
	//auto Back() const->ConstRef;
	//auto Back()->Ref;

	friend std::ostream& operator<<(std::ostream &os, const LinkList &self)
	{
		Node *node = self.m_headNode->next;
		while (node)
		{
			os << node->data << " ";
			node = node->next;
		}
		os << std::endl;
		return os;
	}
private:
	template <int C = 0>
	auto AssertRange(int i) const -> void
	{
		assert(i >= 0 && i < m_length);
	}

	template <>
	auto AssertRange<1>(int i) const -> void
	{
		assert(i >= 0 && i <= m_length);
	}

	auto Free() -> void;

	NodePtr m_headNode; // 头指针！，*m_headNode为头结点
	int m_length = 0;
};

template<typename T>
inline LinkList<T>::LinkList()
{
	m_headNode = new Node();
}

template<typename T>
inline LinkList<T>::~LinkList()
{
	DebugFunc;
	Free();
}

template<typename T>
void LinkList<T>::HeadCreate()
{
	T val;
	while (cin >> val)
	{
		Node *node = new Node{ val };
		node->next = m_headNode->next;
		m_headNode->next = node;
		++m_length;
	}
}

template<typename T>
void LinkList<T>::TailCreate()
{
	T val;
	Node *tail = m_headNode;
	//for (tail = m_headNode; tail->next; tail = tail->next);
	while (cin >> val)
	{
		Node *node = new Node{ val };
		tail->next = node;
		tail = node;
		++m_length;
	}
}

template<typename T>
inline auto LinkList<T>::Length() const -> int
{
	return m_length;
}

template<typename T>
inline auto LinkList<T>::Find(ConstRef e) const -> int
{
	int i = 0;
	for (Node *node = m_headNode->next; node; node = node->next, ++i)
	{
		if (node->data == e)
			return i;
	}
	return i;
}

template<typename T>
auto LinkList<T>::At(int i) const -> ConstNodeRef
{
	AssertRange(i);
	Node *node = m_headNode->next;
	for (int idx = 0; idx < i&&node; ++idx, node = node->next);
	return *node;
}

template<typename T>
inline auto LinkList<T>::At(int i) -> NodeRef
{
	return const_cast<NodeRef>(const_cast<const LinkList*>(this)->At(i));
}

template<typename T>
inline auto LinkList<T>::operator[](int i) const -> ConstNodeRef
{
	return At(i);
}

template<typename T>
inline auto LinkList<T>::operator[](int i) -> NodeRef
{
	return At(i);
}

template<typename T>
inline auto LinkList<T>::Insert(int i, ConstRef e) -> void
{
	AssertRange<1>(i);
	Node *node = m_headNode;
	for (int idx = 0; idx < i; ++idx, node = node->next);
	Node *newNode = new Node{ e };
	newNode->next = node->next;
	node->next = newNode;
	++m_length;
}

template<typename T>
inline auto LinkList<T>::PushBack(ConstRef e) -> void
{
	Insert(m_length, e);
}

template<typename T>
inline auto LinkList<T>::Remove(int i) -> void
{
	AssertRange(i);
	Node *node = m_headNode->next;
	for (int idx = 0; idx < i - 1; ++idx, node = node->next);
	Node *tmp = node->next;
	node->next = tmp->next;
	delete tmp;
	--m_length;
}

template<typename T>
inline auto LinkList<T>::PopBack(Ptr e) -> void
{
	Remove(m_length - 1);
}

template<typename T>
inline auto LinkList<T>::IsEmpty() const -> bool
{
	return m_length == 0;
}

template<typename T>
inline auto LinkList<T>::Clear() -> void
{
	Free();
}

template<typename T>
inline auto LinkList<T>::operator<<(ConstRef v) -> LinkList&
{
	PushBack(v);
	return *this;
}

template<typename T>
inline auto LinkList<T>::begin() -> NodePtr
{
	return m_headNode->next;
}

template<typename T>
inline auto LinkList<T>::begin() const -> ConstNodePtr
{
	return m_headNode->next;
}

template<typename T>
inline auto LinkList<T>::end() -> NodePtr
{
	return nullptr;
}

template<typename T>
inline auto LinkList<T>::end() const -> ConstNodePtr
{
	return nullptr;
}

template<typename T>
auto LinkList<T>::Merge(LinkList & b) -> void
{
	NodePtr p = m_headNode;
	NodePtr pa = m_headNode->next;
	NodePtr pb = b.m_headNode->next;
	while (pa && pb)
	{
		if (pa->data <= pb->data)
		{
			p->next = pa;
			p = pa;
			pa = pa->next;

		}
		else
		{
			p->next = pb;
			p = pb;
			pb = pb->next;
		}
	}
	p->next = pa ? pa : pb;
	b.m_headNode->next = nullptr;
}

template<typename T>
auto LinkList<T>::MergeEx(LinkList & b) -> void
{
	NodePtr pa = m_headNode->next;
	NodePtr pb = b.m_headNode->next;
	NodePtr tmp = nullptr;
	m_headNode->next = nullptr;
	while (pa&&pb)
	{
		/*头插法，每次插入最小的结点即可！*/
		if (pa->data <= pb->data)
		{
			tmp = pa->next;
			pa->next = m_headNode->next;
			m_headNode->next = pa;
			pa = tmp;
		}
		else
		{
			tmp = pb->next;
			pb->next = m_headNode->next;
			m_headNode->next = pb;
			pb = tmp;
		}
		DebugVar(*this); 
	}
	if (pa)
		pb = pa;
	//while (pa)
	//{
	//	tmp = pa->next;
	//	pa->next = m_headNode->next;
	//	m_headNode->next = pa;
	//	pa = tmp;
	//	DebugVar(*this);
	//}
	while (pb)
	{
		tmp = pb->next;
		pb->next = m_headNode->next;
		m_headNode->next = pb;
		pb = tmp;
		DebugVar(*this);
	}
	b.m_headNode->next = nullptr;
}

template<typename T>
auto LinkList<T>::Reverse() -> void
{
	NodePtr p1 = m_headNode->next;
	NodePtr p2 = p1->next;
	NodePtr p;
	p1->next = nullptr;
	while (p1&&p2)
	{
		p = p2->next;
		p2->next = p1;
		p1 = p2;
		p2 = p;
	}
	m_headNode->next = p1;
}

template<typename T>
auto LinkList<T>::ReversePrint() -> void
{
	std::function<void(ConstNodePtr)> print = [&print](ConstNodePtr p) {
		if (p->next)
		{
			print(p->next);
		}
		std::cout << p->data << " ";
	};
	print(m_headNode->next);
	std::cout << std::endl;

}

template<typename T>
auto LinkList<T>::Unique() -> void
{
	for (NodePtr p = m_headNode->next; p && p->next;)
	{
		if (p->data == p->next->data)
		{
			NodePtr p2 = p->next;
			p->next = p2->next;
			delete p2;
			--m_length;
		}
		else
		{
			p = p->next;
		}
	}
}

//************************************
// Method:    Sort
// Desc:      选择排序
// FullName:  LinkList<T>::Sort
// Access:    public 
// Returns:   auto
// Qualifier: -> void
//************************************
template<typename T>
auto LinkList<T>::Sort() -> void
{
	for (NodePtr i = m_headNode; i&&i->next; i = i->next)
	{
		NodePtr preMinP = i;
		for (NodePtr j = i; j&&j->next; j = j->next)
		{
			if (j->next->data < preMinP->next->data)
			{
				preMinP = j;
			}
		}
		NodePtr minP = preMinP->next;
		preMinP->next = minP->next ? minP->next : nullptr;
		minP->next = i->next;
		DebugVar(minP->data);
		i->next = minP;
		DebugVar(*this);
	}
}

template<typename T>
auto LinkList<T>::Sort(std::function<bool(ConstRef, ConstRef)> comp) -> void
{
	for (NodePtr i = m_headNode; i&&i->next; i = i->next)
	{
		NodePtr preMinP = i;
		for (NodePtr j = i; j&&j->next; j = j->next)
		{
			if (comp(j->next->data, preMinP->next->data))
			{
				preMinP = j;
			}
		}
		NodePtr minP = preMinP->next;
		preMinP->next = minP->next ? minP->next : nullptr;
		minP->next = i->next;
		DebugVar(minP->data);
		i->next = minP;
		DebugVar(*this);
	}
}

template<typename T>
auto LinkList<T>::Free() -> void
{
	Node *node = m_headNode;
	while (node)
	{
		Node *next = node->next;
		delete node;
		--m_length;
		node = next;
	}
}

template<typename T>
template<template<class T> class Comp>
inline auto LinkList<T>::TSort() -> void
{
	for (NodePtr i = m_headNode; i&&i->next; i = i->next)
	{
		NodePtr preMinP = i;
		for (NodePtr j = i; j&&j->next; j = j->next)
		{
			if (Comp<T>()(j->next->data, preMinP->next->data))
			{
				preMinP = j;
			}
		}
		NodePtr minP = preMinP->next;
		preMinP->next = minP->next ? minP->next : nullptr;
		minP->next = i->next;
		//DebugVar(minP->data);
		i->next = minP;
		//DebugVar(*this);
	}
}


template class LinkList<int>;