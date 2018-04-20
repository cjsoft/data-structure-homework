#include <cstdio>
#include <cstring>
#include <iostream>
#define MXN 1007
using namespace std;
template <typename T>
struct stk {
    T dta[MXN];
    int tot;
    stk() { memset(dta, 0, sizeof(dta)); tot = 0; }
    T push(T x) {
        if (tot >= MXN) throw 2;
        return dta[tot++] = x;
    }
    T pop() {
        if (tot <= 0) throw 1;
        return dta[--tot];
    }
    T top() {
        if (tot <= 0) throw 1;
        return dta[tot - 1];
    }
    int size() {
        return tot;
    }
    bool empty() {
        return tot <= 0;
    }
    bool full() {
        return tot >= MXN;
    }
};
template <typename T>
struct que {
    stk<T> a, b;
    int size() {
        return a.size() + b.size();
    }
    int full() {
        return a.size() + b.size() >= MXN;
    }
    bool empty() {
        return a.empty() && b.empty();
    }
    T push(T x) {
        try {
            for (; !b.empty(); a.push(b.pop()));
            return a.push(x);
        } catch(int e) {
            throw e;
        }
    }
    T front() {
        try {
            for (; !a.empty(); b.push(a.pop()));
            return b.top();
        } catch(int e) {
            throw e;
        }
    }
    T pop() {
        try {
            for (; !a.empty(); b.push(a.pop()));
            return b.pop();
        } catch(int e) {
            throw e;
        }
    }
};
que<int> q;

int main() {
    for (int i = 1; i < 20; ++i) {
        printf("pushing %d\n", i);
        q.push(i);
        if (i % 3 == 0) {
            printf("poping %d\n", q.pop());
        }
    }
    while (!q.empty()) {
        printf("poping %d\n", q.pop());
    }
}
/**
D:\git-repos\data-structure-homework\02 (master -> origin)
λ g++ e06.cpp

D:\git-repos\data-structure-homework\02 (master -> origin)
λ .\a.exe
pushing 1
pushing 2
pushing 3
poping 1
pushing 4
pushing 5
pushing 6
poping 2
pushing 7
pushing 8
pushing 9
poping 3
pushing 10
pushing 11
pushing 12
poping 4
pushing 13
pushing 14
pushing 15
poping 5
pushing 16
pushing 17
pushing 18
poping 6
pushing 19
poping 7
poping 8
poping 9
poping 10
poping 11
poping 12
poping 13
poping 14
poping 15
poping 16
poping 17
poping 18
poping 19

D:\git-repos\data-structure-homework\02 (master -> origin)
λ
*/