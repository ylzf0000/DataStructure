#pragma once
#include <cstdlib>
#include <cassert>
#include <iostream>
template <typename T>
class SqStack
{
public:
	using Elem = T;
	using Ref = T & ;
	using ConstRef = const T &;
	using Ptr = T * ;
	using ConstPtr = const T *;
	SqStack();
	~SqStack();
	bool IsEmpty() const;
	void Push(ConstRef e);
	void Pop();
	Ref Top();
	ConstRef Top() const;
	void Clear();
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
	auto Expend() -> void;
	const int INIT_SIZE = 5;
	int m_maxSize = INIT_SIZE;
	int m_length;
	Elem * m_data;
};

template<typename T>
inline SqStack<T>::SqStack()
{
	m_data = new Elem[INIT_SIZE];
}

template<typename T>
inline SqStack<T>::~SqStack()
{
	Free();
}

template<typename T>
inline bool SqStack<T>::IsEmpty() const
{
	return m_length == 0;
}

template<typename T>
void SqStack<T>::Push(ConstRef e)
{
	if (m_length == m_maxSize)
		Expend();
	m_data[m_length++] = e;
}

template<typename T>
inline void SqStack<T>::Pop()
{
	--m_length;
}

template<typename T>
inline auto SqStack<T>::Top() -> Ref
{
	return m_data[m_length - 1];
}

template<typename T>
inline auto SqStack<T>::Top() const -> ConstRef
{
	return m_data[m_length - 1];
}

template<typename T>
inline void SqStack<T>::Clear()
{
	m_length = 0;
	Free();
}

template<typename T>
inline auto SqStack<T>::Free() -> void
{
	delete[] m_data;
	m_data = nullptr;
}

template<typename T>
auto SqStack<T>::Expend() -> void
{
	int newSize = m_maxSize == 0 ? 2 : m_maxSize * 2;
	Elem *data = new Elem[newSize];
	for (int i = 0; i < m_length; ++i)
	{
		data[i] = std::move(m_data[i]);
	}
	Free();
	m_data = data;
	m_maxSize = newSize;
}

template class SqStack<int>;