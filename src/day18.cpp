#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

int main() {

    vector<pair<int,int>> M;
    string line;
    while (getline(cin, line)) {
        int s = line.find(",");
        int x = stoi(line.substr(0,s));
        int y = stoi(line.substr(s+1));
        M.push_back({x, y});
    }

    int n = 71;
    vector<string> G;
    string s(n, '.');
    for (int i=0; i<n; i++) {
        G.push_back(s);
    }

    for (int i=0; i<1024; i++) {
        auto [x, y] = M[i];
        G[y][x] = '#';
    }

    queue<pair<int,pair<int,int>>> Q;
    vector<vector<bool>> visited(n, vector<bool>(n, false));
    array<pair<int,int>,4> move{{
        {0, -1}, // up
        {1,  0}, // right
        {0,  1}, // down 
        {-1, 0}  // left
    }};
    Q.push({0, {0, 0}});
    visited[0][0] = true;
    while (!Q.empty()) {
        auto [d, p] = Q.front();
        auto [x, y] = p;
        Q.pop();

        if (x == n-1 and y == n-1) {
            cout << d << endl;
            break;
        }

        for (auto [px, py] : move) {
            int nx=x+px, ny=y+py;
            if (nx >= 0 and nx < n and ny >= 0 and ny < n and !visited[ny][nx] and G[ny][nx] == '.') {
                Q.push({d+1, {nx, ny}});
                visited[ny][nx] = true;
            }
        }
    }

    
    return 0;
}
