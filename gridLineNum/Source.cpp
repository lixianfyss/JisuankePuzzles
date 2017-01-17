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
int new_line(int x, int y, int &sum_lu, int &sum_ld, int &sum_r)
{
	int t_sum = 0, mark_v = floor(y / 2.0), mark_h = floor((x + 1) / 2.0), border = 0;
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
	int n, x, y, sum = 0, temp, sum_lu = 0, sum_ld = 0, sum_r = 0;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> x >> y; if (x < y)
		{
			temp = y; y = x; x = temp;
		}
		for (int j = 2; j < y; j++)
		{
			sum += (2 * new_line(x, j, sum_lu, sum_ld, sum_r)) % max;
		}
		sum += x*x + y; cout << sum << endl; sum = 0; sum_lu = 0; sum_ld = 0; sum_r = 0;
	}
}