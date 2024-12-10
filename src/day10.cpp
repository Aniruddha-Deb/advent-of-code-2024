
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <stack>

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
    int ans = 0;
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if (grid[i][j] != 0) continue;
            set<pair<int,int>> vis;
            stack<pair<int,int>> S;
            S.push({i, j});
            vis.insert({i, j});
            int score = 0;
            while (!S.empty()) {
                auto [y0, x0] = S.top();
                S.pop();
                if (grid[y0][x0] == 9) {
                    score++;
                    continue;
                }
                for (const auto& [yp, xp] : move) {
                    int y = y0 + yp, x = x0 + xp;
                    if (y < 0 or y >= n or x < 0 or x >= m) continue;
                    if (vis.contains({y, x})) continue;
                    if (grid[y][x] != grid[y0][x0]+1) continue;
                    S.push({y, x});
                    vis.insert({y, x});
                }
            }
            ans += score;
        }
    }

    cout << ans << endl;

    return 0;
}
