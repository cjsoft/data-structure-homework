#include <cstdio>
#include <cstring>
#include <cctype>
#define MXN 1007
using namespace std;
struct node {
    char dta;
    node *c[2];
} buffer[MXN], *tot;
int pri[256];
node *read() {
    char ch;
RD:;
    for (ch = getchar(); !pri[ch]; ch = getchar());
    if (ch == '#') return NULL;
    if (pri[ch] == 1) {
        node *cur = tot++;
        cur->dta = ch;
        cur->c[0] = cur->c[1] = NULL;
        for (ch = getchar(); !pri[ch]; ch = getchar());
        if (ch == '(') {
            cur->c[0] = read();
            cur->c[1] = read();
        }
        return cur;
    }
    if (ch == ',' || ch == ')')
        goto RD;
}
void dfs(node *root) {
    if (!root) return;
    printf("%c", root->dta);
    dfs(root->c[0]);
    dfs(root->c[1]);
}
int main() {
    tot = buffer;
    for (int i = 'A'; i <= 'Z'; ++i) 
        pri[i] = 1;
    pri['('] = pri[')'] = pri[','] = 2;
    pri['#'] = -1;
    dfs(read());
}
/**
d:\git-repos\data-structure-homework\06>g++ e18.cpp

d:\git-repos\data-structure-homework\06>a
A(B(C,#),D(E,F))
ABCDEF
d:\git-repos\data-structure-homework\06>
*/