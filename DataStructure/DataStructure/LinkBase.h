#pragma once
#include <string>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <functional>
#include "stdafx.h"
template<typename T>
struct SNode
{
	T data = T();
	SNode *next = nullptr;
};

template<typename T>
struct DNode
{
	T data = T();
	DNode *next = nullptr;
	DNode *prior = nullptr;
};
template<typename T, template<class T> typename NODE = SNode>
class LinkBase
{
	TYPE_ALIAS(T);
	NODE_TYPE_ALIAS(NODE<T>);
public:
	LinkBase();
	~LinkBase();
	auto Free()->void;
	NodePtr m_headNode;
};

template<typename T, template<class T> class NODE>
inline LinkBase<T, NODE>::LinkBase()
{
	m_headNode = new Node;
}

template<typename T, template<class T> class NODE>
inline LinkBase<T, NODE>::~LinkBase()
{
	Free();
}

template<typename T, template<class T> class NODE>
inline auto LinkBase<T, NODE>::Free() -> void
{
	Node *node = m_headNode;
	while (node)
	{
		Node *next = node->next;
		delete node;
		node = next;
	}
}
