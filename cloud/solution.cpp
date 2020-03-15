/*
 * C++ code template for CP
 * 
 * While running, input the name of the test file first
 * Then let it read the file via infile stream
 * 
 * Usage: 
 * 	./solution > output_file
 *	Enter the path of input file and boom.
 * 
 */


#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef map<string, int> msi;

#define REP(i, a, b) \
	for (int i = a; i <= b; i++)

int main()
{
	ifstream infile;
	string filepath;
	cin >> filepath;
	infile.open(filepath);

	int t;
	infile >> t;

	REP(x, 1, t)
	{
		int n, p;
		infile >> n >> p;

		int cp[n];
		REP(i, 1, n)
		{
			infile >> cp[i - 1];
		}

		ll sum;
		ll diff;
		int best_diff = INT_MAX;
		int best_l, best_r;
		for (int l = 0; l < n; l++)
		{
			sum = cp[l];
			diff = sum - p;
			if (diff >= 0 && diff < best_diff)
			{
				best_diff = diff;
				best_l = l;
				best_r = l;
			}
			for (int r = l + 1; r < n; r++)
			{
				sum += cp[r];
				diff = sum - p;
				if (diff < 0) continue;
				if (diff >= 0 && diff < best_diff)
				{
					best_diff = diff;
					best_l = l;
					best_r = r;
				}
				if (diff > best_diff) break;
			}
			if (best_diff == 0)
				break;
		}

		cout << "Case #" << x << ": " << best_l << " " << best_r << "\n";
	}

	infile.close();
}
