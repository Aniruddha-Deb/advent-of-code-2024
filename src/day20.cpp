#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <map>
#include <climits>

using namespace std;

vector<pair<int,int>> get_cells_at(int x, int y, int n, int m, int s) {
    vector<pair<int,int>> cells;
    for (int i=y-s; i<=y+s; i++) {
        for (int j=x-s; j<=x+s; j++) {
            if (j < 0 or j >= m or i < 0 or i >= n) continue;
            int d = abs(x-j) + abs(y-i);
            if (d <= s) {
                cells.push_back({j, i});
            }
        }
    }

    return cells;
}

int main() {

    vector<string> grid;
    string line;
    while (getline(cin, line)) {
        grid.push_back(line);
    }

    int n = grid.size();
    int m = grid[0].size();

    int sx=-1, sy=-1, ex=-1, ey=-1;
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if (grid[i][j] == 'S') {
                sx = j; sy = i;
            }
            else if (grid[i][j] == 'E') {
                ex = j; ey = i;
            }
        }
    }
    assert(sx != -1 and sy != -1 and ex != -1 and ey != -1);

    // cout << sx << " " << sy << " " << ex << " " << ey << endl;

    array<pair<int,int>,4> move{{
        {0, -1}, // up
        {1,  0}, // right
        {0,  1}, // down 
        {-1, 0}  // left
    }};

    vector<vector<int>> dist(n, vector<int>(m, -1));
    dist[sy][sx] = 0;
    int x=sx, y=sy;
    while (!(x == ex and y == ey)) {
        int pdist = dist[y][x];
        for (auto [px, py] : move) {
            int nx=x+px, ny=y+py;
            if (dist[ny][nx] == -1 and grid[ny][nx] != '#') {
                dist[ny][nx] = pdist+1;
                y = ny; x = nx;
                break;
            }
        }
    }

    vector<int> sc({2, 20});
    for (int s : sc) {
        map<int,int> cheat_count;
        x=sx, y=sy;
        while (!(x == ex and y == ey)) {
            // iterate over all the cells that are within s of the dist
            auto cells = get_cells_at(x, y, n, m, s);
            // cout << x << "," << y << ": ";

            for (auto [cx, cy] : cells) {
                int saved = dist[cy][cx] - dist[y][x] - abs(x-cx) - abs(y-cy);
                if (saved > 0) {
                    // cout << "[" << cx << "," << cy << "," << saved << "] ";
                    // valid cheat
                    cheat_count[saved]++;
                }
            }
            for (auto [px, py] : move) {
                int nx=x+px, ny=y+py;
                if (dist[ny][nx] == dist[y][x]+1) {
                    y = ny; x = nx;
                    break;
                }
            }
            // cout << endl;
        }
        int ans = 0;
        for (auto [saved, count] : cheat_count) {
            // cout << saved << ": " << count << endl;
            if (saved >= 100) ans += count;
        }
        cout << ans << endl;
    }

    
    return 0;
}
