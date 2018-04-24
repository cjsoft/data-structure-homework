/**--------------------
 * Prim Spanning Tree Algorithm
 *
 * Time Consumption: E \times \log{V}
 * Mem Consumption: linear
 * Author: cjsoft
 * Date: 2018/01/27
 * --------------------
 */
#include <queue>
#include <vector>
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define EMXN 10007
#define VMXN 107
#define E eglist
#define iterate(NODEN, _I) for (int _I = ehead[NODEN]; _I != -1; _I = eglist[_I].prev)
struct edge {
    int prev, v, w;
    edge(): prev(-1), v(0), w(0) {}
} eglist[EMXN];
int ehead[VMXN], ecur;
inline void einit() {
    ecur = 0;
    eglist[0] = edge();
    for (int i = 1; i < EMXN; ++i)
        eglist[i] = eglist[i - 1];
    for (int i = 0; i < VMXN; ++i)
        ehead[i] = -1;
}
inline void addedge(int u, int v, int w) {
    E[ecur].v = v;
    E[ecur].w = w;
    E[ecur].prev = ehead[u];
    ehead[u] = ecur++;
}
struct PII {
    int v, dis;
    PII(): v(0), dis(0) {}
    PII(int v, int dis): v(v), dis(dis) {}
    bool operator<(const PII &b) const {
        if (dis == b.dis) return v < b.v;
        return dis > b.dis;
    }
};
int G[107][107], n;
priority_queue<PII> npq;
char vis[VMXN];
int dis[VMXN];
int prim(int s) {
    int ans = 0;
    while (!npq.empty()) npq.pop();
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    dis[s] = 0;
    npq.push(PII(s, 0));
    PII tmp;
    while (!npq.empty()) {
        tmp = npq.top(), npq.pop();
        if (vis[tmp.v] || tmp.dis > dis[tmp.v]) continue;
        vis[tmp.v] = 1;
        ans += dis[tmp.v];
        for (int i = 1; i <= n; ++i) {
            if (dis[i] > G[tmp.v][i]) {
                dis[i] =  G[tmp.v][i];
                npq.push(PII(i, dis[i]));
            }
        }
    }
    return ans;
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            scanf("%d", &G[i][j]);
        }
    }
    printf("%d\n", prim(1));
}
/**
 root  …  git-repos  data-structure-homework  07  g++ e22.prim.cpp
 root  …  git-repos  data-structure-homework  07  ./a.out        master 
4
0 4 9 21
4 0 8 17
9 8 0 16
21 17 16 0
28
 root  …  git-repos  data-structure-homework  07                 master 
*/