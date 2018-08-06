#include "stdafx.h"
#include "Test.h"
#include "SqList.h"
#include "LinkList.h"
#include "SqStack.h"
#include "Rand.h"
#include "Algorithm.h"
#include "SqQueue.h"
#include "LinkQueue.h"
#include "Calculator.h"
#include <vector>
#include <string>
using namespace std;

ZXXXE::Test::Test()
{
	//TestList();
	//TestLinkList();
	//TestQueue();
	//TestStack();
	this->Calculate("#1+2-3*((4+5)*3-1)+2#");
}
#define TEST 1
void ZXXXE::Test::TestLinkList()
{
#ifdef TEST
	LinkList<int> a, b;
	int n = 10;
	RandInt rand(1, 100);
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
	RandInt a11(1, 2);
	//a.TSort<greater>();
	//DebugVar(a);
	//a.Unique();
	//DebugVar(a);
#endif // TEST

}

void ZXXXE::Test::TestList()
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

void ZXXXE::Test::TestQueue()
{
	LinkQueue<int> q;
	RandInt rand(10, 50);
	int n = 10;
	while (n--)
		q << rand();
	DebugVar(q);
	while (!q.IsEmpty())
	{
		DebugVar(q.Head());
		q.Pop();
		DebugVar(q);
	}
}

void ZXXXE::Test::TestStack()
{
	SqStack<int> s;
	int n = 10;
	RandInt rand(1, 100);
	while (n--)
		s << rand();
	DebugVar(s);
	while (!s.IsEmpty())
	{
		DebugVar(s.Top());
		s.Pop();
	}
	DebugVar(s);
}

auto ZXXXE::Test::Calculate(const string & s) -> double
{
	Calculator cal;
	string ss;
	while (cin >> ss)
	{
		ss += "#";
		cal.Value(ss);
	}
		
	return 0;
}

