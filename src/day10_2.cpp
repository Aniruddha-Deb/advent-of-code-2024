#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <queue>

using namespace std;

int main() {

    vector<string> grid;
    string line;
    while (getline(cin, line)) {
        for (char& c : line) c -= '0';
        grid.push_back(line);
    }

    int n = grid.size();
    int m = grid[0].size();

    array<pair<int,int>,4> move{{
        {0, -1}, // up
        {1,  0}, // right
        {0,  1}, // down 
        {-1, 0}  // left
    }};
    uint64_t ans = 0;
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if (grid[i][j] != 0) continue;
            map<pair<int,int>,int> paths;
            set<pair<int,int>> vis;
            queue<pair<int,int>> S;
            S.push({i, j});
            paths[{i, j}] = 1;
            vis.insert({i, j});
            while (!S.empty()) {
                auto [y0, x0] = S.front();
                S.pop();
                for (const auto& [yp, xp] : move) {
                    int y = y0 + yp, x = x0 + xp;
                    if (y < 0 or y >= n or x < 0 or x >= m) continue;

                    if (grid[y][x] == grid[y0][x0]-1 and vis.contains({y, x})) {
                        paths[{y0, x0}] += paths[{y, x}];
                        continue;
                    }
                    else if (grid[y][x] == grid[y0][x0]+1 and !vis.contains({y, x})) {
                        S.push({y, x});
                        vis.insert({y, x});
                        paths[{y, x}] = 0;
                    }
                }
                if (grid[y0][x0] == 9) {
                    ans += paths[{y0,x0}];
                    continue;
                }
            }
        }
    }

    cout << ans << endl;

    return 0;
}
