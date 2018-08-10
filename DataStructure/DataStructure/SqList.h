#pragma once
#include <string>
#include <cstdlib>
#include <cassert>
#include <iostream>
template <typename T>
class SqList
{
public:
    using Elem = T;
    using Ref = T & ;
    using ConstRef = const T &;
    using Ptr = T * ;
    using ConstPtr = const T *;
    SqList();
    SqList(std::initializer_list<Elem> &&list);
    SqList(const SqList &right);
    ~SqList();
    auto Length() const -> int;
    auto Capacity() const -> int;
    auto Find(ConstRef e) const -> bool;

    auto At(int i) const->ConstRef;
    auto At(int i)->Ref;
    auto operator[](int i) const->ConstRef;
    auto operator[](int i)->Ref;

    auto Insert(int i, ConstRef e) -> bool;
    auto PushBack(ConstRef e)->void;
    auto Remove(int i)->bool;
    auto PopBack(Ptr e = nullptr)->bool;

    auto IsEmpty() const->bool;
    auto Clear()->void;

    auto begin()->Ptr;
    auto begin() const->ConstPtr;
    auto end()->Ptr;
    auto end() const->ConstPtr;

    auto Front() const->ConstRef;
    auto Front()->Ref;
    auto Back() const->ConstRef;
    auto Back()->Ref;

    auto operator<<(ConstRef e)->SqList&;
    friend std::ostream& operator<<(std::ostream &os, const SqList &self)
    {
        for (const auto &e : self)
        {
            os << e << " ";
        }
        os << std::endl;
        return os;
    }
protected:
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
    int m_maxSize = INIT_SIZE;	//当前最大容量
    int m_length = 0;			//当前个数
    Elem *m_data;
};

template<typename T>
inline SqList<T>::SqList()
{
    m_data = new Elem[INIT_SIZE];
}

template<typename T>
inline SqList<T>::SqList(std::initializer_list<Elem>&& list)
{
    for (auto it = list.begin(); it != list.end(); ++it)
    {
        PushBack(*it);
    }
}

template<typename T>
SqList<T>::SqList(const SqList & right)
{
    m_length = right.m_length;
    m_maxSize = m_length;
    m_data = new Elem[m_maxSize];
    for (int i = 0; i < m_length; ++i)
        m_data[i] = right.m_data[i];
}

template<typename T>
inline SqList<T>::~SqList()
{
    delete[] m_data;
}

template<typename T>
inline auto SqList<T>::Length() const -> int
{
    return m_length;
}

template<typename T>
inline auto SqList<T>::Capacity() const -> int
{
    return m_maxSize;
}

template<typename T>
auto SqList<T>::Find(ConstRef e) const -> bool
{
    for (int i = 0; i < m_length; ++i)
    {
        if (m_data[i] == e)
            return true;
    }
    return false;
}

template<typename T>
inline auto SqList<T>::At(int i) const -> ConstRef
{
    AssertRange(i);
    return (*this)[i];
}

template<typename T>
inline auto SqList<T>::At(int i) -> Ref
{
    AssertRange(i);
    return (*this)[i];
}

template<typename T>
inline auto SqList<T>::operator[](int i) const -> ConstRef
{
    AssertRange(i);
    return m_data[i];
}

template<typename T>
inline auto SqList<T>::operator[](int i) -> Ref
{
    AssertRange(i);
    return m_data[i];
}

template<typename T>
auto SqList<T>::Insert(int i, ConstRef e) -> bool
{
    AssertRange<1>(i);
    if (m_length == m_maxSize)
        Expend();
    for (int idx = m_length - 1; idx >= i; --idx)
    {
        m_data[idx + 1] = std::move(m_data[idx]);
    }
    m_data[i] = e;
    ++m_length;
    return true;
}

template<typename T>
inline auto SqList<T>::PushBack(ConstRef e) -> void
{
    Insert(m_length, e);
}

template<typename T>
auto SqList<T>::Remove(int i) -> bool
{
    AssertRange(i);
    for (int idx = i + 1; idx < m_length; ++idx)
    {
        m_data[idx - 1] = std::move(m_data[idx]);
    }
    --m_length;
    return true;
}

template<typename T>
inline auto SqList<T>::PopBack(Ptr e) -> bool
{
    return Remove(m_length - 1);
}

template<typename T>
inline auto SqList<T>::IsEmpty() const -> bool
{
    return m_length == 0;
}

template<typename T>
inline auto SqList<T>::Clear()-> void
{
    Free();
    m_maxSize = 0;
    m_length = 0;
}

template<typename T>
inline auto SqList<T>::begin() -> Ptr
{
    return m_data;
}

template<typename T>
inline auto SqList<T>::begin() const -> ConstPtr
{
    return m_data;
}

template<typename T>
inline auto SqList<T>::end() -> Ptr
{
    return m_data + m_length;
}

template<typename T>
inline auto SqList<T>::end() const -> ConstPtr
{
    return m_data + m_length;
}

template<typename T>
inline auto SqList<T>::Front() const -> ConstRef
{
    return m_data[0];
}

template<typename T>
inline auto SqList<T>::Front() -> Ref
{
    return m_data[0];
}

template<typename T>
inline auto SqList<T>::Back() const -> ConstRef
{
    return m_data[m_length - 1];
}

template<typename T>
inline auto SqList<T>::Back() -> Ref
{
    return m_data[m_length - 1];
}

template<typename T>
inline auto SqList<T>::operator<<(ConstRef e) -> SqList&
{
    PushBack(e);
    return *this;
}

template<typename T>
inline auto SqList<T>::Free() -> void
{
    delete[] m_data;
    m_data = nullptr;
}

template<typename T>
auto SqList<T>::Expend() -> void
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

template class SqList<int>;