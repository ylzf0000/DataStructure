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
#include "Graph.h"
#include "String.h"
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
    //TestTree();
    //TestGraph();
    //TestString();
    //TestSort();
    //PrintConbinationRec(4, 2);
    //_ZXXXE::printConbination2(7, 3);
    //constexpr int N = 31;
    //int *a = new int[N + 1]; 
    //for (int i = 1; i <= N; ++i)
    //    a[i] = i;
    //_ZXXXE::printDescendant(a, N, 2);
    //PrintPermutation(4);
    //PrintPermutationDict(4);
    int a[] = { 1,3,3,2,4 };
    _ZXXXE::printPermutationDict(a, LENGTH(a));
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
    //           5
    //        /    \
    //       /      \
    //      4        9
    //     /       /   \
    //    2       7    10
    //     \     /       \
    //      3   6        11     
    //      
    int lst[] =
    //{ 5,4,2,12,0,0,3,0,0,0,9,7,6,0,0,0,10,0,11,0,0 };
    { 1,2,4,0,0,5,0,10,0,0,3,6,13,0,0,14,0,0,7,11,0,0,12,0,0, };

    BiTree<int> tree;
    tree.GenerateByPreAndIn(
        { 5,4,2,3,9,7,6,10,11 },
        { 2,3,4,5,6,7,9,10,11 });
    //tree.SetParent();
    DebugVar(tree.Level(5));
    //tree.Generate(CONTAINER(lst));
    //DebugVar(tree.Width());
    //DebugVar(tree.CountLeaf());
    //DebugVar(tree.Depth());
    //decltype(tree) treeCopy;
    //tree.Copy(treeCopy);
    //treeCopy.PreOrder();
    //tree.PreOrder2();
    //tree.InOrder2();
    //tree.LevelOrder();
    //tree.PostOrder3();
    //ThreadTree<int> threadTree;
    //threadTree.Generate(begin(lst), end(lst));
    //threadTree.InThread();
    //threadTree.InOrder();
    //threadTree.PreThread();
    //threadTree.PreOrder();
}

auto ZXXXE::Test::TestGraph()->void
{
    //  0-------1----\
    //  |       |    |
    //  |       |    |
    //  |       |    |
    //  3-------2----4
    int mat[][5] =
    {
        { 0,   1,  INF, 1,   INF },
        { 1,   0,  1,   INF, 1   },
        { INF, 1,  0,   1,   1   },
        { 1,   INF,1,   0,   INF },
        { INF, 1,  1,   INF, 0   }
    };
    //  0------>1\
    //  |         \  
    //  |          > 4
    // \|/        /   
    //  3------>2/
    int mat2[][5] =
    {
        { 0,   1,   INF, 1,   INF },
        { INF, 0,   INF, INF, 1   },
        { INF, INF, 0,   INF, 1   },
        { INF, INF, 1,   0,   INF },
        { INF, INF, INF, INF, 0   }
    };
    //MGraph<int> mg(mat);
    ALGraph<int> alg(mat2);
    alg.dfsnr();
    //auto vec = mg.neighbor(2);
    //auto vec = alg.neighbor(2);
    //std::for_each(CONTAINER(vec), [](auto e) {cout << e; });
    //DFSTraverse(alg);
    //cout << endl;
    //DFSTraverse(mg);
    //cout << endl;
    //BFSTraverse(mg);
    //cout << endl;
    //TopSort(MGraph<int>(mat2), 0);
}

auto ZXXXE::Test::TestString() -> void
{
    char str[] = "12354321233215434";
    char pattern[] = "1233";
    int next[5];
    DebugVar(naiveSearch(str, pattern));
    //getNext(pattern, next);
    getNextval(pattern, next);
    for_each(CONTAINER(next), [](auto e) {cout << e; });
    DebugVar(kmp(str, pattern, next));
}

auto ZXXXE::Test::TestSort() -> void
{
    int a[13];
    auto n = end(a) - begin(a);
    int _;
    while (cin >> _)
    {
        for (int i = 0; i < n; ++i)
        {
            RandInt rand(0, 100);
            a[i] = rand();
        }

        PRINT_CONT(a);
        //Partition(a);
        DebugVar(kBigNo(a, _));
        Sort(a);
        PRINT_CONT(a);
        for (int i = 1; i < n; ++i)
        {
            if (a[i - 1] > a[i])
            {
                cout << "false" << endl;
            }
        }
        //int k = RandInt(0, n)();
        //DebugVar(k);
        //_ZXXXE::kBigHeapSort(a, n, k);
        //HeapSort(a);
    }

}

