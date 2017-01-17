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
int new_line(int x, int y)
{
	int t_sum = 0, mark_j = floor(y / 2.0), mark_k = floor((x + 1) / 2.0);
	for (int j = 1; j <= mark_j; j++)
	{
		for (int k = 1; k < mark_k; k++)
		{
			if (reciprocal(j, k)) t_sum += k;
		}
		for (int k = mark_k; k < x; k++)
		{
			if (reciprocal(j, k)) t_sum += x - k;
		}
	}
	for (int j = mark_j + 1; j <= y; j++)	for (int k = 1; k < x; k++)
	{
		if (reciprocal(j, k)) t_sum += x - k;
	}
	return t_sum;
}
int main()
{
	int n, x, y, sum = 0, temp;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> x >> y; if (x < y)
		{
			temp = y; y = x; x = temp;
		}
		for (int j = 2; j < y; j++)
		{
			sum += (2 * new_line(x, j)) % max;
		}
		sum += x*x + y; cout << sum << endl; sum = 0;
	}
}