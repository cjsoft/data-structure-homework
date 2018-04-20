#include <cstdio>
#include <cstring>
#include <iostream>
#define selbit(x, i) ((x) & (1 << (i)))
typedef unsigned long long ull;
using namespace std;
int n, t;
int w[65];
int main() {
    scanf("%d %d", &n, &t);
    for (int i = 0; i < n; ++i)
        scanf("%d", w + i);
    for (int i = 0; i < (1 << n); ++i) {
        int tmp = 0;
        for (int j = 0; j < n; ++j) if (selbit(i, j)) tmp += w[j];
        if (tmp == t) {
            puts("Solution found.");
            for (int j = 0; j < n; ++j) if (selbit(i, j)) {
                printf("Choose item %d, of which weight is %d.\n", j + 1, w[j]);
            }
            puts("\n--------------------------");
        }
    }
    return 0;
}
/**
d:\git-repos\data-structure-homework\02 (master -> origin)
λ g++ e03.cpp

d:\git-repos\data-structure-homework\02 (master -> origin)
λ a
5 10
1 2 3 4 5
Solution found.
Choose item 1, of which weight is 1.
Choose item 2, of which weight is 2.
Choose item 3, of which weight is 3.
Choose item 4, of which weight is 4.

--------------------------
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

d:\git-repos\data-structure-homework\02 (master -> origin)
λ
*/