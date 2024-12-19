#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <queue>

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
    S.insert({0,RIGHT,{sx, sy}});
    cost[RIGHT][sy][sx] = 0;
    while (!S.empty()) {
        auto [dist, dir, pos] = *S.begin();
        auto [x, y] = pos;
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

            if (dist + c <= cost[d][ny][nx]) {
                S.erase({cost[d][ny][nx], d, {nx, ny}});
                cost[d][ny][nx] = dist + c;
                S.insert({cost[d][ny][nx], d, {nx, ny}});
            }
        }
    }

    auto p1_ans = min({cost[UP][ey][ex], cost[RIGHT][ey][ex], cost[DOWN][ey][ex], cost[LEFT][ey][ex]});
    cout << "Part 1: " << p1_ans << endl;

    set<pair<int,int>> cells;
    queue<tuple<int,Direction,int,int>> Q;
    for (int dir=0; dir<4; dir++) {
        if (cost[dir][ey][ex] == p1_ans) Q.push({p1_ans,(Direction)dir, ex, ey});
    }

    cells.insert({ex, ey});

    while (!Q.empty()) {
        auto [t, dir, x, y] = Q.front();
        Q.pop();
        // iterate through parents, and if the minimum value propagates, add the 
        // parent to cells and to the queue
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
                nx=x-px, ny=y-py;
            }

            if (cost[d][ny][nx] == t-c) {
                Q.push({t-c,d,nx,ny});
                cells.insert({nx, ny});
            }
        }
    }

    cout << "Part 2: " << cells.size() << endl;

    return 0;
}
