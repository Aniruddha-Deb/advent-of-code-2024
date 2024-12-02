#include <iostream>
#include <sstream>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <ranges>
#include <vector>
#include <print>

using namespace std;

int main() {

    vector<vector<int>> reports;
    string line;
    while (getline(cin, line)) {
        auto ss = istringstream{line};
        auto r = views::istream<int>(ss) | ranges::to<vector<int>>() ;

        reports.push_back(r);
    }


    auto valid = [](const vector<int>& report) {
        if (is_sorted(report.begin(), report.end(), std::less<int>()) or 
            is_sorted(report.begin(), report.end(), std::greater<int>())) {
            vector<int> diffs;
            adjacent_difference(report.begin(), report.end(), back_inserter(diffs));
            if (all_of(diffs.begin()+1, diffs.end(), [](int diff) {
                return abs(diff) >= 1 and abs(diff) <= 3;
            })) {
                return true;
            }
        }
        return false;
    };

    vector<int> valid_reports;
    std::transform(reports.begin(), reports.end(), back_inserter(valid_reports), [&](const vector<int>& report) {

        if (valid(report)) return 1;

        for (int i=0; i<report.size(); i++) {
            auto new_report = report;
            new_report.erase(new_report.begin()+i);
            if (valid(new_report)) return 1;
        }

        return 0;
    });

    

    int ans = accumulate(valid_reports.begin(), valid_reports.end(), 0);

    cout << ans << endl;


    return 0;
}
