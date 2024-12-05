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

    int m = grid.size();
    int n = grid[0].size();
    cout << m << " " << n << endl;

    int ans = 0;
    // lengthwise
    for (int i=0; i<m; i++) {
        for (int j=0; j<n-3; j++) {
            string cdt = grid[i].substr(j, 4);
            ans += (cdt == "XMAS" or cdt == "SAMX");
        }
    }
    for (int j=0; j<n; j++) {
        for (int i=0; i<m-3; i++) {
            string cdt{grid[i][j], grid[i+1][j], grid[i+2][j], grid[i+3][j]};
            ans += (cdt == "XMAS" or cdt == "SAMX");
        }
    }
    for (int i=0; i<m-3; i++) {
        for (int j=0; j<n-3; j++) {
            string cdt{grid[i][j], grid[i+1][j+1], grid[i+2][j+2], grid[i+3][j+3]};
            ans += (cdt == "XMAS" or cdt == "SAMX");
        }
    }
    for (int i=0; i<m-3; i++) {
        for (int j=3; j<n; j++) {
            string cdt{grid[i][j], grid[i+1][j-1], grid[i+2][j-2], grid[i+3][j-3]};
            ans += (cdt == "XMAS" or cdt == "SAMX");
        }
    }

    cout << ans << endl;
            
    return 0;
}
