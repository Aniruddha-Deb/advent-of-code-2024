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
    vector<vector<bool>> visited(n, vector<bool>(m, false));

    uint64_t ans = 0;

    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if (visited[i][j]) continue;
            char c = grid[i][j];
            stack<pair<int,int>> S;
            S.push({i, j});
            visited[i][j] = true;
            uint64_t area = 0, perimeter = 0;
            while (!S.empty()) {
                auto [y0, x0] = S.top();
                S.pop();
                area += 1;
                perimeter += 4;
                for (const auto& [yp, xp] : move) {
                    int y = y0 + yp, x = x0 + xp;
                    if (y < 0 or y >= n or x < 0 or x >= m) continue;
                    if (grid[y][x] == c) {
                        perimeter--;
                        if (!visited[y][x]) {
                            S.push({y, x});
                            visited[y][x] = true;
                        }
                    }
                }
            }
            ans += area * perimeter;
        }
    }

    cout << ans << endl;

    return 0;
}
