#include <cstdio>
#include <cstring>
#include <iostream>
#define MXN 1007
using namespace std;
int seq[MXN];
struct node {
    int dep, id;
    node *fa[11];
    node *c[2];
    node() { dep = id = 0; }
} nds[MXN];
int mxdep = 0;
void dfs(node *root, node *f) {
    if (!root || !(root - nds)) return;
    root->dep = f->dep + 1;
    mxdep = max(mxdep, root->dep);
    root->fa[0] = f;
    dfs(root->c[0], root);
    dfs(root->c[1], root);
}
bool ddfs(node *root) {
    if (mxdep == root->dep) {
        seq[root->dep] = root->id;
        return true;
    }
    if (ddfs(root->c[0])) {
        seq[root->dep] = root->id;
        return true;
    } else if (ddfs(root->c[1])) {
        seq[root->dep] = root->id;
        return true;
    }
    return false;
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
    ddfs(nds + 1);
    printf("The height of this tree is %d, following is a sequence of nodes\n", mxdep);
    for (int i = 1; i <= mxdep; ++i)
        printf("%d ", seq[i]);
    putchar('\n');
}
/**
d:\git-repos\data-structure-homework\06>g++ e16.cpp

d:\git-repos\data-structure-homework\06>a
7 2 3 4 5 6 7 0 0 0 0 0 0 0 0
The height of this tree is 3, following is a sequence of nodes
1 2 4

d:\git-repos\data-structure-homework\06>
*/