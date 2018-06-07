#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <cassert>
#include <queue>

using namespace std;
namespace bintree_questions {
    const int MXN = 1007;
    struct node { // 节点类型
        node *c[2], *p;
        int id;
    } buffer[MXN], *cur, *root;
    queue<node*> q; // 层次遍历（bfs）所用的队列
    void init() { // 初始化
        memset(buffer, 0, sizeof(buffer));
        cur = buffer;
        root = 0;
    }
    node *newnode(int id, node *p) { // 结点分配函数
        cur->id = id;
        cur->p = p;
        cur->c[0] = cur->c[1] = 0;
        return cur++;
    }
    node *parsesequence(node *p, int seqa[], int seqb[], int la, int ra, int lb, int rb) { // 解析序列并建立树，返回值为被解析的序列所对应的树的根节点
        if (la > ra || lb > rb) return 0;
        node *tmp = newnode(seqa[la], p);
        int pp;
        for (pp = lb; seqb[pp] != seqa[la] && pp <= rb; ++pp);
        assert(pp <= rb);
        tmp->c[0] = parsesequence(tmp, seqa, seqb, la + 1, la + pp - lb, lb, pp - 1);
        tmp->c[1] = parsesequence(tmp, seqa, seqb, la + pp - lb + 1, ra, pp + 1, rb);
        return tmp;
    }
    void analyze(int n, int a[], int b[]) { // 套了个壳
        init();
        root = parsesequence(0, a, b, 0, n - 1, 0, n - 1);
    }
    void houxu(node *x) { // 后序遍历
        if (!x) return;
        houxu(x->c[0]);
        houxu(x->c[1]);
        printf("%d ", x->id);
    }
    void cengci(node *x) { // 层次遍历
        q.push(x);
        while (!q.empty()) {
            printf("%d ", q.front()->id);
            if (q.front()->c[0]) q.push(q.front()->c[0]);
            if (q.front()->c[1]) q.push(q.front()->c[1]);
            q.pop();
        }
    }
    int seq[MXN], mxdep;
    bool dfss(node *x, int id, int dep) { // dfs待搜索的点
        if (x->id == id) {
            mxdep = dep;
            seq[dep] = id;
            return true;
        }
        if (x->c[0] && dfss(x->c[0], id, dep + 1) || x->c[1] && dfss(x->c[1], id, dep + 1)) {
            seq[dep] = x->id;
            return true;
        } else {
            return false;
        }
    }
    void search(int id) { // 套了个壳
        if (dfss(root, id, 0)) {
            printf("Path to %d found: ", id);
            for (int i = 0; i <= mxdep; ++i) {
                printf("%d ", seq[i]);
            }
        } else {
            printf("No path to %d is found", id);
        }
    }
};
int n;
int a[1007], b[1007];
int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        scanf("%d", a + i);
    for (int i = 0; i < n; ++i)
        scanf("%d", b + i);
    bintree_questions::analyze(n, a, b);
    puts("Hou Xu");
    bintree_questions::houxu(bintree_questions::root);
    putchar('\n');
    puts("Ceng Ci Bian Li");
    bintree_questions::cengci(bintree_questions::root);
    putchar('\n');
    int x;
    while (~scanf("%d", &x)) {
        bintree_questions::search(x);
        putchar('\n');
    }
}