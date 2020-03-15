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
		int n, k;
		ll m;

		infile >> n >> k >> m;
		vi p;
		vi s;

		REP(i, 1, n)
		{
			int temp, temp2;
			infile >> temp >> temp2;
			p.push_back(temp);
			s.push_back(temp2);
		}
		cerr << m;

		int result = -1;
		for (int c = 0; true; c++)
		{
			int tasks_done[n];
			for (int i = 0; i < n; i++)
			{
				tasks_done[i] = max(0, (c - p[i]) / s[i]);
				sort(tasks_done, tasks_done + n, greater<int>());
				if (accumulate(tasks_done, tasks_done + k, 0) >= m)
				{
					result = c;
					break;
				}
			}
			if (result != -1)
				break;
		}

		cout << "Case #" << x << ": " << result << "\n";
	}

	infile.close();
}