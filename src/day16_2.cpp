#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

enum Direction {
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3

};

Direction opp(Direction some) {
    switch(some) {
        case UP:    return DOWN;
        case RIGHT: return LEFT;
        case DOWN:  return UP;
        case LEFT:  return RIGHT;
    }
}

int main() {

    vector<string> grid;
    string line;
    while (getline(cin, line)) {
        grid.push_back(line);
    }

    int n = grid.size();
    int m = grid[0].size();

    cout << m << " " << n << endl;

    array<pair<Direction,pair<int,int>>,4> movemap{{
        {UP,    {0, -1}},
        {RIGHT, {1,  0}},
        {DOWN,  {0,  1}},
        {LEFT,  {-1, 0}}
    }};

    int sx=-1,sy=-1;
    int ex=-1,ey=-1;
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if (grid[i][j] == 'S') {
                sy = i;
                sx = j;
            }
            if (grid[i][j] == 'E') {
                ey = i;
                ex = j;
            }
        }
    }

    set<tuple<int,Direction,pair<int,int>>> S;
    vector<vector<vector<int>>> cost(4, vector<vector<int>>(n, vector<int>(m, 2e9)));
    vector<vector<vector<pair<int,int>>>> parents(n, vector<vector<pair<int,int>>>(m, vector<pair<int,int>>()));
    S.insert({0,RIGHT,{sx, sy}});
    cost[RIGHT][sy][sx] = 0;
    while (!S.empty()) {
        auto [dist, dir, pos] = *S.begin();
        auto [x, y] = pos;
        // cout << dir << " " << x << " " << y << endl;
        S.erase(S.begin());
        for (auto [d, p] : movemap) {
            if (d == opp(dir)) continue;
            int c;
            auto [px, py] = p;
            int nx, ny;
            if (d != dir) {
                c = 1000;
                nx = x, ny = y;
            }
            else {
                c = 1;
                nx=x+px, ny=y+py;
            }
            if (grid[ny][nx] == '#') continue;

            // cout << "  " << d << " " << nx << " " << ny << endl;

            if (dist + c < cost[d][ny][nx]) {
                S.erase({cost[d][ny][nx], d, {nx, ny}});
                cost[d][ny][nx] = dist + c;
                if (ny != y or nx != x) parents[ny][nx].push_back({x, y});
                S.insert({cost[d][ny][nx], d, {nx, ny}});
            }
        }
    }

    cout << min({cost[UP][ey][ex], cost[RIGHT][ey][ex], cost[DOWN][ey][ex], cost[LEFT][ey][ex]}) << endl;

    return 0;
}
