#include<bits/stdc++.h>
using namespace std;

int main() {
    int count = 0;
    string firstStr, secondStr;
    cin >> firstStr >> secondStr;
    int length = firstStr.length();

    if (length == 1) {
        cout << count << endl;
        return 0;
    }

    for (size_t i = 0; i < length; i++) {
        if (firstStr[i] == '0' && secondStr[i] == '0') {
            if (i != 0) {
                if (firstStr[i-1] == '0') { //top before current index
                    firstStr[i] = '1';
                    secondStr[i] = '1';
                    count++;
                    continue;
                }

                if (secondStr[i-1] == '0') { //top before current index
                    firstStr[i] = '1';
                    secondStr[i] = '1';
                    count++;
                    continue;
                }
            }

            if (firstStr[i+1] == '0') { //top after current index
                firstStr[i+1] = '1';
                count++;
                continue;
            }

            if (secondStr[i+1] == '0') { //bottom after current index
                secondStr[i+1] = '1';
                count++;
                continue;
            }
        }
    }

    cout << count << endl;
    return 0;
}