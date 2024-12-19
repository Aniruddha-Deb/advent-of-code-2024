#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <bitset>
#include <set>
#include <stack>

using namespace std;


struct cpu {
    uint64_t a, b, c;
    size_t ip;
    vector<uint64_t> mem;
    vector<uint64_t> output;

    uint64_t decode(uint64_t op) {
        switch(op) {
            case 0: case 1: case 2: case 3: return op;
            case 4: return a;
            case 5: return b;
            case 6: return c;
        }
        throw runtime_error("Invalid operand");
    }

    void adv(uint64_t op) {
        a = (a/(1<<decode(op)));
    }

    void bxl(uint64_t op) {
        b = b ^ op;
    }

    void bst(uint64_t op) {
        b = decode(op)%8;
    }

    bool jnz(uint64_t op) {
        if (ip == op) return false;
        if (a != 0) ip = op;
        return true;
    }

    void bxc(uint64_t op) {
        b = b ^ c;
    }

    void out(uint64_t op) {
        output.push_back(decode(op)%8);
    }

    void bdv(uint64_t op) {
        b = (a/(1<<decode(op)));
    }

    void cdv(uint64_t op) {
        c = (a/(1<<decode(op)));
    }

    bool tick() {
        if (ip > mem.size()) return false;

        auto instr = mem[ip];
        auto op = mem[ip+1];
        switch(instr) {
            case 0: adv(op); break;
            case 1: bxl(op); break;
            case 2: bst(op); break;
            case 3: return jnz(op); // can trap!
            case 4: bxc(op); break;
            case 5: out(op); cout << *output.rbegin() << "," << std::flush;
            case 6: bdv(op); break;
            case 7: cdv(op); break;
        }

        ip += 2;
        return true;
    }

    string op_str(int op) {
        switch(op) {
            case 0: case 1: case 2: case 3: return to_string(op);
            case 4: return "$A";
            case 5: return "$B";
            case 6: return "$C";
        }
        throw runtime_error("Unknown operand " + to_string(op));
    }

    void print_instr(int instr, int op) {

        switch (instr) {
            case 0: cout << "adv " << op_str(op) << endl; return;
            case 1: cout << "bxl " << op << endl; return;
            case 2: cout << "bst " << op_str(op) << endl; return;
            case 3: cout << "jnz " << op << endl; return;
            case 4: cout << "bxc " << endl; return;
            case 5: cout << "out " << op_str(op) << endl; return;
            case 6: cout << "bdv " << op_str(op) << endl; return;
            case 7: cout << "cdv " << op_str(op) << endl; return;
        }

    }

    void print_mem() {
        for (int i=0; i<mem.size(); i+=2) {
            print_instr(mem[i], mem[i+1]);
        }
    }

};

string output(uint64_t a) {
    uint64_t b,c;
    vector<char> v(128);
    int vptr = 0;
    stringstream ans;
    while (a != 0) {
        b = (a&7);
        b ^= 7; // b = ~b
        c = a >> b;
        b ^= 7; // b = (a&7)
        b ^= c; // b = ((a&7) ^ (a >> ~(a&7))) & 7
                // deterministic in 10 bits (1024 states)
        a >>= 3;

        v[vptr++] = (b&7) + '0';
        v[vptr++] = ',';
    }
    if (vptr == 0) return "";
    return string(v.begin(), v.begin()+vptr-1);
}

int main() {

    string s;
    cin >> s >> s >> s;
    int a = stoi(s);
    cin >> s >> s >> s;
    int b = stoi(s);
    cin >> s >> s >> s;
    int c = stoi(s);

    cin >> s; // newline
    cin >> s >> s; // mem
    vector<int> exp_mem;
    
    for (int i=0; i<s.size(); i+=2) {
        exp_mem.push_back(s[i]-'0');
    }

    // pt1
    cout << output(a) << endl;

    vector<int> mmap(1024);
    for (int i=0; i<(1<<10); i++) {
        mmap[i] = ((i&7) ^ (i >> ((i&7)^7))) & 7;
    }

    vector<int> ans_v;
    // starting set
    stack<tuple<uint64_t,int>> S;
    S.push({0,15});

    uint64_t ans = 1e18;
    while (!S.empty()) {
        auto [c,p] = S.top();
        S.pop();
        if (p < 0) {
            ans = min(ans, c);
            continue;
        }
        for (int i=0; i<8; i++) {
            uint64_t new_c = (c << 3) | i;
            if (mmap[new_c & 0x3FF] == exp_mem[p]) {
                S.push({new_c, p-1});
            }
        }
    }
    cout << ans << endl;

    return 0;
}
