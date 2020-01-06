// 分支限界求解TSP问题
// 洛谷P1171
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <limits.h>
#include <numeric>
#include <deque>
#include <queue>
#include <cmath>
using namespace std;
constexpr int INF = INT_MAX;
constexpr int N = 21;
int n;
int w[N][N];
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
			if (w[i][j] < min_w && w[i][j] > 0)
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
	while ((e = q.top()).s < n)
	{
		q.pop();
		if (e.s == n - 1)
		{
			if (e.cw + w[e.x[n - 1]][e.x[n]] + w[e.x[n]][e.x[1]] < bestw)
			{
				bestw = e.cw + w[e.x[n - 1]][e.x[n]] + w[e.x[n]][e.x[1]];
				e.cw = bestw;
				e.lw = bestw;
				e.s += 1;
				q.push(e);
			}
			continue;
		}
		for (int i = e.s + 1; i <= n; ++i)
		{
			int cw = e.cw + w[e.x[e.s]][e.x[i]];
			int rw = e.rw - min_out[e.x[e.s]];
			int b = cw + rw;
			if (b < bestw)
			{
				Node n = e;
				n.x[e.s + 1] = e.x[i];
				n.x[i] = e.x[e.s + 1];
				n.cw = cw;
				n.s = e.s + 1;
				n.lw = b;
				n.rw = rw;
				q.push(n);
			}
		}
	}
	if (bestw == INF)
		return INF;
	return bestw;
}
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			scanf("%d", w[i] + j);
	printf("%d\n", min_weight_tsp());
}
