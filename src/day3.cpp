#include <iostream>
#include <vector>
#include <regex>

using namespace std;

int main() {

    vector<string> memory;
    string line;
    while (getline(cin, line)) {
        memory.push_back(line);
    }

    uint64_t ans = 0;
    regex pattern(R"(mul\(([0-9]+),([0-9]+)\))");
    auto accum = [&](string mem) {
        auto begin = sregex_iterator(mem.begin(), mem.end(), pattern);
        auto end = sregex_iterator();
        for (; begin != end; begin++) {
            auto match = *begin;
            ans += stoull(match[1]) * stoull(match[2]);
        }
    };

    for_each(memory.begin(), memory.end(), accum);

    cout << ans << endl;
        

    return 0;
}