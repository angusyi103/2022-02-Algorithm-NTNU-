#include<bits/stdc++.h>
using namespace std;
#define inf 0x3f3f3f3f

/*Reference：
https://www.geeksforgeeks.org/print-all-the-cycles-in-an-undirected-graph/
https://www.geeksforgeeks.org/find-minimum-weight-cycle-undirected-graph/
https://web.ntnu.edu.tw/~algo/Cycle.html#3
*/

/*
　甲、暫時拿掉邊ij，權重改成無限大。
　乙、求出j點到i點的最短路徑。
　丙、放回邊ij，形成一個環，即是強制經過邊ij的最小環。
　丁、權重最小者即是最小環。
*/

int N, M;

struct Edge {
    int u;
    int v;
    int w;
};

class Graph {
    int V;
    list<pair<int, int>> *adj;
    vector<Edge> edgeList;

    public:
    Graph( int V )
	{
		this->V = V ;
		adj = new list<pair<int, int>> [V+1];
	}

    void addEdge(Edge e);
    void removeEdge(Edge e);
    int Dijkstra(int start, int end, vector<int> &route);
    int findSmallestCycle();
    void printAdj();
};

void Graph :: addEdge(Edge e) {
    adj[e.u].push_back(make_pair(e.v, e.w));
    adj[e.v].push_back(make_pair(e.u, e.w));
    edgeList.push_back(e);
}

void Graph :: removeEdge(Edge e) {
    adj[e.u].remove(make_pair(e.v, e.w));
    adj[e.v].remove(make_pair(e.u, e.w));
}

int Graph :: Dijkstra(int start, int end, vector<int> &route) {
    vector<int> visited(N+1, false);
    vector<int> node(N+1, inf);
    node[start] = 0;
    visited[start] = true;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push(make_pair(0, start));

    while (!pq.empty()) {
        int selectedIdx = pq.top().second;
        pq.pop();

        if (route.size() == 1 && selectedIdx == end) continue;
        if (selectedIdx == end) return node[end]; //selected the end node

        visited[selectedIdx] = true;
        route.push_back(selectedIdx);

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

    return inf;
}

int Graph :: findSmallestCycle() {
    int result = inf;

    for (size_t i = 0; i < M; i++) {
        Edge e = edgeList[i];
        removeEdge(e);
        vector<int> route;
        int shortPath = Dijkstra(e.u, e.v, route);

        // cout << "route: ";
        // for (size_t j = 0; j < route.size(); j++) {
        //     cout << route[j] << " ";
        // }
        // cout << endl;
       
        result = min(result, shortPath + e.w);
        addEdge(e);
    }

    if (result == inf) return -1;
    return result;
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
    Graph g(N);
    for (size_t i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        Edge e {u, v, w};
        g.addEdge(e);
    }
    
    // g.printAdj();
    // cout << g.Dijkstra(1, 5) << endl; 
    // cout << g.Dijkstra(1, 4) << endl;
    // cout << g.Dijkstra(5, 2) << endl;
    // cout << g.Dijkstra(5, 4) << endl;

    cout << g.findSmallestCycle() << endl;
    return 0;
}