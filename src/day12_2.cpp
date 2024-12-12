#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <stack>

using namespace std;

int main() {

    vector<string> grid;
    string line;
    string dummy = "@";
    while (getline(cin, line)) {
        grid.push_back("@"+line+"@");
    }

    int m = grid[0].size();

    string row_buf(m, '@');
    grid.insert(grid.begin(), row_buf);
    grid.push_back(row_buf);
    int n = grid.size();

    array<pair<int,int>,4> move{{
        {0, -1}, // up
        {1,  0}, // right
        {0,  1}, // down 
        {-1, 0}  // left
    }};
    array<pair<int,int>,4> corner{{
        {1,  -1}, // topright
        {1,   1}, // bottomright 
        {-1,  1}, // bottomleft
        {-1, -1}  // topleft
    }};
    vector<vector<bool>> visited(n, vector<bool>(m, false));

    uint64_t ans = 0;

    for (int i=1; i<n-1; i++) {
        for (int j=1; j<m-1; j++) {
            if (visited[i][j]) continue;
            char c = grid[i][j];
            stack<pair<int,int>> S;
            S.push({i, j});
            visited[i][j] = true;
            uint64_t area = 0, verts = 0;
            while (!S.empty()) {
                auto [y0, x0] = S.top();
                S.pop();
                area += 1;
                for (int k=0; k<4; k++) {
                    auto [yp1, xp1] = move[k];
                    auto [yp2, xp2] = move[(k+1)%4];
                    auto [yc, xc] = corner[k];

                    int x = x0+xp1, y=y0+yp1;
                    if (!visited[y][x] and grid[y][x] == c) {
                        S.push({y, x});
                        visited[y][x] = true;
                    }

                    // DC
                    // BA
                    if (grid[y0][x0] != grid[y0+yp1][x0+xp1] and 
                        grid[y0][x0] != grid[y0+yp2][x0+xp2] and 
                        grid[y0][x0] != grid[y0+yc][x0+xc]) {
                        verts++;
                    }
                    // BA
                    // AA
                    else if (grid[y0][x0] == grid[y0+yp1][x0+xp1] and 
                             grid[y0][x0] == grid[y0+yp2][x0+xp2] and 
                             grid[y0][x0] != grid[y0+yc][x0+xc]) {
                        verts++;
                    }
                    // AC
                    // BA
                    else if (grid[y0][x0] != grid[y0+yp1][x0+xp1] and 
                             grid[y0][x0] != grid[y0+yp2][x0+xp2] and 
                             grid[y0][x0] == grid[y0+yc][x0+xc]) {
                        verts++;
                    }
                }
            }
            ans += area * verts;
        }
    }

    cout << ans << endl;

    return 0;
}
