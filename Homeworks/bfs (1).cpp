#include<bits/stdc++.h>
using namespace std;


vector<vector<int>> dir {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int bfs(vector<string>& g) {

    int h = g.size(), w = g[0].length();
    vector<vector<int>> t(h, vector<int>(w, -1));
    queue<pair<int, int>> q;
    int dx = 0, dy = 0;
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            if(g[i][j] == 'L')
                q.push({i, j});
            else if(g[i][j] == 'D') {
                dx = i;
                dy = j;
            }
        }
    }
    int time = 0;
    bool canReachB = false, canReachD = false;
    while(!q.empty()) {
        time++;
        int len = q.size();
        for(int i = 0; i < len; i++) {
            int x = q.front().first, y = q.front().second;
            q.pop();
            for(int j = 0; j < 4; j++) {
                int newx = x + dir[j][0];
                int newy = y + dir[j][1];
                if(newx < 0 || newx >= h || newy < 0 || newy >= w)
                    continue;
                if(g[newx][newy] == 'B') {
                    canReachB = true;
                }
                else if(g[newx][newy] == 'D') {
                    canReachD = true;
                }
                if(g[newx][newy] != 'C')
                    continue;
                q.push({newx, newy});
                g[newx][newy] = '*';
                t[newx][newy] = time;
            }
        }
    }
    for(auto x : g) {
        for(auto y : x)
            cout<<y<<" ";
        cout<<endl;
    }
    cout<<"======="<<endl;
    for(auto x : t) {
        for(auto y : x)
            cout<<y<<" ";
        cout<<endl;
    }

    bool check = canReachB & canReachD;

    int res = -1;
    if(check) {
        for(int j = 0; j < 4; j++) {
            int newx = dx + dir[j][0];
            int newy = dy + dir[j][1];
            if(newx < 0 || newx >= h || newy < 0 || newy >= w)
                continue;
            res = max(res, t[newx][newy]);
        }
    }

    return (res == 1 || !check) ? -1 : res-1;

}


int main() {
    int h, w;
    cin >> h >> w;
    vector<string> g;
    for (size_t i = 0; i < h; i++) {
        string str;
        cin >> str;
        g.push_back(str);
    }

    cout << bfs(g) << endl;
    return 0;
}
