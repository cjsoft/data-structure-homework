#include <cstdio>
#include <cstring>
#include <iostream>
#define MXN 1007
using namespace std;
struct node {
    int id;
    node *c[2];
    node() { id = 0; }
} nds[MXN];
void dfs(node *root) {
    if (!root || !(root - nds)) return;
    putchar('(');
    dfs(root->c[0]);
    printf("%d", root->id);
    dfs(root->c[1]);
    putchar(')');
}

int n;
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        int a, b;
        nds[i].id = i;
        scanf("%d %d", &a, &b);
        nds[i].c[0] = nds + a;
        nds[i].c[1] = nds + b;
    }
    dfs(nds + 1);
}
/**
d:\git-repos\data-structure-homework\06>g++ e17.cpp

d:\git-repos\data-structure-homework\06>a
7 2 3 4 5 6 7 0 0 0 0 0 0 0 0
(((4)2(5))1((6)3(7)))
d:\git-repos\data-structure-homework\06>
*/