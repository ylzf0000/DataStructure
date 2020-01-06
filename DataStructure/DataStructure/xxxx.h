#pragma once
#include <iostream>
#include <deque>
#include <queue>
using namespace std;
constexpr int N = 10;
int n;
#define printex(e) do{\
	for (int i = 1; i <= n; ++i)\
		cout << e.x[i] << " ";cout << endl;\
	}while (0)
void f2017_5()
{
	struct E { int x[N], s; };
	queue<E> q;
	E e;
	for (int i = 1; i <= n; ++i)
		e.x[i] = i;
	e.s = 0;
	q.push(e);
	while (!q.empty()) {
		E e = q.front();
		q.pop();
		if (e.s >= n - 1) {
			printex(e);
			continue;
		}
		for (int i = e.s + 1; i <= n; ++i) {
			E new_e = e;
			new_e.x[e.s + 1] = e.x[i];
			new_e.x[i] = e.x[e.s + 1];
			new_e.s = e.s + 1;
			q.push(new_e);
		}
	}
}
int main()
{
	while (cin >> n)
	{
		f2017_5();
		cout << endl;
	}
}