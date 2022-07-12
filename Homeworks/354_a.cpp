#include<bits/stdc++.h>
using namespace std;

/*reference:
https://www.geeksforgeeks.org/ford-fulkerson-algorithm-for-maximum-flow-problem/
https://alrightchiu.github.io/SecondRound/flow-networksmaximum-flow-ford-fulkerson-algorithm.html
*/

int N, M;

bool bfs(vector<vector<int>> &residualAdj, int s, int t, int predecessor[]) {
    int visited[N+3];
    for (size_t i = 0; i < N+3; i++) {
        visited[i] = false;
        predecessor[i] = -1;
    }

    queue<int> q;
    q.push(s);
    visited[s] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 1; v < N+3; v++) {
            if (visited[v] == false && residualAdj[u][v] > 0) {
                if (v == t) {
                    predecessor[v] = u;
                    return true;
                }
                q.push(v);
                predecessor[v] = u;
                visited[v] = true;
            }
        }
    }
    
    return false;
}

int max_flow(vector<vector<int>> &adj, int s, int t) {
    int result = 0;
    vector<vector<int>> residualAdj = adj;
    
    int predecessor[N+3];
    while(bfs(residualAdj, s, t, predecessor)) {
        int curFlow = INT_MAX;
        for (int v = t; v != s; v = predecessor[v]) {
            int u = predecessor[v];
            curFlow = min(curFlow, residualAdj[u][v]);
        }

        for (int v = t; v != s; v = predecessor[v]) { //update residual
            int u = predecessor[v];
            residualAdj[u][v] -= curFlow;
            residualAdj[v][u] += curFlow;
        }

        result += curFlow;
    }

    return result;ㄨㄛ
}

void printAdj(vector<vector<int>> adj) {
    for (int i = 0; i < adj.size(); i++) {
        for (int j = 0; j < adj[i].size(); j++) {
            cout << adj[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> N >> M;
    vector<vector<int>> adj(N+3, vector<int> (N+3, 0));

    for (int i = 1; i <= N; i++) {
        int value;
        cin >> value;
        adj[N+1][i] = value;
    }

    for (int i = 1; i <= N; i++) {
        int value;
        cin >> value;
        adj[i][N+2] = value;
    }

    for (int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u][v] = w;
        adj[v][u] = w;
    }

    // printAdj(adj);

    cout << max_flow(adj, N+1, N+2) << endl;
    return 0;
}