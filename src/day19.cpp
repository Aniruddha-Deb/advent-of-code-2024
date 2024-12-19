#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

int main() {

    vector<pair<int,int>> M;
    string line;
    getline(cin, line);
    line += ",";
    set<string> towels;
    size_t max_towel_len = 0;
    int prev = 0;
    for (size_t i=0; i<line.size(); i++) {
        if (line[i] == ',') {
            string towel = line.substr(prev, i-prev);
            prev = i+2;
            max_towel_len = max(towel.size(), max_towel_len);
            towels.insert(towel);
            i++;
            continue;
        }
    }

    getline(cin,line);
    vector<string> tgts;
    while (getline(cin, line)) {
        tgts.push_back(line);
    }

    int ans = 0;
    uint64_t ans_pt2 = 0;
    for (const string& tgt : tgts) {

        int n = tgt.size();
        vector<uint64_t> DP(n+1);
        DP[0] = 1;

        for (int i=1; i<=n; i++) {
            for (int j=i-1; j>=0; j--) {
                if (towels.contains(tgt.substr(j, i-j))) {
                    DP[i] += DP[j];
                }
            }
        }
        ans += (DP[n] > 0);
        ans_pt2 += DP[n];
    }

    cout << ans << endl;
    cout << ans_pt2 << endl;
    
    return 0;
}
