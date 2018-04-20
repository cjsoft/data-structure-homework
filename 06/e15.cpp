#include <cstdio>
#include <cstring>
#include <iostream>
#define MXN 1007
using namespace std;

struct node {
    int dep, id;
    node *fa[11];
    node *c[2];
    node() { dep = id = 0; }
} nds[MXN];
void dfs(node *root, node *f) {
    if (!root || !(root - nds)) return;
    root->dep = f->dep + 1;
    root->fa[0] = f;
    dfs(root->c[0], root);
    dfs(root->c[1], root);
}
node *lca(node *x, node *y) {
    if (x->dep > y->dep) swap(x, y);
    for (int d = y->dep - x->dep, i = 0; d; ++i, d >>= 1)
        if (d & 1)
            y = y->fa[i];
    if (x == y) return x;
    for (int i = 10; i >= 0; --i)
        if (x->fa[i] != y->fa[i])
            x = x->fa[i], y = y->fa[i];
    return x->fa[0];
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
    nds[0].fa[0] = nds;
    dfs(nds + 1, nds);
    for (int j = 1; j < 11; ++j) {
        for (int i = 0; i <= n; ++i) {
            nds[i].fa[j] = nds[i].fa[j - 1]->fa[j - 1];
        }
    }
    int a, b;
    while (~scanf("%d %d", &a, &b)) {
        printf("The LCA is %d\n", lca(nds + a, nds + b)->id);
    }
}
/**
d:\git-repos\data-structure-homework\06>g++ e15.cpp

d:\git-repos\data-structure-homework\06>a
7 2 3 4 5 6 7 0 0 0 0 0 0 0 0
1 2
The LCA is 1
1 3
The LCA is 1
4 5
The LCA is 2
4 6
The LCA is 1
5 7
The LCA is 1
2 6
The LCA is 1
^Z

d:\git-repos\data-structure-homework\06>
*/