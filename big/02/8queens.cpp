#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

namespace eight_queens {
    const int MXN = 31;
    bool x[MXN], y[MXN], v[MXN];
    int seq[MXN];
    int cnt;
    void dfs(int pos) {
        if (pos == 8) { // 得到一组合法序列，输出并计数
            for (int i = 1; i <= 8; ++i) {
                printf("%d ", seq[i]);
            }
            ++cnt;
            putchar('\n');
            return;
        }
        for (int i = 1; i <= 8; ++i) {
            if (!v[i] && !x[i - pos + 8] && !y[i + pos]) { // 当前位置纵列、反斜行、斜行是否已经有元素
                v[i] = 1, x[i - pos + 8] = 1, y[i + pos] = 1; // 打上标记
                seq[pos + 1] = i;
                dfs(pos + 1); // 下个位置
                v[i] = 0, x[i - pos + 8] = 0, y[i + pos] = 0; // 回退标记
            }
        }
    }
    void solve() {
        cnt = 0;
        memset(seq, 0, sizeof(seq)); // 初始化各种数组
        memset(x, 0, sizeof(x));
        memset(y, 0, sizeof(y));
        memset(v, 0, sizeof(v));
        dfs(0);
        printf("%d\n", cnt);
    }
};

int main() {
    eight_queens::solve();
}