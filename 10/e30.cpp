#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;
struct node {
    int data;
    node *nxt;
} *hd, buffer[1007], *cur;
node *newnode(int data, node *xt) {
    cur->data = data;
    cur->nxt = xt;
    return cur++;
}
void init() {
    cur = buffer + 1;
    hd = buffer;
    hd->data = 0x7fffffff + 1;
    hd->nxt = NULL;
}
void insert(int data) {
    node *p = hd;
    for (; p->nxt && p->data <= data && p->nxt->data <= data; p = p->nxt);
    p->nxt = newnode(data, p->nxt);
}
int main() {
    init();
    int x;
    while (~scanf("%d", &x))
        insert(x);
    for (node *p = hd->nxt; p; p = p->nxt)
        printf("%d ", p->data);
}
/**
 root  …  git-repos  data-structure-homework  10  2  g++ e30.cpp -g
 root  …  git-repos  data-structure-homework  10  2  ./a.out    master 
23 14 3 53 52 3214 243 321 245 2 43 242 52
2 3 14 23 43 52 52 53 242 243 245 321 3214
 root  …  git-repos  data-structure-homework  10  2             master 
/*