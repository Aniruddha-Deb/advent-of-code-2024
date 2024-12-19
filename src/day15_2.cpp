#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

bool can_move(vector<string>& G, pair<int,int> pos, pair<int,int> dir) {
    auto [x1, y] = pos;
    auto [px, py] = dir;
    if (G[y][x1] == '#') {
        return false;
    }
    if (G[y][x1] == '@') return can_move(G, {x1+px, y+py}, dir);
    if (G[y][x1] == '.') return true;
    int x2=x1+1;
    if (G[y][x1] == ']') x2 = x1-1;


    if (py == 0) {
        int x = min(x2,x1)-1;
        if (px == 1) x = max(x2,x1)+1;
        return can_move(G, {x, y}, dir);
    }
    else {
        y += py;
        return (can_move(G, {x1,y}, dir) and can_move(G, {x2,y}, dir));
    }
}

bool do_move(vector<string>& G, pair<int,int> pos, pair<int,int> dir, bool movechk) {
    if (!movechk) movechk = can_move(G, pos, dir);
    if (!movechk) {
        return false;
    }
    auto [x1, y] = pos;
    if (!(G[y][x1] == '[' or G[y][x1] == ']' or G[y][x1] == '@')) return true;
    int x2=x1+1;
    if (G[y][x1] == ']') x2 = x1-1;

    auto [px, py] = dir;

    if (G[y][x1] == '@') {
        do_move(G, {x1+px, y+py}, dir, true);
        swap(G[y+py][x1+px], G[y][x1]);
        return true;
    }

    if (py == 0) {
        int xl = min(x1, x2), xr = max(x1, x2);
        if (px == -1) {
            do_move(G, {xl-1, y}, dir, true);
            swap(G[y][xl], G[y][xl-1]);
            swap(G[y][xr], G[y][xl]);
        }
        else {
            do_move(G, {xr+1, y}, dir, true);
            swap(G[y][xr], G[y][xr+1]);
            swap(G[y][xl], G[y][xr]);
        }
    }
    else {
        do_move(G, {x1, y+py}, dir, true);
        do_move(G, {x2, y+py}, dir, true);
        swap(G[y][x1], G[y+py][x1]);
        swap(G[y][x2], G[y+py][x2]);
    }

    return true;
}

int main() {

    vector<string> grid;
    string line;
    vector<int> moves;
    bool parsing_grid = true;
    while (getline(cin, line)) {
        if (line.size() == 0) {
            parsing_grid = false;
            continue;
        }
        if (parsing_grid) {
            stringstream ss;
            for (char c : line) {
                switch(c) {
                    case '#': ss << "##"; break;
                    case 'O': ss << "[]"; break;
                    case '@': ss << "@."; break;
                    case '.': ss << ".."; break;
                }
            }
            grid.push_back(ss.str());
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
        auto [px, py] = movemap[move];
        // cout << move << " " << x << " " << y << endl;
        // cout << endl;
        if (do_move(grid, {x, y}, {px, py}, false)) {
            x += px;
            y += py;
        }
        // for (string g : grid) cout << g << endl;
    }

    uint64_t ans = 0;
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            // cout << grid[i][j];
            if (grid[i][j] == '[') {
                ans += 100*i + j;
            }
        }
        // cout << endl;
    }

    cout << ans << endl;

    return 0;
}
