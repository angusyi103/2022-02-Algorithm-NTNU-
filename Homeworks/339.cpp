#include<bits/stdc++.h>
using namespace std;

/* 
3 4 => 0 2 0 3
CLCD
CCCC
BCLC
*/

int row, column, maxTime = 0;

int checkWayOut1(vector<vector<int>> &fillTime, set<pair<int, int>> &bedList, set<pair<int, int>> &doorList, int curTime) {
    // // add four way: room[i-1][j], room[i+1][j], room[i][j-1], room[i][j+1] 
    // cout << "fillTime:" << endl;
    // for (size_t i = 0; i < row; i++) {
    //     for (size_t j = 0; j < column; j++) {
    //         cout << fillTime[i][j] << " "; 
    //     }
    //     cout << endl;
    // }

    if (bedList.empty() || doorList.empty()) {
        return 2;
    }

    set<pair<int, int>> nextRoundDoorList;
    for (auto floor : doorList) {
        fillTime[floor.first][floor.second] = -3;

        if (floor.first - 1 >= 0) { // top
            if (fillTime[floor.first-1][floor.second] == -2) { // hit door
                return 1;
            }
            if (fillTime[floor.first-1][floor.second] != -1 && fillTime[floor.first-1][floor.second] > curTime) {
                nextRoundDoorList.insert(pair<int, int> (floor.first-1, floor.second));
            }
        } 

        if (floor.first + 1 < row) { // down
            if (fillTime[floor.first+1][floor.second] == -2) { // hit door
                return 1;
            }
            if (fillTime[floor.first+1][floor.second] != -1 && fillTime[floor.first+1][floor.second] > curTime) {
                nextRoundDoorList.insert(pair<int, int> (floor.first+1, floor.second));
            }
        }

        if (floor.second - 1 >= 0) { // left
            if (fillTime[floor.first][floor.second-1] == -2) { // hit door
                return 1;
            }
            if (fillTime[floor.first][floor.second-1] != -1 && fillTime[floor.first][floor.second-1] > curTime) {
                nextRoundDoorList.insert(pair<int, int> (floor.first, floor.second-1));
            }
        }

        if (floor.second + 1 < column) { // right
            if (fillTime[floor.first][floor.second+1] == -2) { // hit door
                return 1;
            }
            if (fillTime[floor.first][floor.second+1] != -1 && fillTime[floor.first][floor.second+1] > curTime) {
                nextRoundDoorList.insert(pair<int, int> (floor.first, floor.second+1));
            }
        }
    }

    set<pair<int, int>> nextRoundBedList;
    for (auto floor : bedList) {
        // cout << "lava: (" << lava.first << ", " << lava.second << ") " << "depth: " << depth << " ";
        fillTime[floor.first][floor.second] = -2;

        if (floor.first - 1 >= 0) { // top
            if (fillTime[floor.first-1][floor.second] == -3) { // hit door
                return 1;
            }
            if (fillTime[floor.first-1][floor.second] != -1 && fillTime[floor.first-1][floor.second] > curTime) {
                nextRoundBedList.insert(pair<int, int> (floor.first-1, floor.second));
            }
        } 

        if (floor.first + 1 < row) { // down
            if (fillTime[floor.first+1][floor.second] == -3) { // hit door
                return 1;
            }
            if (fillTime[floor.first+1][floor.second] != -1 && fillTime[floor.first+1][floor.second] > curTime) {
                nextRoundBedList.insert(pair<int, int> (floor.first+1, floor.second));
            }
        }

        if (floor.second - 1 >= 0) { // left
            if (fillTime[floor.first][floor.second-1] == -3) { // hit door
                return 1;
            }
            if (fillTime[floor.first][floor.second-1] != -1 && fillTime[floor.first][floor.second-1] > curTime) {
                nextRoundBedList.insert(pair<int, int> (floor.first, floor.second-1));
            }
        }

        if (floor.second + 1 < column) { // right
            if (fillTime[floor.first][floor.second+1] == -3) { // hit door
                return 1;
            }
            if (fillTime[floor.first][floor.second+1] != -1 && fillTime[floor.first][floor.second+1] > curTime) {
                nextRoundBedList.insert(pair<int, int> (floor.first, floor.second+1));
            }
        }
    }

    return checkWayOut1(fillTime, nextRoundBedList, nextRoundDoorList, curTime);
}

