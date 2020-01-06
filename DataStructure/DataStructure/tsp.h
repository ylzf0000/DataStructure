#pragma once
// 分支限界求解TSP问题
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <limits.h>
#include <numeric>
#include <deque>
#include <queue>
#include <cmath>
using namespace std;
constexpr int N = 22;
int n;
int w[N][N];
constexpr int INF = INT_MAX;
int bestx[N];
struct Node
{
	int x[N];
	int s, cw, rw, lw;
	bool operator>(const Node& e)const
	{
		return this->lw > e.lw;
	}
};
int min_weight_tsp()
{
	int min_sum = 0;
	int min_out[N];
	int bestw = INF;
	for (int i = 1; i <= n; ++i)
	{
		int min_w = INF;
		for (int j = 1; j <= n; ++j)
			if (w[i][j] < min_w)
				min_w = w[i][j];
		if (min_w == INF)
			return INF;
		min_out[i] = min_w;
		min_sum += min_w;
	}
	priority_queue<Node, vector<Node>, greater<Node>> q;
	Node e;
	for (int i = 1; i <= n; ++i)
		e.x[i] = i;
	e.s = 1; e.cw = 0; e.rw = min_sum;
	q.push(e);
	while (!q.empty())
	{
		e = q.top();
		q.pop();
		if (e.s == n - 1)
		{
			if (w[e.x[n - 1]][e.x[n]] != INF && w[e.x[n]][e.x[1]] != INF &&
				e.cw + w[e.x[n - 1]][e.x[n]] + w[e.x[n]][e.x[1]] < bestw)
			{
				bestw = e.cw + w[e.x[n - 1]][e.x[n]] + w[e.x[n]][e.x[1]];
				for (int i = 1; i <= n; ++i)
					bestx[i] = e.x[i];
			}
		}
		else
		{
			for (int i = e.s + 1; i <= n; ++i)
			{
				if (w[e.x[e.s]][e.x[i]] != INF)
				{
					int cw = e.cw + w[e.x[e.s]][e.x[i]];
					int rw = e.rw - min_out[e.x[i]];
					int b = cw + rw;
					if (b < bestw)
					{
						Node new_e = e;
						new_e.x[e.s + 1] = e.x[i];
						new_e.x[i] = e.x[e.s + 1];
						new_e.cw = cw;
						new_e.s = e.s + 1;
						new_e.lw = b;
						new_e.rw = rw;
						q.push(new_e);
					}
				}
			}
		}
	}
	if (bestw == INF)
		return INF;
	return bestw;
}

void finput(const string& s)
{
	struct Point { float x, y; };
	vector<Point> v;
	v.push_back({});
	ifstream fin(s);
	string _;
	for (float i, x, y; fin >> i >> x >> y >> _;)
	{
		v.push_back({ x,y });
	}
	n = v.size() - 1;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
		{
			float dx = v[i].x - v[j].x;
			float dy = v[i].y - v[j].y;
			w[i][j] = (int)sqrt(dx * dx + dy * dy);
		}
}
void finput2()
{
	fstream fin("in_tsp.txt");
	fin >> n;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			fin >> w[i][j];
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			cout << w[i][j] << ((j == n) ? "\n" : " ");
}
int main()
{
	//finput("in_tsp_351.txt");
	//n = 10;
	cin >> n;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			cin >> w[i][j];


	cout << min_weight_tsp() << endl;
	//for (int i = 1; i <= n; ++i)
	//	cout << bestx[i] << " ";
	//cout << endl;

}