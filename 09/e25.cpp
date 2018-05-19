#include <cstdio>
#include <cstring>
#include <iostream>
#define MXN 1007
using namespace std;
typedef int eletype;
struct node {
    int cnt;
    eletype data;
    node *prev, *nxt;
} buffer[MXN], *root, *tail, *tot;
node *newnode(eletype dta) {
    tot->cnt = 0;
    tot->data = dta;
    tot->prev = tot->nxt = NULL;
    return tot++;
}
void init() {
    root = tail = buffer;
    tot = buffer + 1;
    root->data = -1;
    root->cnt = 0x7fffffff;
    root->prev = root->nxt = NULL;
}
void adddata(eletype dta) {
    tail->nxt = newnode(dta);
    tail->nxt->prev = tail;
    tail = tail->nxt;
}
void pull(node *x) {
    node *ox = x->prev->prev, *oy = x->nxt, *oa = x->prev;
    if (ox) ox->nxt = x;
    x->prev = ox;
    x->nxt = oa;
    oa->prev = x;
    oa->nxt = oy;
    if (oy) oy->prev = oa;
    if (tail == x) tail = oa;
}
bool access(eletype data) {
    node *x;
    for (x = root->nxt; x; x = x->nxt) {
        if (x->data == data) {
            x->cnt++;
            while (x->prev->cnt < x->cnt) pull(x);
            return true;
        }
    }
    return false;
}
int main() {
    init();
    int n;
    int x;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &x);
        adddata(x);
    }
    puts("----------");
    while (~scanf("%d", &x)) {
        if (access(x)) {
            puts("Successful");
            for (node *x = root->nxt; x; x = x->nxt)
                printf("%d ", x->data);
            putchar('\n');
        } else {
            puts("Failed");
        }
    }
    return 0;
}
/**
 root  …  git-repos  data-structure-homework  09  g++ e25.cpp       master 
 root  …  git-repos  data-structure-homework  09  ./a.out           master 
5 1 2 3 4 5
----------
2
Successful
2 1 3 4 5
5
Successful
2 5 1 3 4
5
Successful
5 2 1 3 4
6
Failed
0
Failed
2
Successful
5 2 1 3 4
1
Successful
5 2 1 3 4
1
Successful
5 2 1 3 4
1
Successful
1 5 2 3 4
2
Successful
1 2 5 3 4
2
Successful
2 1 5 3 4
^Z
[1]  + 123 suspended  ./a.out
 root  …  git-repos  data-structure-homework  09  1  
*/