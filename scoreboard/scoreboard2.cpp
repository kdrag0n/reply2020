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

int t, n, l;
//~ vi penalty_time(n, 0);
vi scores(n, 0);
map<int, map<ii, int>> timestamps;
map<int, vii> problems_done;
int timestamp, teamid, problemid, inputid, score;
vi teams;

bool compare_teams(int team1, int team2)
{
	if (scores[team1] == scores[team2])
	{
		int penaltytime_1 = 0, penaltytime_2 = 0;
		for (ii key: problems_done[team1])
			penaltytime_1 += timestamps[team1][key];
		for (ii key: problems_done[team1])
			penaltytime_2 += timestamps[team2][key];
		
		if (penaltytime_1 == penaltytime_2)
			return team1 > team2;
		else
			return penaltytime_1 > penaltytime_2;
	}

	return scores[team1] > scores[team2];
}

int main()
{
	ifstream infile;
	string filepath;
	cin >> filepath;
	infile.open(filepath);

	infile >> t;

	REP(x, 1, t)
	{
		infile >> n >> l;

		problems_done.clear();
		teams.clear();
		teams.resize(n);
		timestamps.clear();
		scores.clear();
		scores.resize(n);
		REP(i, 1, l)
		{
			infile >> timestamp >> teamid >> problemid >> inputid >> score;
			if (score == 1)
			{
				timestamps[teamid][{problemid, inputid}] = timestamp;
				if (find(problems_done[teamid].begin(), problems_done[teamid].end(), (ii) {problemid, inputid}) != problems_done[teamid].end())
				{
					problems_done[teamid].push_back({problemid, inputid});
					scores[teamid]++;
				}
			}
		}
		REP (i, 1, n)
		{
			teams.push_back(i);
		}

		sort(teams.begin(), teams.end(), compare_teams);

		cout << "Case #" << x << ":";
		REP(i, 0, n - 1)
		{
			cout << " " << teams[i];
		}
		
		cout << "\n";
	}

	infile.close();
}
