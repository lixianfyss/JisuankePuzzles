#include<iostream>
#include<vector>
using namespace std;

short digitfib(unsigned short first, unsigned short second, int n)
{
	unsigned short last_1 = first, last_2 = second, next = 0, i, location = 0;
	vector<short> numSeries(2, 0); numSeries.reserve(20);
	numSeries[0] = first; numSeries[1] = second;
	if (n < 3)	return numSeries[n - 1];
	while (numSeries.size() < n)
	{
		next = last_1 + last_2;
		if (next < 10)
		{
			last_1 = last_2; last_2 = next;
		}
		else
		{
			last_1 = 1; last_2 = next - 10; numSeries.push_back(1);
		}
		for (i = 0; i < numSeries.size() - 1; i++)
		{
			if (last_1 == numSeries[i] && last_2 == numSeries[i + 1])
			{
				location = (n - i) % (numSeries.size() - 1 - i); location += location ? (i - 1) : (numSeries.size() - 2);
				return numSeries[location];
			}
		}
		numSeries.push_back(last_2);
	}
	return numSeries[n - 1];
}
int main()
{
	unsigned short first = 0, second = 0, line = 0; cin >> line;
	vector<short> result(line, 0);
	for (int i = 0; i < line; i++)
	{
		int n = 0;
		cin >> first >> second >> n;
		result[i] = digitfib(first, second, n);
	}
	for (int i = 0; i < line; i++)
		cout << "Case #" << i+1 << ": " << result[i] << endl;
	return 0;
}