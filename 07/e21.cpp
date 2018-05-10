#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <map>
#define MXN 1007
using namespace std;
set<vector<int>> sts;
vector<int> v[MXN];
int n, m;
int seq[MXN], loc[MXN];
char tag[MXN];
#define MREPMXN 1007
typedef int MREPTP;

MREPTP _SEQ[MREPMXN << 1 | 1];

int minrep(MREPTP a[], int n) {
    memset(_SEQ, 0, sizeof(_SEQ));
    memcpy(_SEQ, a, sizeof(MREPTP) * n);
    memcpy(_SEQ + n, _SEQ, sizeof(MREPTP) * n);
    int i = 0, j = 1, k;
    while (j < n) {
        k = 0;
        while (j + k < (n << 1) && _SEQ[i + k] == _SEQ[j + k]) ++k;
        if (j + k == (n << 1)) break;
        else if (_SEQ[i + k] > _SEQ[j + k]) {
            i = std::max(i + k + 1, j);
            j = i + 1;
        } else j += k + 1;
    }
    return i;
}

void dfs(int root, int dep) {
    if (tag[root] == 1) {
        vector<int> tmp;
        int x = minrep(seq + loc[root], dep - loc[root]);
        for (int i = loc[root] + x; i < dep; ++i)
            tmp.push_back(seq[i]);
        for (int i = loc[root]; i < loc[root] + x; ++i)
            tmp.push_back(seq[i]);
        sts.insert(tmp);
        return;
    }
    tag[root] = 1;
    seq[dep] = root;
    loc[root] = dep;
    for (auto i : v[root]) {
        dfs(i, dep + 1);
    }
    tag[root] = 2;
}
int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        v[a].push_back(b);
    }
    for (int i = 1; i <= n; ++i)
        if (tag[i] == 0)
            dfs(i, 0);
    printf("Found %d distinct simple cycles, expressed in their minimum representation:\n", sts.size());
    for (auto i : sts) {
        for (auto j : i)
            printf("%d ", j);
        putchar('\n');
    }
}
/**
 root  …  git-repos  data-structure-homework  07  g++ e21.cpp -std=c++11
 root  …  git-repos  data-structure-homework  07  ./a.out       master 
4 7
1 2
2 3
3 4
4 1
1 3
3 2
2 4
Found 5 distinct simple cycles, expressed in their minimum representation:
1 2 3 4
1 2 4
1 3 2 4
1 3 4
2 3
 root  …  git-repos  data-structure-homework  07  ./a.out       master 
7 11
5 6
5 7
7 6
6 2
7 4
2 4
2 3
4 1
1 2
3 1
4 3
Found 3 distinct simple cycles, expressed in their minimum representation:
1 2 3
1 2 4
1 2 4 3
 root  …  git-repos  data-structure-homework  07                master 
*/