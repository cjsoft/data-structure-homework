#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>
typedef std::chrono::high_resolution_clock Clock;
using namespace std;

namespace Qsort {
    int tarr[27];
    void partion_sort(int seq[], int l, int r) { // 每次选择区间右端点作为参照
        if (l >= r) return;
        int p = r; // 定基准
        int tl = l, tr = r;
        while (tl < tr) {
            while (tl < tr && seq[tl] < seq[p]) ++tl;
            while (tl < tr && seq[tr] >= seq[p]) --tr;
            swap(seq[tl], seq[tr]);
        }
        swap(seq[p], seq[tl]);
        partion_sort(seq, l, tl - 1);
        partion_sort(seq, tl + 1, r);
    }
    void tripivot_sort(int seq[], int l, int r) { // 枢轴三者取中方法，序列长度低于20直接插排
        if (l >= r) return;
        if (r - l < 20) { // 插排部分
            memset(tarr, 0x7f, sizeof(tarr));
            for (int i = l, j = 0; i <= r; ++i) {
                for (j = 0; j < i - l; ++j) {
                    if (tarr[j] >= seq[i]) break;
                }
                for (int t = i - l; t > j; --t)
                    tarr[t] = tarr[t - 1];
                tarr[j] = seq[i];
            }
            for (int i = l; i <= r; ++i)
                seq[i] = tarr[i - l];
        } else { // 先找中值
            int M = l, m = l;
            if (seq[r] < seq[m]) m = r;
            if (seq[(l + r) >> 1] < seq[m]) m = (l + r) >> 1;
            if (seq[r] > seq[M]) M = r;
            if (seq[(l + r) >> 1] > seq[M]) M = (l + r) >> 1;
            int p = (l + r) >> 1;
            if (m != l && M != l) p = l;
            if (m != r && M != r) p = r;
            swap(seq[p], seq[r]);
            p = r;
            int tl = l, tr = r;
            while (tl < tr) {
                while (tl < tr && seq[tl] < seq[p]) ++tl;
                while (tl < tr && seq[tr] >= seq[p]) --tr;
                swap(seq[tl], seq[tr]);
            }
            swap(seq[p], seq[tl]);
            tripivot_sort(seq, l, tl - 1);
            tripivot_sort(seq, tl + 1, r);
        }
    }
}
int tmp[2][100007];
int main() {
    int n, seed;
    scanf("%d %d", &n, &seed);
    srand(seed);
    for (int i = 0; i < n; ++i)
        tmp[0][i] = tmp[1][i] = rand();
    auto t1 = Clock::now();
    decltype(t1) t2, t3;
    Qsort::partion_sort(tmp[0], 0, n - 1); // 测量随机序列
    t2 = Clock::now();
    Qsort::tripivot_sort(tmp[1], 0, n - 1);
    t3 = Clock::now();
    printf("Normal qsort costs :%ld ns\nTripivot sort costs :%ld ns\n", chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count(), chrono::duration_cast<std::chrono::nanoseconds>(t3 - t2).count());
    reverse(tmp[0], tmp[0] + n);
    reverse(tmp[1], tmp[1] + n);
    t1 = Clock::now();
    Qsort::partion_sort(tmp[0], 0, n - 1); // 测量递减序列
    t2 = Clock::now();
    Qsort::tripivot_sort(tmp[1], 0, n - 1);
    t3 = Clock::now();
    printf("Normal qsort costs(decreasing sequence) :%ld ns\nTripivot sort costs(decreasing sequence) :%ld ns\n", chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count(), chrono::duration_cast<std::chrono::nanoseconds>(t3 - t2).count());
}