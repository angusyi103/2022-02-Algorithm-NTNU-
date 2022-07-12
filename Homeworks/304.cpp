#include<bits/stdc++.h>
using namespace std;

/*reference：
https://yuihuang.com/cses-1639/
https://rust-algo.club/levenshtein_distance/
https://stackoverflow.com/questions/6080958/ocr-weighted-levenshtein-distance
*/

int minRotate(int a, int b, int rotate) {
    if (abs(a-b) > 13) {
        return (min(a,b) + 26 - max(a,b)) * rotate;
    } 

    return abs(a-b) * rotate;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int add, remove, rotate;
    cin >> add >> remove >> rotate;
    string beginStr, endStr;
    cin >> beginStr >> endStr;
    int beginLength = beginStr.length();
    int endLength = endStr.length();
    vector<int> result(beginLength+1, 0);
    for (size_t i = 0; i <= beginLength; i++) { // initial ary
        result[i] = i*remove;
    }

    for (int i = 1; i <= endLength; i++) {
        vector<int> temp(beginLength+1, 0);
        temp[0] = i*add;
        for (int j = 1; j <= beginLength; j++) {
            //temp = min(pre, temp[j]+1, temp[j-1]+1)
            int left = temp[j-1] + remove;
            int top = result[j] + add;
            int leftTop = result[j-1];
            if (endStr[i-1] != beginStr[j-1]) {
                leftTop += minRotate(endStr[i-1], beginStr[j-1], rotate);
            }
            temp[j] = min({left, top, leftTop});
        }

        result = temp;
    }

    cout << result[result.size()-1] << endl;
    return 0;
}