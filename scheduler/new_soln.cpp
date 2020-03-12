#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#include <stack>
#include <map>
#include <ctype.h>

using namespace std;

#define loop(n) for (int i = 0; i < n; ++i) 
#define loopll(n) for (long long i = 0; i < n; ++i)
#define loop2(i,k,n) for (i = k; i <= n; ++i) 
#define loopb(i,k,n) for (i = k; i >= n; --i)
#define remove_space(x) x.erase(remove(x.begin(), x.end(), ' '), x.end())
typedef long long ll;

int main(){
    
    ios_base::sync_with_stdio(false);
 
	ifstream infile;
	string filepath;
	cin >> filepath;
	infile.open(filepath); 

    int t;
    infile >> t;

    vector<ll> answers;

    loop(t){

    	ll n,k,m;
    	infile >> n >> k >> m;

    	vector< pair <ll,ll> > PS;

    	loopll(n){

    		ll p,s;
    		infile >> p >> s;

    		PS.push_back(make_pair(p,s));
    	}

    	ll leastTime = INT_MAX;

    	for(int i=0; i<n; ++i){

    		ll timeSpent = 0;

    		ll taskPerServer = m / k;

    		timeSpent += PS[i].first;
    		timeSpent += PS[i].second * taskPerServer;

    		for(int j=i+1; j<=k; ++j){
    			timeSpent += PS[j].first + PS[j].second * taskPerServer;
    		}

    		leastTime = min(timeSpent,leastTime);
    	}

    	answers.push_back(leastTime);

    }

	int x;
    loopb(x, 1, t){
    	cout << "Case #" << x << ": " << answers[x - 1] << endl;
    }

    infile.close();
	return 0;
}
