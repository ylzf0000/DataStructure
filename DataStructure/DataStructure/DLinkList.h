#pragma once
#include <string>
#include <cstdlib>
#include <cassert>
#include <iostream>
template<typename T>
class DLinkList
{
public:
	using Elem = T;
	using Ref = T & ;
	using ConstRef = const T &;
	using Ptr = T * ;
	using ConstPtr = const T *;
	struct Node
	{
		Elem data;
		Node *prior = nullptr;
		Node *next = nullptr;
	};
	using NodeRef = Node & ;
	using NodePtr = Node * ;
	using ConstNodeRef = const Node &;
	using ConstNodePtr = const Node *;
	DLinkList();
	~DLinkList();

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

	auto begin()->Ptr;
	auto begin() const->ConstPtr;
	auto end()->Ptr;
	auto end() const->ConstPtr;

	//auto Front() const->ConstRef;
	//auto Front()->Ref;
	//auto Back() const->ConstRef;
	//auto Back()->Ref;

	friend std::ostream& operator<<(std::ostream &os, const DLinkList &self)
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

	Node *m_headNode;
	int m_length = 0;
};

template<typename T>
inline DLinkList<T>::DLinkList()
{
	m_headNode = new Node();
}

template<typename T>
inline DLinkList<T>::~DLinkList()
{
	DebugFunc;
	Free();
}

template<typename T>
void DLinkList<T>::HeadCreate()
{
	T val;
	while (cin >> val)
	{
		Node *node = new Node{ val };
		node->next = m_headNode->next;
		m_headNode->next->prior = node;
		node->prior = m_headNode;
		m_headNode->next = node;
		++m_length;
	}
}

template<typename T>
void DLinkList<T>::TailCreate()
{
	T val;
	Node *tail = m_headNode;
	//for (tail = m_headNode; tail->next; tail = tail->next);
	while (cin >> val)
	{
		Node *node = new Node{ val };
		tail->next = node;
		node->prior = tail;
		tail = node;
		++m_length;
	}
}

template<typename T>
inline auto DLinkList<T>::Length() const -> int
{
	return m_length;
}

template<typename T>
inline auto DLinkList<T>::Find(ConstRef e) const -> int
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
auto DLinkList<T>::At(int i) const -> ConstNodeRef
{
	AssertRange(i);
	Node *node = m_headNode->next;
	for (int idx = 0; idx < i&&node; ++idx, node = node->next);
	return *node;
}

template<typename T>
inline auto DLinkList<T>::At(int i) -> NodeRef
{
	return const_cast<NodeRef>(const_cast<const DLinkList*>(this)->At(i));
}

template<typename T>
inline auto DLinkList<T>::operator[](int i) const -> ConstNodeRef
{
	return At(i);
}

template<typename T>
inline auto DLinkList<T>::operator[](int i) -> NodeRef
{
	return At(i);
}

template<typename T>
inline auto DLinkList<T>::Insert(int i, ConstRef e) -> void
{
	AssertRange<1>(i);
	Node *node = m_headNode->next;
	for (int idx = 0; idx < i - 1; ++idx, node = node->next);
	Node *newNode = new Node{ e };
	newNode->next = node->next;
	if(node->next)
		node->next->prior = newNode;
	node->next = newNode;
	newNode->prior = node;
	++m_length;
}

template<typename T>
inline auto DLinkList<T>::PushBack(ConstRef e) -> void
{
	Insert(m_length, e);
}

template<typename T>
inline auto DLinkList<T>::Remove(int i) -> void
{
	AssertRange(i);
	Node *node = m_headNode->next;
	for (int idx = 0; idx < i - 1; ++idx, node = node->next);
	Node *tmp = node->next;
	node->next = tmp->next;
	tmp->next->prior = node;
	delete tmp;
	--m_length;
}

template<typename T>
inline auto DLinkList<T>::PopBack(Ptr e) -> void
{
	Remove(m_length - 1);
}

template<typename T>
inline auto DLinkList<T>::IsEmpty() const -> bool
{
	return m_length == 0;
}

template<typename T>
inline auto DLinkList<T>::Clear() -> void
{
	Free();
}

template<typename T>
inline auto DLinkList<T>::begin() -> Ptr
{
	return m_headNode->next;
}

template<typename T>
inline auto DLinkList<T>::begin() const -> ConstPtr
{
	return m_headNode->next;
}

template<typename T>
inline auto DLinkList<T>::end() -> Ptr
{
	return nullptr;
}

template<typename T>
inline auto DLinkList<T>::end() const -> ConstPtr
{
	return nullptr;
}

template<typename T>
auto DLinkList<T>::Free() -> void
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

template class DLinkList<int>;
