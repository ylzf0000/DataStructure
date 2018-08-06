#include "Calculator.h"
#include "SqStack.h"
#include "SqList.h"
#include <cstring>
#include <exception>
using namespace std;
ZXXXE::Calculator::Calculator()
{
	memset(m_intFromChar, -1, sizeof(m_intFromChar));
	m_intFromChar['#'] = 0;
	m_intFromChar['+'] = 1;
	m_intFromChar['-'] = 2;
	m_intFromChar['*'] = 3;
	m_intFromChar['/'] = 4;
	m_intFromChar['('] = 5;
	m_intFromChar[')'] = 6;
}

double ZXXXE::Calculator::Value(const string & input) const
{
	SqList<OperAndVal> lst = Postfix(input);
	SqStack<double> s;
	for (int i = 0; i < lst.Length(); ++i)
	{
		OperAndVal oav = lst[i];
		if (oav.isVal)
			s.Push(oav.x);
		else
		{
			double b = s.Top(); s.Pop();
			double a = s.Top(); s.Pop();
			auto val = Cal(a, oav.c, b);
			cout << a << " " << b << " " << val;
			cout << endl;
			s.Push(val);
		}
	}
	cout << endl;
	DebugVar(s.Top());
	return s.Top();
}

double ZXXXE::Calculator::Cal(double a, char b, double c) const
{
	switch (b)
	{
	case '+':
		return a + c;
	case '-':
		return a - c;
	case '*':
		return a * c;
	case '/':
		return a / c;
	}
	throw runtime_error("Can only suppose + - * /");
}

bool ZXXXE::Calculator::IsNum(const string & s, int cur, int & final, double & x) const
{
	if (cur < s.length() && m_intFromChar[s[cur]] >= 0)
	{
		final = cur;
		return false;
	}
	double val = 0;
	while (cur < s.length() && m_intFromChar[s[cur]] < 0)
	{
		int v = s[cur] - '0';
		val = val * 10 + v;
		++cur;
	}
	final = cur;
	x = val;
	return true;
}
//this->Calculate("#1+2-3*((4+5)*3-1)+2#");
auto ZXXXE::Calculator::Postfix(const string & nifix) const -> SqList<OperAndVal>
{
	SqStack<char> s;
	s.Push('#');
	SqList<OperAndVal> lst;
	for (int i = 0; i < nifix.length(); ++i)
	{
		double x;
		if (IsNum(nifix, i, i, x))
		{
			lst << OperAndVal{ true,x };
		}
		char c = nifix[i];
		int  prior = Prior(s.Top(), c);
		if (prior > 0)
		{
			s.Push(c);
		}
		else if (prior < 0)
		{
			if (c == ')')
			{
				while (s.Top() != '(')
				{
					lst << OperAndVal{ false,s.Top() };
					s.Pop();
				}
				if (s.Top() == '(')
					s.Pop();
			}
			else
			{
				do
				{
					lst << OperAndVal{ false,s.Top() };
					s.Pop();
					prior = Prior(s.Top(), c);
				} while (s.Top() != '(' && prior < 0);
				s.Push(c);
			}
		}
		DebugVar(lst);
	}
	while (!s.IsEmpty() && s.Top() != '#')
	{
		lst << OperAndVal{ false,s.Top() };
		s.Pop();
	}
	DebugVar(lst);
	return lst;
}

int ZXXXE::Calculator::Prior(char a, char b) const
{
	int x = m_intFromChar[a];
	int y = m_intFromChar[b];
	return m_operatorTable[x][y];
}
