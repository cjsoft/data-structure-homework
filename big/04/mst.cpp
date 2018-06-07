#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;
namespace mst {
    const int MXN = 107;
    int n;
    int mp[MXN][MXN];
    int dis[MXN];
    struct cmp { bool operator()(const pair<int, int> &a, const pair<int, int> &b) { return a > b; } };
    priority_queue<pair<int, int>, vector<pair<int, int> >, cmp> pq;
    struct edge { // 边类型，用于kruskal算法和去边法
        int w, u, v;
        bool operator<(const edge &b) const {
            if (w == b.w) {
                if (u == b.u) {
                    return v < b.v;
                }
                return u < b.u;
            }
            return w < b.w;
        }
    } buf[MXN * MXN | 7];
    int tot = 0;
    int fa[MXN];
    int getfa(int x) { // 并查集，用于判断连通性
        return x == fa[x] ? x : fa[x] = getfa(fa[x]);
    }
    bool check(int x, int y) {
        return getfa(x) == getfa(y);
    }
    void uni(int x, int y) {
        fa[getfa(x)] = getfa(y);
    }
    int load(int n_) { // 从标准输入读取邻接矩阵
        n = n_;
        memset(mp, 0x3f, sizeof(mp));
        memset(dis, 0x3f, sizeof(dis));
        for (int i = 0; i < MXN; ++i)
            fa[i] = i;
        tot = 0;
        for (int i = 1; i <= n_; ++i) {
            for (int j = 1; j <= n_; ++j) {
                scanf("%d", &mp[i][j]);
                if (mp[i][j] != -1 && i > j) {
                    buf[tot++] = edge({mp[i][j], i, j});
                } else if (mp[i][j] == -1 && i != j) {
                    mp[i][j] = 0x3f3f3f3f;
                }
            }
        }
    }
    vector<edge> kru() { // kruskal算法
        vector<edge> rtn;
        for (int i = 0; i < n; ++i)
            fa[i] = i;
        sort(buf, buf + tot);
        for (int i = 0, z = 1; i < tot, z < n; ++i) {
            if (!check(buf[i].u, buf[i].v)) {
                rtn.push_back(buf[i]);
                uni(buf[i].u, buf[i].v);
                ++z;
            }
        }
        return rtn;
    }
    vector<int> prim() { // 堆优prim算法
        vector<int> rtn; // 最后一个存的是mst大小
        while (!pq.empty()) pq.pop();
        memset(dis, 0x3f, sizeof(dis));
        dis[1] = 0;
        pq.push(make_pair(0, 1));
        int ans = 0;
        while (!pq.empty()) {
            pair<int, int> tmp = pq.top();
            pq.pop();
            if (tmp.first <= dis[tmp.second]) {
                rtn.push_back(tmp.second);
                ans += dis[tmp.second];
                for (int i = 1; i <= n; ++i) {
                    if (i == tmp.second) continue;
                    if (mp[tmp.second][i] < dis[i]) {
                        dis[i] = mp[tmp.second][i];
                        pq.push(make_pair(dis[i], i));
                    }
                }
            }
        }
        rtn.push_back(ans);
        return rtn;
    }
    bool tag[MXN];
    vector<edge> qubianfa() { // 去边法
        vector<edge> rtn;
        memset(tag, 0xff, sizeof(tag));
        sort(buf, buf + tot);
        int ans = 0;
        for (int i = tot - 1; i >= 0; --i) {
            for (int j = 0; j < MXN; ++j) {
                fa[j] = j;
            }
            tag[i] = false;
            for (int j = 0; j < tot; ++j) {
                if (tag[j])
                    uni(buf[j].u, buf[j].v);
            }
            if (!check(buf[i].u, buf[i].v)) {
                tag[i] = true;
                rtn.push_back(buf[i]);
                ans += buf[i].w;
            }
        }
        return rtn;
    }
};
using namespace mst;
int main() { // 读入数据
    int n;
    scanf("%d", &n);
    mst::load(n);
    auto x = mst::kru();
    auto y = mst::prim();
    auto z = mst::qubianfa();
    int ans = 0;
    puts("Kruskal");
    for (auto i : x) {
        ans += i.w;
        printf("%d<-%d->%d\n", i.u, i.w, i.v);
    }
    printf("sum=%d\n", ans);
    puts("Prim");
    for (auto i = y.begin(); i != y.cend() - 1; ++i) {
        printf("%d ", *i);
    }
    printf("\nsum=%d\n", *(y.cend() - 1));
    puts("Qu Bian Fa");
    ans = 0;
    for (auto i : z) {
        ans += i.w;
        printf("%d<-%d->%d\n", i.u, i.w, i.v);
    }
    printf("sum=%d\n", ans);
}