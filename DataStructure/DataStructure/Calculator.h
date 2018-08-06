#pragma once
#include <string>
#include <iostream>
#include "SqList.h"
namespace ZXXXE
{
	using namespace std;
	class Calculator
	{
	public:
		Calculator();
		//************************************
		// Method:    Value
		// Desc:      Now it only suppose + - * /
		// FullName:  ZXXXE::Calculator::Value
		// Access:    public 
		// Returns:   double
		// Qualifier: const
		// Parameter: const string & input
		//************************************
		double Value(const string &input) const;
	private:
		struct OperAndVal;
		double Cal(double a, char b, double c) const;
		bool IsNum(const string &s, int cur, int &final, double &x)const;
		auto Postfix(const string &nifix) const->SqList<OperAndVal>;
		int Prior(char a, char b) const;
		int m_intFromChar[sizeof(char) << 8];
		int m_operatorTable[7][7] = {
			{ 0, 1, 1, 1, 1, 1, 0 },
			{ 0,-1,-1, 1, 1, 1,-1 },
			{ 0,-1,-1, 1, 1, 1,-1 },
			{ 0,-1,-1,-1,-1, 1,-1 },
			{ 0,-1,-1,-1,-1, 1,-1 },
			{ 0, 1, 1, 1, 1, 1,-1 },
			{ 0, 0, 0, 0, 0, 0, 0 }
		};

		struct OperAndVal
		{
			bool isVal;
			union
			{
				char c;
				double x;
			};
			OperAndVal(){}
			OperAndVal(bool b, char ch) :isVal{ b }, c{ ch } {}
			OperAndVal(bool b, double v) :isVal{ b }, x{ v } {}
			friend ostream &operator<<(ostream &os, const OperAndVal &self)
			{
				if (self.isVal)
					os << self.x;
				else
					os << self.c;
				return os;
			}
		};
	};
}
