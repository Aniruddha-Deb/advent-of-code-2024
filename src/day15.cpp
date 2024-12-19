#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <set>
#include <stack>

using namespace std;

int main() {

    vector<vector<char>> grid;
    string line;
    vector<int> moves;
    bool parsing_grid = true;
    while (getline(cin, line)) {
        if (line.size() == 0) {
            parsing_grid = false;
            continue;
        }
        if (parsing_grid) {
            grid.push_back(vector<char>(line.begin(), line.end()));
        }
        else {
            for (char c : line) {
                switch(c) {
                    case '^': moves.push_back(0); break;
                    case '>': moves.push_back(1); break;
                    case 'v': moves.push_back(2); break;
                    case '<': moves.push_back(3); break;
                }
            }
        }
    }

    int n = grid.size();
    int m = grid[0].size();

    array<pair<int,int>,4> movemap{{
        {0, -1}, // up
        {1,  0}, // right
        {0,  1}, // down 
        {-1, 0}  // left
    }};

    int x=-1,y=-1;
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if (grid[i][j] == '@') {
                y = i;
                x = j;
                goto move_boxes;
            }
        }
    }

move_boxes:

    for (int move : moves) {
        // for (int i=0; i<n; i++) {
        //     for (int j=0; j<n; j++) {
        //         cout << grid[i][j];
        //     }
        //     cout << endl;
        // }
        // cout << endl;
        // cout << move << " " << x << " " << y << endl;
        auto [px, py] = movemap[move];
        int sx=x,sy=y;
        while (grid[sy][sx] == '@' or grid[sy][sx] == 'O') {
            sx += px;
            sy += py;
        }
        // cout << move << " " << sx << " " << sy << " " << x << " " << y << endl;
        if (grid[sy][sx] == '.') {
            // move everything forward
            // cout << "Moving:" << endl;
            while (!(sy == y and sx == x)) {
                char t = grid[sy][sx];
                grid[sy][sx] = grid[sy-py][sx-px];
                grid[sy-py][sx-px] = t;
                sy-=py;
                sx-=px;
            }
            x+=px;
            y+=py;
        }
    }

    uint64_t ans = 0;
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            cout << grid[i][j];
            if (grid[i][j] == 'O') {
                ans += 100*i + j;
            }
        }
        cout << endl;
    }

    cout << ans << endl;

    return 0;
}
