#include<bits/stdc++.h>
using namespace std;

#define inf 1e11

/*reference：
https://web.ntnu.edu.tw/~algo/Path.html#5
https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/
*/

int N, M;
int H, S1, S2, C;

struct Edge {
    int u;
    int v;
    int w;
};

class Graph {
    int V;
    list<pair<int, int>> *adj;

    public:
    Graph( int V )
	{
		this->V = V ;
		adj = new list<pair<int, int>> [V+1];
	}

    void addEdge(Edge e);
    long long Dijkstra(int u, int v);
    void printAdj();
};

void Graph :: addEdge(Edge e) {
    adj[e.u].push_back(make_pair(e.v, e.w));
    adj[e.v].push_back(make_pair(e.u, e.w));
}

long long Graph :: Dijkstra(int start, int end) {
    vector<int> visited(N+1, false);
    vector<long long> node(N+1, inf);
    node[start] = 0;
    visited[start] = true;

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    pq.push(make_pair(0, start));

    while (!pq.empty()) {
        int selectedIdx = pq.top().second;
        pq.pop();
        visited[selectedIdx] = true;

        //selected the end node
        if (selectedIdx == end) return node[end];

        for (auto i = adj[selectedIdx].begin(); i != adj[selectedIdx].end(); i++) {
            int v = i->first;
            int w = i->second;

            //relaxation
            if (!visited[v] && node[v] > node[selectedIdx] + w) {
                node[v] = node[selectedIdx] + w;
                pq.push(make_pair(node[v], v));
            }
        }
    }

    return node[end];
}

void Graph :: printAdj() {
    for (int i = 0; i <= N; i++) {
        cout << "node: " << i;
        for (auto x = adj[i].begin(); x != adj[i].end(); x++) {
            cout << "-> (" << x->first << "," << x->second << ")";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    cin >> H >> S1 >> S2 >> C;
    Graph g(N);
    for (size_t i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        Edge e {u, v, w};
        g.addEdge(e);
    }

    // g.printAdj();

    // cout << g.Dijkstra(H, S1) << endl;
    // cout << g.Dijkstra(S1, S2) << endl;
    // cout << g.Dijkstra(S2, C) << endl;
    // cout << g.Dijkstra(C, H) << endl;
    
    cout << g.Dijkstra(H, S1) + g.Dijkstra(S1, S2) + g.Dijkstra(S2, C) + g.Dijkstra(C, H) << endl;
    return 0;
}
