#include<bits/stdc++.h>
using namespace std;

/*reference：
https://leetcode.com/problems/maximum-alternating-subsequence-sum/discuss/1886038/c%2B%2B-oror-easy-oror-small
odd length：a-b+c
even length：a-b+c-d
record the largest odd & even from first index to current index
*/

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int input;
    cin >> input;
    vector<int> treasures;
    for (size_t i = 0; i < input; i++) {
        int treasure;
        cin >> treasure;
        treasures.push_back(treasure);
    }

    int odd= 0, even = 0;
    for (size_t i = 0; i < input; i++) {
        odd = max(odd, even+treasures[i]);
        even = max(even, odd-treasures[i]);
    }

    cout << odd << endl;
    return 0;
}