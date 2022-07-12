#include <bits/stdc++.h>
using namespace std;

void DFS(unordered_map<int, set<int>> &orderedList, vector<int> &visited, int node, int depth, int &maxDepth, int nodes, int distance, vector<int> &result) {
    // cout << "node: " << node << endl;
    if (depth > maxDepth) {
        maxDepth = depth;
    }
    if (depth > distance) return;
    if (visited[node]) return;
    visited[node] = true;
    result.push_back(node);
    for (auto iter : orderedList[node]) {
        // cout << "node: " << iter << endl;
        if (maxDepth > distance) {
            return;
        }
        if (!visited[iter]) {
            DFS(orderedList, visited, iter, depth+1, maxDepth, nodes, distance, result);
        }
    }
    // for (size_t i = 0; i < orderedList[node].size(); i++) {
    //     if (maxDepth > distance) {
    //         return;
    //     }
    //     // if (!visited[orderedList[node][i]]) {
    //     //     DFS(orderedList, visited, orderedList[node][i], depth+1, maxDepth, nodes, distance, result);
    //     // }
    // }
}

int main() {
    int nodes, distance;
    cin >> nodes >> distance;

    unordered_map<int, set<int>> nodeList;
    for (size_t i = 0; i < nodes-1; i++) {
        int begin, end;
        cin >> begin >> end;
        nodeList[begin].insert(end);
        nodeList[end].insert(begin);
    }

    // unordered_map<int, set<int>> orderedList;
    // for (auto element : nodeList) {
    //     set<int> temp = element.second;
    //     sort(temp.begin(), temp.end());
    //     orderedList[element.first] = temp;
    // }

    for (size_t i = 1; i <= nodes; i++) {
        vector<int> visited(nodes+1, false);
        vector<int> result;
        int maxDepth = 0;
        // cout << "round: " << i << endl;
        DFS(nodeList, visited, i, 0, maxDepth, nodes, distance, result);
        if (result.size() == nodes) {
            for (size_t j = 0; j < nodes; j++) {
                cout << result[j] << " ";
            }
            return 0;
        }
    }
    
    cout << -1 << endl;
    return 0;
}