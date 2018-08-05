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
	delete beDel;
	if (m_rear == beDel)
		m_rear = m_front;
}

template<typename T>
inline auto LinkQueue<T>::Head() const -> Elem
{
	return *m_front;
}

template class LinkQueue<int>;