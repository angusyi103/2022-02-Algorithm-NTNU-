#include<bits/stdc++.h>
using namespace std;

/*reference：
https://web.ntnu.edu.tw/~algo/Subsequence.html
*/

int LIS(int size, vector<int> v) {
    vector<int> length(size, 1);
    for (size_t i = 0; i < length.size(); i++) {
        for (size_t j = 0; j < i; j++) {
            if (v[j] <= v[i]) {
                length[i] = max(length[i], length[j]+1);
            }
        }
    }

    int max = -1;
    for (size_t i = 0; i < length.size(); i++) {
        if (length[i] > max) {
            max = length[i];
        }
    }

    return max;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int input;
    cin >> input;
    vector<vector<int>> treasures;
    for (size_t i = 0; i < input; i++) {
        int x, y;
        cin >> x >> y;
        vector<int> treasure;
        treasure.push_back(x);
        treasure.push_back(y);
        treasures.push_back(treasure);
    }

    sort(treasures.begin(), treasures.end());

    vector<int> yAxis;
    for (size_t i = 0; i < input; i++) {
        yAxis.push_back(treasures[i][1]);
    }

    cout << LIS(input, yAxis) << endl;
    return 0;
}