#include<bits/stdc++.h>
using namespace std;
#define inf 1e8

/*Reference：
https://www.geeksforgeeks.org/print-all-the-cycles-in-an-undirected-graph/
https://www.geeksforgeeks.org/find-minimum-weight-cycle-undirected-graph/
https://web.ntnu.edu.tw/~algo/Cycle.html#3
*/

int N, M;

void floyd_warshall(long long &result, vector<vector<int>> &adj, vector<vector<int>> &all_dist) {
    for (size_t k = 1; k <= N; k++) {
        for (size_t i = 1; i <= k; i++) {
            for (size_t j = 1; j <= k; j++) {
                // cout << "(i,j,k) " << i << j << k << endl;
                if (i != j && adj[k][i] + all_dist[i][j] + adj[j][k] < result) {
                    result = adj[k][i] + all_dist[i][j] + adj[j][k];
                }
                // cout << result << endl;
            }
        }

        for (size_t i = 1; i <= N; i++) {
            for (size_t j = 1; j <= N; j++) {
                if (all_dist[i][k] + all_dist[k][j] < all_dist[i][j]) {
                    all_dist[i][j] = all_dist[i][k] + all_dist[k][j];
                }
            }
        }
    }
} 

void printAdj(vector<vector<int>> adj) {
    for (size_t i = 1; i <= N; i++) {
        for (size_t j = 1; j <= N; j++) {
            cout << adj[i][j] << "              ";
        }
        cout << endl;
    }
}

int main() {
    cin >> N >> M;
    vector<vector<int>> adj(N+1, vector<int>(N+1, inf));

    for (size_t i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u][v] = w;
        adj[v][u] = w;
    }

    // printAdj(adj);

    long long result = inf;
    vector<vector<int>> all_dist = adj;
    floyd_warshall(result, adj, all_dist);

    if (result == inf) cout << -1 << endl;
    else cout << result << endl;
    return 0;
}