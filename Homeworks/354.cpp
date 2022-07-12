#include<bits/stdc++.h>
using namespace std;

int N, M;

struct NodeInfo {
    int value;
    vector<int> route;
};

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
    int extraCost(int node, int AorB, vector<int> route);
    int dfs(vector<int> &A, vector<int> &B);
    void printAdj();
};

void Graph :: addEdge(Edge e) {
    adj[e.u].push_back(make_pair(e.v, e.w));
    adj[e.v].push_back(make_pair(e.u, e.w));
}

int Graph :: extraCost(int node, int AorB, vector<int> route) {
    int result = 0;
    for (auto i = adj[node].begin(); i != adj[node].end(); i++) {
        if (route.size() >= i->first) {
            result += route[i->first] == AorB ? 0 : i->second;
        }
    }
    
    return result;
}

struct cmp {
    bool operator() (NodeInfo n1, NodeInfo n2) {
        return n1.value > n2.value;
    }
};


int Graph :: dfs(vector<int> &A, vector<int> &B) {
    priority_queue<NodeInfo, vector<NodeInfo>, cmp> pq;
    pq.push(NodeInfo{A[1], {0,0}}); //select A
    pq.push(NodeInfo{B[1], {0,1}}); //select B

    while (!pq.empty()) {
        NodeInfo selectNode = pq.top();
        pq.pop();
        int value = selectNode.value;
        vector<int> route = selectNode.route;
        int curPerson = route.size();

        vector<int> routeA = route, routeB = route;
        routeA.push_back(0);
        routeB.push_back(1);
        int extraA = extraCost(curPerson, 0, routeA);
        int extraB = extraCost(curPerson, 1, routeB);
        int valueA = value + A[curPerson] + extraA;
        int valueB = value + B[curPerson] + extraB;
        if (routeA.size() == N+1) return min(valueA, valueB);
        pq.push(NodeInfo{valueA, routeA});
        pq.push(NodeInfo{valueB, routeB});
    }

    return -1;
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

int main () {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    Graph g(N);

    vector<int> A(1,0), B(1,0);
    for (size_t i = 0; i < N; i++) {
        int value;
        cin >> value;
        A.push_back(value);
    }

    for (size_t i = 0; i < N; i++) {
        int value;
        cin >> value;
        B.push_back(value);
    }

    // vector<vector<int>> adjMatrix(N+1, vector<int>(N+1, 0)); //store unhappieness when not choosing the same dorm
    for (size_t i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        Edge e {u, v, w};
        g.addEdge(e);
        // adjMatrix[u][v] = w;
        // adjMatrix[v][u] = w;
    }

    // g.printAdj();

    cout << g.dfs(A, B) << endl;
    return 0;
}
