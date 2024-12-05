#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <regex>
#include <ranges>
#include <sstream>

using namespace std;

int main() {

    vector<string> grid;
    string line;
    regex re(R"(([0-9]+)\|([0-9]+))");
    bool parsing_flows = true;
    map<int,set<int>> after;
    map<int,set<int>> before;
    vector<vector<int>> pages;
    while (getline(cin, line)) {
        if (line == "") {
            parsing_flows = false;
            continue;
        }
        if (parsing_flows) {
            smatch m;
            regex_match(line, m, re);
            int from = stoi(m[1]);
            int to = stoi(m[2]);
            after[from].insert(to);
            before[to].insert(from);
        }
        else {
            stringstream in(line);
            string num;
            vector<int> p;
            while (getline(in, num, ',')) {
                p.push_back(stoi(num));
            }
            pages.push_back(p);
        }
    }

    int ans = 0;
    for (const auto& v : pages) {
        bool valid = true; 
        for (int i=0; i<v.size(); i++) {
            vector<int> v_back;
            vector<int> v_front;
            set_intersection(v.begin(), v.begin()+i, after[v[i]].begin(), after[v[i]].end(), back_inserter(v_back));
            set_intersection(v.begin()+i+1, v.end(), before[v[i]].begin(), before[v[i]].end(), back_inserter(v_front));
            valid = (valid and v_back.size() == 0 and v_front.size() == 0);
            if (!valid) break;
        }
        if (valid) {
            ans += v[v.size()/2];
        }
    }

    cout << ans << endl;

    return 0;
}
