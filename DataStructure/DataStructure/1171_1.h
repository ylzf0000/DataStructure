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
#include <cstring>
#include <cmath>
using namespace std;
constexpr int INF = INT_MAX;
constexpr int N = 21;
int n;
int w[N][N];
int x[N];
int cw, rw;
int min_sum;
int min_out[N];
int bestw = INF;
int bestx[N];
int dfs(int d)
{
	if (d == n - 1)
	{
		if (cw + w[x[n - 1]][x[n]] + w[x[n]][x[1]] < bestw)
		{
			bestw = cw + w[x[n - 1]][x[n]] + w[x[n]][x[1]];
		}
		return bestw;
	}
	for (int i = d + 1; i <= n; ++i)
	{
		cw += w[x[d]][x[i]];
		rw -= min_out[x[d]];
		int b = cw + rw;
		if (b < bestw)
		{
			swap(x[d + 1], x[i]);
			dfs(d + 1);
			swap(x[d + 1], x[i]);
		}
		rw += min_out[x[d]];
		cw -= w[x[d]][x[i]];
	}
	return bestw;
}
void init()
{
	min_sum = 0;
	bestw = INF;
	for (int i = 1; i <= n; ++i)
	{
		int min_w = INF;
		for (int j = 1; j <= n; ++j)
			if (w[i][j] < min_w && w[i][j] > 0)
				min_w = w[i][j];
		min_out[i] = min_w;
		min_sum += min_w;
		x[i] = i;
	}
	cw = 0;
	rw = min_sum;
}
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			scanf("%d", w[i] + j);
	init();
	printf("%d\n", dfs(1));
}