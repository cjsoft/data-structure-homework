#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <map>
#define MXN 1007
using namespace std;
map<set<int>, vector<int>> sts;
vector<int> v[MXN];
int n, m;
int seq[MXN], loc[MXN];
char tag[MXN];
void dfs(int root, int dep) {
    if (tag[root] == 1) {
        set<int> tmp;
        vector<int> tp;
        for (int i = loc[root]; i < dep; ++i)
            tmp.insert(seq[i]), tp.push_back(seq[i]);
        if (sts.find(tmp) != sts.cend()) return;
        sts.insert(make_pair(tmp, tp));
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
    printf("Found %d distinct simple cycle:\n", sts.size());
    for (auto i : sts) {
        for (auto j : i.second)
            printf("%d ", j);
        putchar('\n');
    }
}
/**
 root  …  git-repos  data-structure-homework  07  g++ e21.cpp -std=c++11
 root  …  git-repos  data-structure-homework  07  ./a.out        master 
7
11
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
Found 3 distinct simple cycle:
1 2 3
1 2 4 3
1 2 4
 root  …  git-repos  data-structure-homework  07                 master 
*/