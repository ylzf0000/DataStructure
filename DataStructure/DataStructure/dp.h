#pragma once
#include <algorithm>
using namespace std;



const int N = 15;
int I[N];
int d[N][N];//d[i][j]Ϊǰi�����ֵ����j�˻�
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
	//��Ϊd[n][k]
}
