#include <iostream>
#include <string>
#include <map>
#include <set>
using namespace std;
bool equal(const string &a, const string &b) {
    return a == b;
}
int len(const string &a) {
    return a.length();
}
string sub(const string &a, int st, int len) {
    return a.substr(st, len);
}
string concat(const string &a, const string &b) {
    return a + b;
}
string x, y, r;
map<char, int> mpx;
set<char> sty;
int main() {
    getline(cin, x);
    getline(cin, y);
    for (auto i : y) {
        sty.insert(i);
    }
    for (auto i = x.cbegin(); i != x.cend(); i++) {
        if (!mpx.count(*i))
            mpx[*i] = distance(x.cbegin(), i);
        if (!sty.count(*i)) r += *i;
    }
    for (auto i : r) {
        cout << i << '\t';
    }
    cout << endl;
    for (auto i : r) {
        cout << mpx[i] << '\t';
    }
    cout << endl;
}
/**
d:\git-repos\data-structure-homework\04 (master -> origin)
λ g++ 07.cpp -std=c++11 -g

d:\git-repos\data-structure-homework\04 (master -> origin)
λ a
c:\mingw\lib\gcc\mingw32\5.3.0\include\c++\bits\basic_string.h:391:7: note:   no known conversion for argument 1 from 'const char' to 'const std::allocator<char>&'
c:\mingw\lib\gcc\mingw32\5.3.0\include\c++\bits\basic_string.h:380:7: note: candidate: std::__cxx11::basic_string<_CharT, _Traits, _Alloc>::basic_string() [with _CharT = char; _Traits = std::char_traits<char>; _Alloc = std::allocator<char>]
9       k       v       f       f       '       '       '       &       '
64      81      90      98      98      118     118     118     161     118

d:\git-repos\data-structure-homework\04 (master -> origin)
λ
*/