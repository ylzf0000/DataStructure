#include "stdafx.h"
#include "Test.h"
#include "SqList.h"
#include "LinkList.h"
#include "SqStack.h"
#include "Rand.h"
#include "Algorithm.h"
#include "SqQueue.h"
#include "LinkQueue.h"
#include <vector>
using namespace std;

Test::Test()
{
	//TestList();
	//TestLinkList();
	TestQueue();
}
#define TEST 1
void Test::TestLinkList()
{
#ifdef TEST
	LinkList<int> a, b;
	int n = 10;
	RandInt rand(1,100);
	while (n--)
	{
		a << rand();
	}
	n = 10;
	while (n--)
	{
		b << rand();
	}
	DebugVar(a);
	DebugVar(b);
	a.TSort();
	b.TSort();
	DebugVar(a);
	DebugVar(b);
	a.MergeEx(b);
	DebugVar(a);
	RandInt a11(1,2);
	//a.TSort<greater>();
	//DebugVar(a);
	//a.Unique();
	//DebugVar(a);
#endif // TEST

}

void Test::TestList()
{
#if(!TEST)
	SqList<int> a, b;
	a.PushBack(1);
	a.PushBack(2);
	b.PushBack(3);
	b.PushBack(4);
	cout << a << endl;
	cout << b << endl;
	Union(a, b);
	cout << a;
	a << 5 << 8 << 9;
	decltype(a) c;
	Merge(a, b, c);
	cout << c;
#endif // TEST

}

void Test::TestQueue()
{
	//SqQueue<int> q;
	//RandInt rand(1, 100);
	//int n = 10;
	//while (n--)
	//{
	//	int x = rand();
	//	q << x;
	//}
	//DebugVar(q);
	//int t = 6;
	//while (t--)
	//	q.Pop();
	//DebugVar(q);
	//n = 28;
	//while (n--)
	//{
	//	int x = rand();
	//	q << x;
	//}
	//DebugVar(q);
	// 

	LinkQueue<> q;
}
