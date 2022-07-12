#include<bits/stdc++.h>
using namespace std;
              
#define module 1000000007

int solve(vector<int> &boxes) {
    long long result = 0;
    std::unordered_map<int, int> position; //{ value: index }
    int index = 0;
    priority_queue<int, vector<int>, greater<int>> priorityQueue; 
    for (size_t i = 0; i < boxes.size(); i++) {
        position.insert(pair<int, int> (boxes[i], i)); // [4,3,0,1,2] {[3,0],[4,1],[5,2],[2,3],[1,4]}
        // position[boxes[i]] = i; 
        priorityQueue.push(boxes[i]); //[3,4,5,2,1] => [1,2,3,4,5]
    }

    while (!priorityQueue.empty()) {
        long long currentMin = priorityQueue.top(); //current min number in left
        // cout << currentMin << endl;
        priorityQueue.pop();
        long long indexDistant = abs(position[currentMin] - index) % module;
        result += (((indexDistant * (long long)boxes[index] % module)) % module + ((indexDistant % module) * (currentMin % module)) % module) % module;
        result = result % module;

        int temp1 = position[boxes[index]]; //index box[0] = 3, positioin[3] = 0
        int temp2 = boxes[index]; // value box[0] = 3
        position[boxes[index]] = position[currentMin]; //change index  position[3] = position[1] = 4
        boxes[index] = boxes[position[currentMin]]; // change value
        boxes[position[currentMin]] = temp2; // boxes[4] = 3
        position[currentMin] = temp1; // position[1] = 0

        index++;
    }

    return result;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int input;
    cin >> input;
    vector<int> boxes;
    for (size_t i = 0; i < input; i++) {
        int value; 
        cin >> value;
        boxes.push_back(value);
    }

    cout << solve(boxes);
    return 0;
}
