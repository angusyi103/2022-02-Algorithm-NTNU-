#include<bits/stdc++.h>
using namespace std;

/*reference：
https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-using-stl-in-c/
http://alrightchiu.github.io/SecondRound/minimum-spanning-treekruskals-algorithm.html
http://alrightchiu.github.io/SecondRound/setyi-arraybiao-shi.html
*/

/*
sort all weighted edge
Kruskal find max spanning tree => the last is bottleneck
then find min spanning tree

for edge larger than bottleneck from max to min
    delete edge 
    if tree has every node 
        if has cycle 
            continue
        else 
            return result
    else 
        add back edge
*/

int N, M;

struct Edge {
    int u;
    int v;
    int w;
};

int findSetCollapsing(int *subset, int i) {
    int root;
    for (root = i; subset[root] >= 0; root = subset[root]);

    while(i != root) {
        int parent = subset[i];
        subset[i] = root;
        i = parent;
    }

    return root;
}

void unionSet(int *subset, int x, int y) {
    int xroot = findSetCollapsing(subset, x);
    int yroot = findSetCollapsing(subset, y);

    if (subset[xroot] <= subset[yroot]) {
        subset[xroot] += subset[yroot];
        subset[yroot] = xroot; 
    } else {
        subset[yroot] += subset[xroot];
        subset[xroot] = yroot;
    }
}

class Graph {
    int V;
    vector<pair<int, pair<int, int>>> edgeList;
    vector<pair<int, pair<int, int>>> increaseEdgeList;

    public:
    Graph( int V )
	{
		this->V = V;
	}

    void addEdge(Edge e);
    void removeEdge(int bottleNeck);
    int KruskalFindBottleNeck();
    int KruskalMST();
};

void Graph :: addEdge(Edge e) {
    edgeList.push_back({e.w, {e.u, e.v}});
}

void Graph :: removeEdge(int bottleNeck) {
    for (auto e = edgeList.begin(); e != edgeList.end(); e++) {
        int w = e->first;
        if (w >= bottleNeck) {
            int u = e->second.first;
            int v = e->second.second;
            increaseEdgeList.push_back({w, {u, v}});
        } else {
            break;
        }
    }
    reverse(increaseEdgeList.begin(), increaseEdgeList.end());
}   

bool cmp(pair<int, pair<int, int>> e1, pair<int, pair<int, int>> e2) {
    return e1.first > e2.first;
}

int Graph :: KruskalFindBottleNeck() {
    int result;
    sort(edgeList.begin(), edgeList.end(), cmp);

    int subset[N+1];
    for (size_t i = 0; i < N+1; i++) {
        subset[i] = -1;
    }

    for (auto i = edgeList.begin(); i != edgeList.end(); i++) {
        int u = i->second.first;
        int v = i->second.second;

        int setU = findSetCollapsing(subset, u);
        int setV = findSetCollapsing(subset, v);

        if (setU != setV) {
            result = i->first; //last added edge weight == bottleneck            
            unionSet(subset, u, v);
        }
    }
    
    return result;
}

int Graph :: KruskalMST() {
    int result = 0;
    int subset[N+1];
    for (size_t i = 0; i < N+1; i++) {
        subset[i] = -1;
    }

    for (auto i = increaseEdgeList.begin(); i != increaseEdgeList.end(); i++) {
        int u = i->second.first;
        int v = i->second.second;

        int setU = findSetCollapsing(subset, u);
        int setV = findSetCollapsing(subset, v);

        if (setU != setV) {
            result += i->first;        
            // cout << i->first << endl;  
            unionSet(subset, u, v);
        }
    }
    
    return result;
}

int main () {
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

    int bottleNeck = g.KruskalFindBottleNeck();
    // cout << bottleNeck << endl;
    g.removeEdge(bottleNeck);
    cout << g.KruskalMST() << endl;
    return 0;
}
