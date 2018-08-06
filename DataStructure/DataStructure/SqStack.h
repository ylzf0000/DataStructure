#pragma once
#include <cstdlib>
#include <cassert>
#include <iostream>
#include "SqBase.h"
template <typename T>
class SqStack
{
	TYPE_ALIAS(T);
public:
	SqStack();
	~SqStack();
	auto operator<<(ConstRef e)->SqStack&;
	friend std::ostream& operator<<(std::ostream &os, const SqStack &self)
	{
		for (int i = 0; i <= self.m_top; ++i)
			os << self.m_base.m_data[i] << " ";
		os << std::endl;
		return os;
	}
	bool IsEmpty() const;
	void Push(ConstRef e);
	void Pop();
	Elem Top() const;
	void Clear();
private:
	SqBase<Elem> m_base;
	int m_top = -1;
};

template<typename T>
inline SqStack<T>::SqStack()
{
	DebugFunc;
}

template<typename T>
inline SqStack<T>::~SqStack()
{
	DebugFunc;
}

template<typename T>
inline auto SqStack<T>::operator<<(ConstRef e) -> SqStack &
{
	Push(e);
	return *this;
}

template<typename T>
inline bool SqStack<T>::IsEmpty() const
{
	return m_top == -1;
}

template<typename T>
void SqStack<T>::Push(ConstRef e)
{
	if (m_top + 1 == m_base.m_maxSize)
		m_base.Expend();
	m_base.m_data[++m_top] = e;
}

template<typename T>
inline void SqStack<T>::Pop()
{
	--m_top;
}

template<typename T>
inline auto SqStack<T>::Top() const -> Elem
{
	return m_base.m_data[m_top];
}

template<typename T>
inline void SqStack<T>::Clear()
{
	m_top = -1;
	m_base.Free();
}

template class SqStack<int>;