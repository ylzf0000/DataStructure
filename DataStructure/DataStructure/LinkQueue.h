#pragma once
#include <string>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <functional>
#include "LinkBase.h"
template<typename T = int>
class LinkQueue
{
	TYPE_ALIAS(T);
	NODE_TYPE_ALIAS(SNode<T>);
public:
	LinkQueue();
	~LinkQueue() = default;
	auto operator<<(ConstRef e)->LinkQueue&;
	friend std::ostream& operator<<(std::ostream &os, const LinkQueue &self)
	{
		for (auto p = self.m_front->next; p; p = p->next)
			os << p->data << " ";
		os << std::endl;
		return os;
	}
	auto IsEmpty()const->bool;
	auto Push(ConstRef e)->void;
	auto Pop()->void;
	auto Head()const->Elem;

private:
	LinkBase<T> m_base;
	NodePtr m_front;
	NodePtr m_rear;
};

template<typename T>
inline LinkQueue<T>::LinkQueue()
{
	m_front = m_rear = m_base.m_headNode;
}

template<typename T>
inline auto LinkQueue<T>::operator<<(ConstRef e) -> LinkQueue &
{
	Push(e);
	return *this;
}

template<typename T>
inline auto LinkQueue<T>::IsEmpty() const -> bool
{
	return m_front == m_rear;
}

template<typename T>
auto LinkQueue<T>::Push(ConstRef e) -> void
{
	NodePtr newNode = new Node{ e };
	m_rear->next = newNode;
	m_rear = m_rear->next;
}

template<typename T>
auto LinkQueue<T>::Pop() -> void
{
	if (IsEmpty())
		return;
	NodePtr beDel = m_front->next;
	m_front->next = beDel->next;
	if (m_rear == beDel)
		m_rear = m_front;
	delete beDel;
}

template<typename T>
inline auto LinkQueue<T>::Head() const -> Elem
{
	return m_front->next->data;
}

template class LinkQueue<int>;