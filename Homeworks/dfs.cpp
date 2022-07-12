#include <bits/stdc++.h>
using namespace std;

void dfs(unordered_map<int, vector<int>>& g, vector<int>& visited, int node, int step, int n, int d, vector<int>& path) {

    if(step > d)
        return;
    if(visited[node])
        return;
    visited[node] = true;
    path.push_back(node);
    for(int i = 0; i < g[node].size(); i++) {
        if(!visited[g[node][i]]) {
            dfs(g, visited, g[node][i], step+1, n, d, path);
        }
    }
}

vector<int> solve(int n, int d, vector<vector<int>>& v) {

    unordered_map<int, vector<int>> tmp;
    for(auto node : v) {
        tmp[node[0]].push_back(node[1]);
        tmp[node[1]].push_back(node[0]);
    }
    unordered_map<int, vector<int>> g;
    for(auto ele : tmp) {
        vector<int> tmpv = ele.second;
        sort(tmpv.begin(), tmpv.end());
        g[ele.first] = tmpv;
    }
    for(int i = 1; i <= n; i++) {

        vector<int> visited(n+1, false);
        vector<int> path;
        dfs(g, visited, i, 0, n, d, path);
        if(path.size() == n)
            return path;
    }
    return {-1};

}


int main() {

    vector<vector<int>> v {{1,2}, {1,6}, {1,7}, {2,3}, {2,4}, {4,5}};
    vector<int> res;
    res = solve(7, 2, v);
    for(auto x : res) {
        cout<<x<<" ";
    }
    cout<<endl;
    vector<vector<int>> v2 {{1,8}, {8,5}, {1,6}, {8,10}, {6,9}, {5,2}, {1,4}, {1,3}, {4,7}};
    vector<int> res2;
    res2 = solve(10, 2, v2);
    for(auto x : res2) {
        cout<<x<<" ";
    }
    cout<<endl;
    vector<vector<int>> v3 {{1,3}, {1,9}, {9,6}, {9,4}, {9,10}, {6,8}, {9,2}, {1,7}, {8,5}};
    vector<int> res3;
    res3 = solve(10, 9, v3);
    for(auto x : res3) {
        cout<<x<<" ";
    }


    return 0;

}
