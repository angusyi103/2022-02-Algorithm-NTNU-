#include<bits/stdc++.h>
using namespace std;

/*reference：
https://www.youtube.com/watch?v=kyLxTdsT8ws&list=PLDN4rrl48XKpZkf03iYFl-O29szjTrs_O&index=66&ab_channel=AbdulBari
https://stackoverflow.com/questions/43078142/subset-sum-with-negative-values-in-c-or-c
https://stackoverflow.com/questions/62012005/count-all-subsets-of-integers-including-negative-that-sum-to-x
https://en.wikipedia.org/wiki/Subset_sum_problem
https://blog.csdn.net/yangguangqizhi/article/details/49426431?spm=1001.2101.3001.6661.1&utm_medium=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7EOPENSEARCH%7Edefault-1-49426431-blog-122638525.pc_relevant_default&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7EOPENSEARCH%7Edefault-1-49426431-blog-122638525.pc_relevant_default&utm_relevant_index=1
https://www.youtube.com/watch?v=ZHyb-A2Mte4&t=497s&ab_channel=takeUforward
*/

int backTrack(int curIndex, long sum, vector<int> elements, unordered_map<long, int> &dp) {
    if (sum == 0) {
        return 1;
    }

    if (curIndex == 0) {
        if (elements[curIndex] == sum) {
            return 1;
        } else {
            return 0;
        }  
    }

    

    int notPick = backTrack(curIndex-1, sum, elements, dp);
    int pick = backTrack(curIndex-1, sum - elements[curIndex], elements, dp);
    return pick + notPick;
}

int main() {
    int N, T;
    cin >> N >> T;
    vector<int> elements;
    for (size_t i = 0; i < N; i++) {
        int si;
        cin >> si;
        elements.push_back(si);
    }

    unordered_map<long, int> dp;

    cout << backTrack(N-1, T, elements, dp) << endl;
    return 0;
}
