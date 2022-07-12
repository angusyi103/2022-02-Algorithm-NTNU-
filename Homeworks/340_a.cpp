#include<bits/stdc++.h>
using namespace std;

/*reference：
https://en.wikipedia.org/wiki/Subset_sum_problem
https://blog.csdn.net/yangguangqizhi/article/details/49426431?spm=1001.2101.3001.6661.1&utm_medium=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7EOPENSEARCH%7Edefault-1-49426431-blog-122638525.pc_relevant_default&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7EOPENSEARCH%7Edefault-1-49426431-blog-122638525.pc_relevant_default&utm_relevant_index=1
https://www.youtube.com/watch?v=ZHyb-A2Mte4&t=497s&ab_channel=takeUforward
6 0
-1 2 -3 4 -5 6
9223372036854775807
1099511627775
*/
unordered_map<long, int> firstMap, secondMap;

void dfs(vector<int> elements, long sum, int length, int curIndex, int endIndex, int addTo) {
    if (length > 0) {
        if (addTo == 1) {
            firstMap[sum] += 1;
        } else {
            secondMap[sum] += 1;
        }
    }
    
    for (size_t i = curIndex; i < endIndex; i++) {
        dfs(elements, sum + elements[i], length+1, i+1, endIndex, addTo);
    }
}

int main() {
    int N, T;
    cin >> N >> T;
    vector<int> firstVec, secondVec;
    for (size_t i = 0; i < N; i++) {
        int value;
        cin >> value;
        if (i < N/2) {
            firstVec.push_back(value);
        } else {
            secondVec.push_back(value);
        }
    }

    long long result = 0;
    firstMap.insert(pair<long, int> (0, 1));
    secondMap.insert(pair<long, int> (0, 1));
    dfs(firstVec, 0, 0, 0, firstVec.size(), 1);
    dfs(secondVec, 0, 0, 0, secondVec.size(), 2);

    // for (const auto& n: firstMap) {
    //     cout << "value:" << n.first << " amount:" << n.second << endl;
    // }

    // cout << "seconde" << endl;
    // for (const auto& n: secondMap) {
    //     cout << "value:" << n.first << " amount:" << n.second << endl;
    // }

    for (const auto& n: firstMap) {
        // cout << "value:" << n.first << " depth:" << n.second << " result:" << result << endl;
        long residue = T - n.first;
        // cout << "found" << secondeMap.count(residue) << endl;
        result += (long long)firstMap[n.first] * (long long)secondMap[residue];
    }

    if (result == 0) {
        cout << result << endl;
        return 0;
    }

    if (T == 0) {
        cout << result-1 << endl;
    } else {
        cout << result << endl;
    }
    return 0;
}