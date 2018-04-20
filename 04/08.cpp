#include <cstdio>
#include <cstring>
#include <iostream>
#define BLOCKSIZE 107
#define LOWSIZE 20
using namespace std;

struct block {
    int sz;
    char seq[BLOCKSIZE];
    block *pre, *nxt;
    block() { sz = 0; memset(seq, 0, sizeof(seq)); pre = nxt = NULL; }
    void assign(char *p) {
        while (*p && sz < BLOCKSIZE)
            seq[sz++] = *p++;
        if (sz >= BLOCKSIZE && *p) {
            nxt = new block();
            nxt->pre = this;
            nxt->assign(p);
        }
    }
    void check() {
        if (nxt && nxt->sz < LOWSIZE && nxt->sz + sz <= BLOCKSIZE) {
            for (int i = 0; i < nxt->sz; ++i) seq[sz++] = nxt->seq[i];
            block *on = nxt;
            nxt->nxt->pre = this;
            nxt = nxt->nxt;
            delete nxt;
        }
    }
    void print() {
        for (int i = 0; i < sz; ++i) putchar(seq[i]);
        if (nxt) nxt->print();
    }
};

void split(block *a, int pos, block *&x, block *&y) {
    x = a;
    while (a->sz < pos + 1) {
        pos -= a->sz;
        a = a->nxt;
    }
    if (a->sz == pos + 1) {
        y = a->nxt;
        if (y) y->pre = NULL;
        a->nxt = NULL;
    }
    block *tmp = new block();
    for (int i = pos + 1; i < a->sz; ++i) tmp->seq[tmp->sz++] = a->seq[i];
    tmp->nxt = a->nxt;
    if (a->nxt) a->nxt->pre = tmp;
    a->sz = pos + 1;
    a->nxt = NULL;
    y = tmp;
}
void concat(block *a, block *b) {
    while (a->nxt) a = a->nxt;
    a->nxt = b;
    b->pre = a;
}
char s[1007];
block a, b, *c, *d;
int main() {
    cin.getline(s, 1007);
    a.assign(s);
    memset(s, 0, sizeof(s));
    cin.getline(s, 1007);
    b.assign(s);
    int x;
    scanf("%d", &x);
    split(&a, x, c, d);
    concat(c, &b);
    concat(c, d);
    c->print();
}
/**
:\git-repos\data-structure-homework\04 (master -> origin)
λ g++ 08.cpp

d:\git-repos\data-structure-homework\04 (master -> origin)
λ a
asdfghjkl
123
3
asdf123ghjkl
d:\git-repos\data-structure-homework\04 (master -> origin)
λ a
asfdgh
123
-1
123asfdgh
d:\git-repos\data-structure-homework\04 (master -> origin)
λ
*/