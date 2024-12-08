#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

int main() {

    string line;
    vector<string> grid;
    while (getline(cin, line)) {
        grid.push_back(line);
    }

    int n = grid.size();
    int m = grid[0].size();

    map<char, vector<pair<int,int>>> antennas;

    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if (grid[i][j] != '.') antennas[grid[i][j]].push_back({i, j});
        }
    }

    set<pair<int,int>> antinodes;

    for (const auto& [k, v] : antennas) {
        for (int i=0; i<v.size(); i++) {
            for (int j=i+1; j<v.size(); j++) {
                auto& [y1, x1] = v[i];
                auto& [y2, x2] = v[j];
                auto [yd, xd] = std::pair<int,int>{y2-y1, x2-x1};
                auto [yn1, xn1] = std::pair<int,int>{y1-yd, x1-xd};
                auto [yn2, xn2] = std::pair<int,int>{y2+yd, x2+xd};

                if (yn1 >= 0 and yn1 < n and xn1 >= 0 and xn1 < m) antinodes.insert({yn1, xn1});
                if (yn2 >= 0 and yn2 < n and xn2 >= 0 and xn2 < m) antinodes.insert({yn2, xn2});
            }
        }
    }

    cout << antinodes.size() << endl;

    return 0;
}