// add four way: room[i-1][j], room[i+1][j], room[i][j-1], room[i][j+1] 
void bfsLava(vector<vector<char>> &room, set<pair<int, int>> &lavaList, int &depth, vector<vector<int>> &fillTime) {
    if (lavaList.empty()) {
        return;
    }

    if (depth > maxTime) {
        maxTime = depth;
    }

    set<pair<int, int>> nextRoundList; //(0,2) (1,1) (1,3)
    for (auto lava : lavaList) {
        // cout << "lava: (" << lava.first << ", " << lava.second << ") " << "depth: " << depth << " ";
        fillTime[lava.first][lava.second] = depth;
        if (lava.first - 1 >= 0) { // top
            if (room[lava.first-1][lava.second] != 'O' && room[lava.first-1][lava.second] != 'B' && room[lava.first-1][lava.second] != 'D' && fillTime[lava.first-1][lava.second] == -1) {
                nextRoundList.insert(pair<int, int> (lava.first-1, lava.second));
            }
        } 

        if (lava.first + 1 < row) { // down
            if (room[lava.first+1][lava.second] != 'O' && room[lava.first+1][lava.second] != 'B' && room[lava.first+1][lava.second] != 'D' && fillTime[lava.first+1][lava.second] == -1) {
                nextRoundList.insert(pair<int, int> (lava.first+1, lava.second));
            }
        }

        if (lava.second - 1 >= 0) { // left
            if (room[lava.first][lava.second-1] != 'O' && room[lava.first][lava.second-1] != 'B' && room[lava.first][lava.second-1] != 'D' && fillTime[lava.first][lava.second-1] == -1) {
                nextRoundList.insert(pair<int, int> (lava.first, lava.second-1));
            }
        }

        if (lava.second + 1 < column) { // right
            if (room[lava.first][lava.second+1] != 'O' && room[lava.first][lava.second+1] != 'B' && room[lava.first][lava.second+1] != 'D' && fillTime[lava.first][lava.second+1] == -1) {
                nextRoundList.insert(pair<int, int> (lava.first, lava.second+1));
            }
        }
    }

    depth++;
    bfsLava(room, nextRoundList, depth, fillTime);
}

int main() {
    int result = -1;
    cin >> row >> column;
    vector<vector<char>> room;
    pair<int, int> bed, door;
    set<pair<int, int>> lavaList, bedList, doorList;
    for (size_t i = 0; i < row; i++) {
        vector<char> tiles;
        for (size_t j = 0; j < column; j++) {
            char temp;
            cin >> temp;
            tiles.push_back(temp);
            if (temp == 'L') {
                lavaList.insert(pair<int, int> (i, j));
            }

            if (temp == 'B') {
                bed = pair<int, int> (i, j);
                bedList.insert(pair<int, int> (i, j));
            }

            if (temp == 'D') {
                door = pair<int, int> (i, j);
                doorList.insert(pair<int, int> (i, j));
            }
        }
        room.push_back(tiles);
    }

    vector<vector<int>> fillTime(row, vector<int>(column, -1));
    int depth = 0;
    bfsLava(room, lavaList, depth, fillTime);

    fillTime[bed.first][bed.second] = -2; //bed
    fillTime[door.first][door.second] = -3; // door

    // cout << "fillTime:" << endl;
    // for (size_t i = 0; i < row; i++) {
    //     for (size_t j = 0; j < column; j++) {
    //         cout << fillTime[i][j] << " "; 
    //     }
    //     cout << endl;
    // }

    int left = 0, right = maxTime;
    unordered_map<int, int> checkList;
    //checkwayout(500) == true, checkwayout(501) == false, result == 500
    while (left <= right) {
        int curTime = left + (right - left) / 2;
        // cout << "curTime: " << curTime << endl;
        vector<vector<int>> temp1 = fillTime, temp2 = fillTime;
        // bool pivot = checkWayOut(temp1, bedList, curTime);
        // bool plusOne = checkWayOut(temp2, bedList, curTime+1);

        int pivot, plusOne;
        // 0 = init, 1 = true, 2 = false

        if (checkList[curTime] == 0) {
            pivot = checkWayOut1(temp1, bedList, doorList, curTime);
            checkList[curTime] = pivot;
        } else {
            pivot = checkList[curTime];
        }

        if (checkList[curTime+1] == 0) {
            plusOne = checkWayOut1(temp2, bedList, doorList, curTime+1);
            checkList[curTime+1] = plusOne;
        } else {
            plusOne = checkList[curTime+1];
        }

        if (pivot == 1 && plusOne == 2) {
            result = curTime;
            break;
        }

        if (pivot == 2) {
            right = curTime-1;
        } else {
            left = curTime+1;
        }
    } 


    if (result == 0) {
        cout << -1 << endl;
    } else {
        cout << result << endl;
    }
    return 0;
}