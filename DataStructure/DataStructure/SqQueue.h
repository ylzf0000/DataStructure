#pragma once
#include <string>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include "SqBase.h"
template <typename T>
class SqQueue
{
	TYPE_ALIAS(T);
public:
	SqQueue();
	~SqQueue();
	auto operator<<(ConstRef e)->SqQueue&;
	friend std::ostream& operator<<(std::ostream &os, const SqQueue &self)
	{
		for (int i = self.m_front; i != self.rear(); i = self.nextIdx(i))
			os << self.m_base.m_data[i] << " ";
		os << std::endl;
		return os;
	}
	auto Push(ConstRef e)->void;
	auto Pop()->void;
	auto Head()->Elem;

	auto IsEmpty() const->bool
	{
		return m_front == m_rear;
	}

private:
	auto isFull()const->bool;
	auto nextIdx(int i)const->int;
	auto nextRear()const->int;
	auto idx(int i)const->int;
	auto rear()const->int;
	SqBase<Elem> m_base;
	int m_front = 0;
	int m_rear = 0;
};

template<typename T>
inline SqQueue<T>::SqQueue()
{
	DebugFunc;
}

template<typename T>
inline SqQueue<T>::~SqQueue()
{
	DebugFunc;
}

template<typename T>
inline auto SqQueue<T>::operator<<(ConstRef e) -> SqQueue &
{
	this->Push(e);
	return *this;
}

template<typename T>
auto SqQueue<T>::Push(ConstRef e) -> void
{
	if (isFull())
	{
		m_base.Expend();
	}
	m_base.m_data[m_rear] = e;
	m_rear = this->nextRear();
}

template<typename T>
auto SqQueue<T>::Pop() -> void
{
	if (!IsEmpty())
		++m_front;
}

template<typename T>
inline auto SqQueue<T>::Head() -> Elem
{
	return m_base.m_data[m_front];
}

template<typename T>
inline auto SqQueue<T>::isFull() const -> bool
{
	return m_front == nextRear();
}

template<typename T>
inline auto SqQueue<T>::nextIdx(int i) const -> int
{
	return idx(i + 1);
}

template<typename T>
inline auto SqQueue<T>::nextRear() const -> int
{
	return nextIdx(m_rear);
}

template<typename T>
inline auto SqQueue<T>::idx(int i) const -> int
{
	return i % m_base.m_maxSize;
}

template<typename T>
inline auto SqQueue<T>::rear() const -> int
{
	return idx(m_rear);
}

template class SqQueue<int>;