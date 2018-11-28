#pragma once
#include <iostream>

namespace ZXXXE
{
    using namespace std;

    template<typename T>
    struct TypeTrait
    {
        const T& operator()(const T &val)
        {
            return val;
        }
    };

    template<typename T>
    struct DebugVarClass
    {
        void operator()(const char *str, const T &val, const char *funcName)
        {
            cout << "[" << funcName << "] " << str << ": " << val << endl;
        }
    };
}

#define DebugVar(x) ZXXXE::DebugVarClass<decltype(x)>()(#x, ZXXXE::TypeTrait<decltype(x)>()(x),__func__)

#define Visit(x) DebugVar(x)

#define DebugVarName(x) ZXXXE::DebugVarClass<decltype(x)>()(#x, __func__)

#define DebugFunc (std::cout << "[" << __func__ << "]" << std::endl)

#define TYPE_ALIAS(T)				\
	public:							\
		using Elem = T;				\
		using Ref = T & ;			\
		using ConstRef = const T &;	\
		using Ptr = T * ;			\
		using ConstPtr = const T *

#define NODE_TYPE_ALIAS(NODE)				\
	public:									\
		using Node = NODE;					\
		using NodeRef = NODE & ;			\
		using ConstNodeRef = const NODE &;	\
		using NodePtr = NODE * ;			\
		using ConstNodePtr = const NODE *


#define CONTAINER(x) std::begin(x), std::end(x)
#define LENGTH(a) (sizeof(a)/sizeof(a[0]))
#define PRINT_CONT(c)                      {            \
    std::for_each(CONTAINER(c),[](auto e){std::cout<<e<<" "; });\
    std::cout<<std::endl;                               \
    }

#define PRINT_CONTEX(c,a,b)                 {            \
    std::for_each((c+a), (c+b),[](auto e){std::cout<<e<<" "; });\
    std::cout<<std::endl;                               \
    }