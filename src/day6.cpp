#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {

    vector<string> grid;
    string line;
    while (getline(cin, line)) {
        grid.push_back(line);
    }

    int n = grid.size();
    int m = grid[0].size();

    vector<vector<bool>> visited(n, vector<bool>(m, false));

    int x=-1, y=-1;
    array<pair<int,int>,4> move{{
        {0, -1}, // up
        {1,  0}, // right
        {0,  1}, // down 
        {-1, 0}  // left
    }};
    int dir = 0;

    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if (grid[i][j] == '^') {
                x = j;
                y = i;
                break;
            }
        }
    }

    if (x < 0 or y < 0) throw runtime_error("Couldn't find start");

    while (y >= 0 and y < n and x >= 0 and x < m) {
        visited[y][x] = true;
        int new_x = x + move[dir].first;
        int new_y = y + move[dir].second;
        if (new_x < 0 or new_x >= m or new_y < 0 or new_y >= n) break;
        if (grid[new_y][new_x] == '#') {
            dir = (dir+1)%4;
        }
        else {
            x = new_x;
            y = new_y;
        }
    }
        
    int ans = 0;
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            ans += visited[i][j];
        }
    }

    cout << ans << endl;

    return 0;
}
