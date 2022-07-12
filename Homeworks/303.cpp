#include<bits/stdc++.h>
using namespace std;

/*
reference：
https://blog.csdn.net/chengonghao/article/details/51915753
https://web.ntnu.edu.tw/~algo/KnapsackProblem.html
*/

void knapSack(int type, int capacity, vector<int> weight, vector<int> value, vector<int> amount, vector<int> &result) {
    for (int i = 0; i < type; i++) {
        int num = min(amount[i], capacity/weight[i]);
        for (int k = 1; num > 0; k*=2) {
            if (k > num) {
                k = num;
            }
            num -= k;
            for (int j = capacity; j >= weight[i] * k; j--) {
                result[j] = max(result[j], result[j - weight[i] * k] + value[i] * k);
            }
        } 
    }  
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int type, capacity;
    cin >> type >> capacity;
    vector<int> weightAry, valueAry, amountAry;
    for (size_t i = 0; i < type; i++) {
        int w, v, a;
        cin >> w >> v >> a;
        weightAry.push_back(w);
        valueAry.push_back(v);
        amountAry.push_back(a);
    }
    vector<int> result(capacity + 1, 0);
    knapSack(type, capacity, weightAry, valueAry, amountAry, result);
    
    cout << result[result.size() - 1] << endl;
    return 0;
}