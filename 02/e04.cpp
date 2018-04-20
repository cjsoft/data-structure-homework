#include <iostream>
#include <map>
#include <stack>
#include <cstring>
using namespace std;
char p[256];
char input[1007];
map<char, char> mp({
    {')', '('},
    {']', '['},
    {'}', '{'}
});
stack<int> stk;
void check(char s[]) {
    int len = strlen(s);
    for (; !stk.empty(); stk.pop());
    for (int i = 0; i < len; ++i) if (p[s[i]]) {
        if (p[s[i]] > 1) stk.push(s[i]);
        else {
            if (stk.empty() || mp[s[i]] != stk.top()) {
                goto ILLE;
            } else stk.pop();
        }
    } else {
ILLE:;
        puts("Illegal Sequence!");
        puts(s);
        for (int j = 0; j < i; ++j) putchar(' ');
        putchar('^');
        return;
    }
    puts("Pairing test passed");
}
int main() {
    for (auto i : mp) {
        p[i.first] = p[i.second] = 1;
        p[i.second]++;
    }
    cin >> input;
    check(input);
}
/**
D:\git-repos\data-structure-homework\02 (master -> origin)
λ g++ e04.cpp -std=c++11

D:\git-repos\data-structure-homework\02 (master -> origin)
λ .\a.exe
}}}
Illegal Sequence!
}}}
^
D:\git-repos\data-structure-homework\02 (master -> origin)
λ .\a.exe
(){}[{()}([])]
Pairing test passed

D:\git-repos\data-structure-homework\02 (master -> origin)
λ .\a.exe
(){}[{()}([])}
Illegal Sequence!
(){}[{()}([])}
             ^
*/