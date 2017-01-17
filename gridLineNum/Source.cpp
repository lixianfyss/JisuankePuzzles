#include<iostream>
#include<cmath>
#define max 1073741824
using namespace std;

bool reciprocal(int x, int y)
{
	int temp;
	if (x < y)
	{
		temp = y; y = x; x = temp;
	}
	while (y != 0 && y != 1)
	{
		temp = x%y; x = y; y = temp;
	}
	if (y == 0) return false;
	return true;
}
unsigned int new_line(int x, int y, unsigned int &sum_lu, unsigned int &sum_ld, unsigned int &sum_r)
{
	unsigned int t_sum = 0; int mark_v = floor(y / 2.0), mark_h = floor((x + 1) / 2.0), border = 0;
	if (y % 2 == 0)
	{
		for (int i = 1; i < mark_h; i++)
		{
			if (reciprocal(mark_v, i)) sum_lu += i;
			if (reciprocal(y, i)) sum_ld += x - i;
		}
		for (int i = mark_h; i < x; i++)
		{
			if (reciprocal(y - 1, i)) sum_r += x - i;	if (reciprocal(y, i)) sum_r += x - i;
		}
		sum_lu %= max; sum_ld %= max; sum_r %= max;
		t_sum = sum_lu + sum_ld + sum_r;
	}
	else
	{
		for (int i = 1; i < mark_h; i++)
		{
			if (reciprocal(mark_v + 1, i)) border += x - i;
			if (reciprocal(y, i)) sum_ld += x - i;
		}
		for (int i = mark_h; i < x; i++)
		{
			if (reciprocal(y, i)) t_sum += x - i;
		}
		t_sum += sum_lu + sum_ld + sum_r; sum_ld -= border; border = 0;
	}
	return t_sum;
}
int main()
{
	int n, *x, *y, temp; unsigned int sum = 0, sum_lu = 0, sum_ld = 0, sum_r = 0;
	cin >> n; x = new int[n]; y = new int[n];
	for (int i = 0; i < n; i++)
	{
		cin >> x[i] >> y[i]; if (x[i] < y[i])
		{
			temp = y[i]; y[i] = x[i]; x[i] = temp;
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 2; j < y[i]; j++)
		{
			sum += (2 * new_line(x[i], j, sum_lu, sum_ld, sum_r)) % max;
		}
		sum += (x[i] * x[i] + y[i]) % max; cout << sum << endl; sum = 0; sum_lu = 0; sum_ld = 0; sum_r = 0;
	}
	delete[] x; delete[] y;
}