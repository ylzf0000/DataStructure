#pragma once
#include <algorithm>
#include <queue>
using namespace std;


//2
const int N = 15;
const int M = 20;
int I[N];
//int d[N][N] = {0};//d[i][j]为前i个数字的最大j乘积
int n, k;
int GetVal(int a, int b)
{
	int ret = 0;
	for (int i = a; i <= b; i++)
		ret = ret * 10 + I[i];
	return ret;
}
int f2017_2()
{
	for (int i = 1; i <= n; i++)
		d[i][1] = GetVal(1, i);
	for (int j = 1; j <= k; ++j)
		for (int i = j; i <= n; ++i)
			for (int m = 1; m < i; ++m)
				d[i][j] = max(d[i][j], d[m][j - 1] * GetVal(m + 1, i));
	//解为d[n][k]
}

//3
void f2017_3(int a[M][N], int b[N], int m, int n)
{
	for (int j = 1; j <= n; ++j) {
		int one_num = 0;
		for (int i = 1; i <= m; ++i)
			one_num += a[i][j];
		if (2 * one_num > m)
			b[j] = 0;
		else
			b[j] = 1;
	}
}

//4
int X, Y;
int d[N][M][M] = { 0 };
int v[N];
//int w[N];
int n;
void f2017_4()
{
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= X; ++j) //第一个背包容量
			for (int k = 1; k <= Y; ++k) { //第二个背包容量
				if (w[i] > j&& w[i] > k) { //两个都放不下
					d[i][j][k] = d[i - 1][j][k];
				}
				else if (w[i] > j) { //第一个背包放不下
					d[i][j][k] = max(d[i - 1][j][k], d[i - 1][j][k - w[i]] + v[i]);
				}
				else if (w[i] > k) { //第二个背包放不下
					d[i][j][k] = max(d[i - 1][j][k], d[i - 1][j - w[i]][k] + v[i]);
				}
				else { // 放入背包
					d[i][j][k] = max(d[i - 1][j][k],
						max(d[i - 1][j - w[i]][k], d[i - 1][j][k - w[i]]) + v[i]);
				}
			}
	//解为d[n][X][Y]
}

//5

void f2017_5()
{
	struct E { int x[N], s; };
	queue<E> q;
	E e;
	for (int i = 1; i <= n; ++i)
		e.x[i] = i;
	q.push(e);
	while (!q.empty())
	{
		E e = q.front();
		q.pop();
		if (e.s == n - 1) {
			print(e.x, n);
		}
		else {
			for (int i = e.s + 1; i <= n; ++i) {
				E new_e = e;
				new_e.x[e.s + 1] = e.x[i];
				new_e.x[i] = e.x[e.s + 1];
				new_e.s = e.s + 1;
				q.push(new_e);

			}
		}
	}
}

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
int f2017_6()
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
		min_out[i] = min_w;
		min_sum += min_w;
	}
	priority_queue<Node, vector<Node>, greater<Node>> q;
	Node e;
	for (int i = 1; i <= n; ++i)
		e.x[i] = i;
	e.s = 1; e.cw = 0; e.rw = min_sum;
	q.push(e);
	while ((e = q.top()).s < n + 1)
	{
		q.pop();
		if (e.s == n) {
			e.cw += w[e.x[e.s]][e.x[n]];
			if (e.cw < bestw) {
				bestw = e.cw;
				e.lw = bestw;
				e.s += 1;
				q.push(e);
			}
			continue;
		}
		for (int i = e.s; i <= n; ++i) {
			int cw = e.cw + w[e.x[e.s]][e.x[i]];
			int rw = e.rw - min_out[e.x[e.s]];
			int b = cw + rw;
			if (b < bestw)
			{
				Node n = e;
				n.x[e.s] = e.x[i];
				n.x[i] = e.x[e.s];
				n.s = e.s + 1;
				n.cw = cw;
				n.lw = b;
				n.rw = rw;
				q.push(n);
			}
		}
	}
	for (int i = 1; i <= n; ++i)
		bestx[i] = e.x[i];
	return bestw;
}