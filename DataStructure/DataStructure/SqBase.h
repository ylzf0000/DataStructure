#pragma once
#include <string>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include "stdafx.h"
template <typename T>
class SqBase
{
	TYPE_ALIAS(T);
public:
	SqBase();
	~SqBase();
	//template <int C = 0>
	//auto AssertRange(int i) const -> void
	//{
	//	assert(i >= 0 && i < m_length);
	//}
	//template <>
	//auto AssertRange<1>(int i) const -> void
	//{
	//	assert(i >= 0 && i <= m_length);
	//}
	auto Free() -> void;
	auto Expend() -> void;
	const int INIT_SIZE = 1000;
	int m_maxSize = INIT_SIZE;	//当前最大容量
	Ptr m_data;
};

template<typename T>
inline SqBase<T>::SqBase()
{
	m_data = new Elem[INIT_SIZE];
}

template<typename T>
inline SqBase<T>::~SqBase()
{
	delete[] m_data;
}

template<typename T>
inline auto SqBase<T>::Free() -> void
{
	DebugFunc;
	delete[] m_data;
	m_data = nullptr;
	m_maxSize = 0;
}

template<typename T>
auto SqBase<T>::Expend() -> void
{
	DebugFunc;
	int newSize = m_maxSize == 0 ? 2 : m_maxSize * 2;
	Elem *data = new Elem[newSize];
	for (int i = 0; i < m_maxSize; ++i)
	{
		data[i] = std::move(m_data[i]);
	}
	Free();
	m_data = data;
	m_maxSize = newSize;
}
