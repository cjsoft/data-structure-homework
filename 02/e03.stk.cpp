#include <cstdio>
#include <cstring>
#include <iostream>
int seq[63];
int w[63];
int n, t;
void dfs(int pos, int sum) {
    if (sum > t) return;
    if (pos == n) {
        if (sum == t) {
            puts("Solution found.");
            for (int i = 0; i < n; ++i) if (seq[i]) {
                printf("Choose item %d, of which weight is %d.\n", i + 1, w[i]);
            }
            puts("\n--------------------------");
        }
        return;
    }
    seq[pos] = 0;
    dfs(pos + 1, sum);
    seq[pos] = 1;
    dfs(pos + 1, sum + w[pos]);
}
int main() {
    scanf("%d %d", &n, &t);
    for (int i = 0; i < n; ++i) scanf("%d", w + i);
    dfs(0, 0);
}
/**
d:\git-repos\data-structure-homework\02 (master -> origin)
λ g++ e03.stk.cpp

d:\git-repos\data-structure-homework\02 (master -> origin)
λ a
5 10
1 2 3 4 5
Solution found.
Choose item 2, of which weight is 2.
Choose item 3, of which weight is 3.
Choose item 5, of which weight is 5.

--------------------------
Solution found.
Choose item 1, of which weight is 1.
Choose item 4, of which weight is 4.
Choose item 5, of which weight is 5.

--------------------------
Solution found.
Choose item 1, of which weight is 1.
Choose item 2, of which weight is 2.
Choose item 3, of which weight is 3.
Choose item 4, of which weight is 4.

--------------------------

d:\git-repos\data-structure-homework\02 (master -> origin)
λ
*/