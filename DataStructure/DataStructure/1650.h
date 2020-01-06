#pragma once

#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <limits.h>
#include <numeric>
#include <deque>
#include <queue>
#include <cstring>
#include <cmath>
#include <tuple>
using namespace std;
constexpr int INF = INT_MAX;
constexpr int N = 2005 * 2;
int n;
deque<int> qa, qb;
int func()
{
	sort(qa.rbegin(), qa.rend());
	sort(qb.rbegin(), qb.rend());
	int ans = 0;
	while (!qa.empty())
	{
		int ahead = qa.front();
		int atail = qa.back();
		int bhead = qb.front();
		int btail = qb.back();
		if (ahead > bhead)
		{
			++ans;
			qa.pop_front();
			qb.pop_front();
		}
		else if (ahead < bhead)
		{
			--ans;
			qa.pop_back();
			qb.pop_front();
		}
		else if (atail > btail)
		{
			++ans;
			qa.pop_back();
			qb.pop_back();
		}
		else
		{
			if (atail < bhead)
				--ans;
			qa.pop_back();
			qb.pop_front();
		}
	}
	return ans * 200;
}
int main()
{
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		int v;
		cin >> v;
		qa.push_back(v);
	}
	for (int i = 0; i < n; ++i)
	{
		int v;
		cin >> v;
		qb.push_back(v);
	}
	cout << func() << endl;

}
