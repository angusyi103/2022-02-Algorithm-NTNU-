#include<bits/stdc++.h>
using namespace std;


void solve(vector<vector<int>>& all_dist, vector<vector<int>>& times, int n, int k) {
        unordered_map<int, vector<pair<int,int>>> g;
        vector<int> dist(n+1, INT_MAX);
        dist[k] = 0;
        for(auto x : times) {
            g[x[0]].push_back({x[1],x[2]});
        }
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
        pq.push({0,k});
        while(!pq.empty()) {
            int node = pq.top().second;
            int d = pq.top().first;
            pq.pop();
            for(int i = 0; i < g[node].size(); i++) {
                int nxt = g[node][i].first;
                int w = g[node][i].second;
                if(dist[nxt] > d + w) {
                    dist[nxt] = d + w;
                    pq.push({dist[nxt], nxt});
                }
            }
        }
        vector<int> subv {dist.begin()+1, dist.end()};

        all_dist.push_back(subv);
    }
bool check(vector<int>& v, int node) {
    for(auto x : v) {
        if(x == node) {
            return true;
        }
    }
    return false;
}
int main () {
	ios::sync_with_stdio(false);
    cin.tie(nullptr);

	int N, M;
    cin >> N >> M;
	vector<vector<int>> times;
	for (size_t i = 0; i < M; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		times.push_back({u, v, w});
	}

    int res = INT_MAX;
    unordered_map<int,vector<int>> g;
    vector<vector<int>> all_dist;
    // vector<vector<int>> times {{1,2,3}, {2,3,4}, {3,1,5}};
    for(auto x : times) {
        g[x[0]-1].push_back(x[1]-1);
    }

    for(int i = 1; i <= N; i++)
        solve(all_dist, times, N, i);

    /*for(auto x : all_dist) {
        for(auto y : x)
            cout<<y<<" ";
        cout<<endl;
    }
    cout<<"----------"<<endl;*/
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(i != j && (all_dist[i][j] != INT_MAX && all_dist[j][i] != INT_MAX ) && !check(g[j], i)) {
                //cout<<all_dist[j][i]<<" "<<all_dist[i][j]<<endl;
                res = min(res, all_dist[j][i] + all_dist[i][j]);
            }

        }
    }
    int ans = res == INT_MAX ? -1 : res;
    cout<<ans<<endl;

    return 0;
}
