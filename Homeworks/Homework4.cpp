#include<bits/stdc++.h>
using namespace std;

//reference:
//https://www.geeksforgeeks.org/counting-inversions/
//https://lakesd6531.pixnet.net/blog/post/344227318
//https://alrightchiu.github.io/SecondRound/comparison-sort-merge-sorthe-bing-pai-xu-fa.html
//https://www.youtube.com/watch?v=owZhw-A0yWE&ab_channel=TECHDOSE
//https://stackoverflow.com/questions/58110255/counting-inversions-with-merge-sort-gives-a-negative-number-if-the-array-length

void PrintArray(vector<int> &array){
    for (int i = 0; i < array.size(); i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

string checkOrder(vector<int> a, vector<int> b, int input) {
    int idxA = 0, idxB = 0;
    for (size_t i = 0; i < input - 1; i++) {
        if (idxA == idxB) {
            if (a[idxA] > b[idxB]) {
                return "no";
            }
            idxA++;
        } else if (idxA > idxB) {
            if (a[idxA] < b[idxB]) {
                return "no";
            }
            idxB++;
        }
    } 

    return "yes";
}

long long mergeSortCombine(vector<int> &a, int front, int end, int m) {
    vector<int> final(end - front + 1);
    int idxLeft = front, idxRight = m, idxCurrent = 0;
    long long count = 0;
    while ((idxLeft <= m-1) && (idxRight <= end)) {
        if (a[idxLeft] < a[idxRight]) {
            final[idxCurrent++] = a[idxLeft++]; 
        } else {
            final[idxCurrent++] = a[idxRight++];
            count += (m - idxLeft);
        }
    }

    while (idxLeft <= m-1) {
        final[idxCurrent++] = a[idxLeft++];
    }

    while (idxRight <= end) {
        final[idxCurrent++] = a[idxRight++];
    }

    for (size_t i = 0; i <= final.size()-1; i++) {
        a[i+front] = final[i];
    }

    return count;
}

long long mergeSort(vector<int> &a, int front, int end) {
    long long count = 0;
    if (front < end) {
        int m = (front + end) / 2;
        count += mergeSort(a, front, m);
        count += mergeSort(a, m+1, end);
        count += mergeSortCombine(a, front, end, m+1);
    }
    return count;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int input;
    long long result = 0;
    cin >> input;
    vector<int> oddIndexAry, evenIndexAry;
    for (size_t i = 0; i < input; i++) {
        int value;
        cin >> value;
        if (i % 2 == 0) {
            evenIndexAry.push_back(value);
        } else {
            oddIndexAry.push_back(value);
        }
    }

    result += mergeSort(evenIndexAry, 0, evenIndexAry.size()-1);
    result += mergeSort(oddIndexAry, 0, oddIndexAry.size()-1);
    PrintArray(evenIndexAry);
    PrintArray(oddIndexAry);
    cout << checkOrder(evenIndexAry, oddIndexAry, input) << endl;
    cout << result << endl;
    return 0;
}