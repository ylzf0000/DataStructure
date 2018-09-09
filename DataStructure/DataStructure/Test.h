#pragma once
#include <string>
namespace ZXXXE 
{
	using namespace std;
	class Test
	{
	public:
		Test();
		void TestLinkList();
		void TestList();
		void TestQueue();
		void TestStack();
		auto Calculate(const string &s)->double;
		auto Recursion()->void;
        auto TestTree()->void;
        auto TestGraph()->void;
	};
}
