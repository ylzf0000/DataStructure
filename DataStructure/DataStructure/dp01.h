#pragma once
// 01背包问题
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;
const int N = 10;
const int M = 100;
int d[N][M] = { 0 };
int b[N][M] = { 0 };
int v[N];
int w[N];
int W;
int n;
void func()
{
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j <= W; ++j)
		{
			if (w[i] > j) // 放不下
			{
				d[i][j] = d[i - 1][j];
			}
			else if (d[i - 1][j] > d[i - 1][j - w[i]] + v[i]) // 能放下但是不如不放
			{
				d[i][j] = d[i - 1][j];
			}
			else // 放入背包
			{
				d[i][j] = d[i - 1][j - w[i]] + v[i];
				b[i][j] = 1;
			}
		}
}
void print_trace(int i, int j)
{
	if (i == 0 || j == 0)
		return;
	if (b[i][j] == 1)
	{
		print_trace(i - 1, j - w[i]);
		printf("%d ", i);
	}
	else
	{
		print_trace(i - 1, j);
	}
}
int main()
{
	ifstream fin("in.txt");
	fin >> n >> W;
	for (int i = 1; i <= n; ++i)
		fin >> w[i] >> v[i];
	func();
	for (int i = 0; i <= n; ++i)
	{
		for (int j = 0; j <= W; ++j)
			printf("%2d ", d[i][j]);
		puts("");
	}
	cout << d[n][W] << endl;
	print_trace(n, W);


}