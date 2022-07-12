#include<bits/stdc++.h>
using namespace std;

int nodes, maxDepth;

void printNodeList(int nodes, vector<vector<int>> nodeList) {
    cout << "nodeList:" << endl;
    for (size_t i = 0; i < nodes+1; i++) {
        vector<int>:: iterator iter = nodeList[i].begin();
        cout << i << ": ";
        for (size_t j = 0; iter != nodeList[i].end(); j++, iter++) {
            cout << *iter << " ";
        }
        cout << endl;
    }
}

bool preOrderTraversal(vector<vector<int>> nodeList, int startNode, unordered_map<int, int> &visited, stack<int> &st, vector<int> &depth, vector<int> &result) {
    result.push_back(startNode);
    visited[startNode] = 1;
    for (size_t i = 0; i < nodeList[startNode].size(); i++) {
        if (visited[nodeList[startNode][i]] == 0) {
            st.push(nodeList[startNode][i]);
            depth[nodeList[startNode][i]] = depth[startNode] + 1;
            if (depth[startNode] + 1 > maxDepth) {
                return false;
            }
        }
    }

    while (!st.empty()) {
        int temp = st.top();
        st.pop();
        if (!preOrderTraversal(nodeList, temp, visited, st, depth, result)) {
            return false;
            // break;
        }
    } 
    
    return true;
}

void DFS1(vector<vector<int>> nodeList, int from, int to, vector<int> &depth, int &max, vector<int> &result) {
    result.push_back(to);
    for (size_t i = 0; i < nodeList[to].size(); i++) {
        // cout << "node: " << nodeList[to][i] << endl;
        if (nodeList[to][i] != from) {
            depth[nodeList[to][i]] = depth[from] + 1;
            if (depth[from] + 1 > maxDepth) {
                max = depth[from] + 1;
                return;
            }
            DFS1(nodeList, to, nodeList[to][i], depth, max, result);
        }
    }
}

int main() {
    cin >> nodes >> maxDepth;
    vector<int> a;
    vector<vector<int>> nodeList(nodes+1, a);
    for (size_t i = 0; i < nodes-1; i++) {
        int begin, end;
        cin >> begin >> end;
        nodeList[begin].push_back(end);
        nodeList[end].push_back(begin);
    }

    for (size_t i = 0; i < nodes; i++) {
        vector<int> temp = nodeList[i];
        sort(temp.begin(), temp.end(), greater<int>());
        // sort(temp.begin(), temp.end());
        nodeList[i] = temp;
    }

    printNodeList(nodes, nodeList);

    vector<int> result;
    for (size_t i = 1; i <= nodes; i++) {
        stack<int> st;
        unordered_map<int, int> visited;
        vector<int> result1, depth(nodes+1, 0);
        if (preOrderTraversal(nodeList, i, visited, st, depth, result1)) {
            for (size_t j = 0; j < result1.size(); j++) {
                cout << result1[j] << " ";
            }

            return 0;
        } 
    }

    cout << -1 << endl;
    return 0;

    
    for (size_t i = 1; i <= nodes; i++) {
        vector<int> visited(nodes+1, 0), depth(nodes+1, 1);
        stack<int> st;
        st.push(i);

        // result.clear();
        // depth.clear();
        int max = 0;
        DFS1(nodeList, i, i, depth, max, result);
        // DFS(nodeList, visited, st, 0, result);

        if (max > maxDepth) {
            result.clear();
            depth.clear();
            max = 0;
            continue;
        } else {
            break;
        }
    }

    if (result.empty()) {
        cout << -1 << endl;
    } else {
        for (size_t i = 0; i < result.size(); i++) {
            cout << result[i] << " ";
        }
    }

    // if (result.size() != nodes) {
    //     cout << -1 << endl;
    // } else {
    //     for (size_t i = 0; i < result.size(); i++) {
    //         cout << result[i] << " ";
    //     }
    // }
    return 0;
}