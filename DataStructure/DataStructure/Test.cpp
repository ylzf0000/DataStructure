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
#include "BiTree.h"
#include "ThreadTree.h"
#include <vector>
#include <string>
using namespace std;

ZXXXE::Test::Test()
{
    //TestList();
    //TestLinkList();
    //TestQueue();
    //TestStack();
    //this->Calculate("#1+2-3*((4+5)*3-1)+2#");
    //Recursion();
    TestTree();
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
        cal.Value(ss);
    return 0;
}

auto ZXXXE::Test::Recursion() -> void
{
    int x, n;
    while (cin >> x >> n)
    {
        int p0 = 1;
        int p1 = x * 2;
        int pn;
        if (n == 0)
            pn = p0;
        else if (n == 1)
            pn = p1;
        else
        {
            for (int i = 2; i <= n; ++i)
            {
                pn = 2 * x*p1 - 2 * (i - 1)*p0;
                p0 = p1;
                p1 = pn;
            }
        }
        DebugVar(pn);
    }
}

auto ZXXXE::Test::TestTree() -> void
{
    
    //int lst[] = { 1,2,3,4,0,0,5,0,0,6,0,0,7,8,10,0,0,0,9,0,0 };
    //           5
    //        /    \
    //       /      \
    //      4        9
    //     /       /   \
    //    2       7    10
    //     \     /       \
    //      3   6        11     
    //      
    int lst[] = { 5,4,2,0,3,0,0,0,9,7,6,0,0,0,10,0,11,0,0 };
    //BiTree<int> tree;
    //tree.GenerateByPreAndIn(
    //    { 5,4,2,3,9,7,6,10,11 }, 
    //    { 2,3,4,5,6,7,9,10,11 });
    //tree.Generate(begin(lst), end(lst));
    
    //tree.PreOrder2();
    //tree.InOrder2();
    //tree.LevelOrder();
    //tree.PostOrder3();
    ThreadTree<int> threadTree;
    threadTree.Generate(begin(lst), end(lst));
    //threadTree.InThread();
    //threadTree.InOrder();
    threadTree.PreThread();
    threadTree.PreOrder();
}

