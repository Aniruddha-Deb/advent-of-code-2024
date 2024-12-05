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
    for (int i=0; i<m-2; i++) {
        for (int j=0; j<n-2; j++) {
            string cdt{grid[i][j], grid[i][j+2], grid[i+1][j+1], grid[i+2][j], grid[i+2][j+2]};
            ans += (cdt == "MMASS" or cdt == "MSAMS" or cdt == "SMASM" or cdt == "SSAMM");
        }
    }

    cout << ans << endl;
            
    return 0;
}
