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
		// Code here, replace result with variable name used for output

		cout << "Case #" << x << ": " << result << "\n";
	}

	infile.close();
}
