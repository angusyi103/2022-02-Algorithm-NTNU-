#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> circle;

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

void dfs(int start, unordered_map<int,vector<int>>& g, vector<int>& visited, vector<int>& p, int node, int step) {
    if(visited[node]) {
        if(node == start && step > 2) {
            circle.push_back(p);
            return;
        }
        else
            return;
    }
    visited[node] = 1;
    p.push_back(node);
    for(auto x : g[node])
        dfs(start, g, visited, p, x, step+1);
    visited[node] = 0;
    p.pop_back();
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
    // vector<vector<int>> times {{1,2,1}, {6,1,1}, {1,3,1}, {2,1,1}, {3,1,1}, {2,3,1}, {3,2,2}, {1,4,1}, {4,5,1}, {5,6,1}, {1,6,1}};
    //vector<vector<int>> times {{1,2,3}, {2,3,4}, {2,1,2}};
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
    vector<vector<int>> path;
    for(int i = 0; i < N; i++) {
        vector<int> visited(N, 0);
        vector<int> path;
        dfs(i, g, visited, path, i, 0);
    }
    set<vector<int>> uset;
    for(auto x : circle) {
        sort(x.begin(), x.end());
        uset.insert(x);
    }
    for(auto x : uset) {
        int dist = 0;
        for(int i = 0; i < x.size(); i++) {
            if(i+1 < x.size())
                dist += all_dist[x[i]][x[i+1]];
            else
                dist += all_dist[x[i]][x[0]];
        }
        res = min(res, dist);
    }
    int ans = res == INT_MAX ? -1 : res;
    cout<<ans<<endl;

    return 0;
}