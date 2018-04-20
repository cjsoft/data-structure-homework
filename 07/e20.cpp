#include <cstdio>
#include <cstring>
#include <vector>
#define MXN 107
using namespace std;
vector<int> v[MXN];
bool tag[MXN];
int n, m;
int x;
bool dfs(int root, int dep, int target, int k) {
    if (dep > k) return false;
    if (target == root && dep == k) return true;
    for (auto i : v[root]) {
        if (!tag[i]) {
            tag[i] = true;
            if (dfs(i, dep + 1, target, k))
                return true;
            tag[i] = false;
        }
    }
    return false;
}
int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        v[a].push_back(b);
        v[b].push_back(a);
    }
    int a, b, k;
    while (~scanf("%d %d %d", &a, &b, &k)) {
        memset(tag, 0, sizeof(tag));
        tag[a] = true;
        puts(dfs(a, 0, b, k) ? "YES" : "NO");
    }
}
