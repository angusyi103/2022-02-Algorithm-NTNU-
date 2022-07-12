#include<bits/stdc++.h>
using namespace std;

/*reference：
https://web.ntnu.edu.tw/~algo/Graph.html
7 2
1 2
1 7
1 6
2 3
2 4
4 5
*/

int maxDepth = 0;

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

void countDistance(int node, vector<vector<int>> &nodeList, int depth, vector<int> &distanceFromFirst, vector<int> &result) {
    if (node == 0) {
        return;
    }
    // cout << "node:" << node << endl;
    distanceFromFirst[node-1] = depth;
    if (depth > maxDepth) {
        maxDepth = depth;
    }
    // printNodeList(nodeList.size()-1, nodeList);

    result.push_back(node);

    for (size_t i = 0; i < nodeList[node].size(); i++) {
        // cout << "size:" << nodeList[node].size() << endl;
        replace(nodeList[nodeList[node][i]].begin(), nodeList[nodeList[node][i]].end(), node, 0);
        // printNodeList(nodeList.size()-1, nodeList);
        countDistance(nodeList[node][i], nodeList, depth+1, distanceFromFirst, result);
    }
}

void DFS(vector<vector<int>> &nodeList, int distance, int node, int depth, vector<int> &result) {
    if (node == 0) {
        return;
    }

    if (depth > distance) {
        return;
    }

    // printNodeList(nodeList.size()-1, nodeList);
    // cout << "node:" << node << endl;

    result.push_back(node); //keep node info;
    
    for (size_t i = 0; i < nodeList[node].size(); i++) {
        replace(nodeList[nodeList[node][i]].begin(), nodeList[nodeList[node][i]].end(), node, 0); //replace connected node=>0 in other nodeAry
        DFS(nodeList, distance, nodeList[node][i], depth+1, result);
    }

}

int main() {
    int nodes, distance;
    cin >> nodes >> distance;

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
        sort(temp.begin(), temp.end());
        nodeList[i] = temp;
    }
    // cout << "ordered" << endl;
    printNodeList(nodes, nodeList);

    vector<int> result;
    for (size_t i = 1; i <= nodes; i++) {
        result.clear();
        vector<vector<int>> temp = nodeList;
        DFS(temp, distance, i, 0, result);
        if (result.size() == nodes) {
            break;
        }
    }

    if (result.size() != nodes) {
        cout << -1 << endl;
        return 0;
    }

    for (size_t i = 0; i < nodes; i++) {
        cout << result[i] << " ";
    }

    return 0;

    vector<vector<int>> tempList = nodeList;
    vector<int> distanceFromFirst(nodes, 0); //{0,0,0,0,0,0,0} -> {0,1,2,2,3,1,1}
    countDistance(1, tempList, 0, distanceFromFirst, result);

    if (maxDepth <= distance) { //safe track
        for (size_t i = 0; i < nodes; i++) {
            cout << result[i] << " ";
        }
        return 0;
    } 
    // else if (maxDepth - distance > distance) { //no track
    //     cout << -1;
    //     return 0;
    // }

    // cout << "dis:" << endl;
    // for (size_t i = 0; i < distanceFromFirst.size(); i++) {
    //     cout << distanceFromFirst[i] << " ";
    // }
    // cout << endl;

    for (size_t i = 1; i < distanceFromFirst.size(); i++) {
        if (distanceFromFirst[i] <= distance) { //possible node to start
            // cout << "start node:" << i+1 << endl;
            result.clear();
            vector<vector<int>> temp = nodeList;
            DFS(temp, distance, i+1, 0, result);
            if (result.size() == nodes) { //to do
                for (size_t j = 0; j < nodes; j++) {
                    cout << result[j] << " ";
                }
                return 0;
            }
        }
    }

    cout << -1 << endl;
    return 0;
}