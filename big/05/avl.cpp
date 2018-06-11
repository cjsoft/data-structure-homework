#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
namespace avl { // 可以重构为class，以编在一个程序中使用多棵AVL树
    const int MXN = 100007;
    struct node { // 节点结构
        node *p, *c[2];
        int sz, mxdep; // 子树大小，最大深度
        int key; // 键值
    } buffer[MXN], *root, *cur, *nil, _nil; // root表示根节点，nil为一个空节点
    bool isrson(node *x) { // 右儿子判定函数，用于生成标识d与dd
        return x->p->c[1] == x;
    }
    node *newnode(node *p, int key) { // 节点分配，p为父结点指针
        cur->sz = cur->mxdep = 1;
        cur->key = key;
        cur->p = p;
        cur->c[0] = cur->c[1] = nil;
        return cur++;
    }
    void update(node *x) { // 更新上传节点信息
        x->mxdep = max(x->c[0]->mxdep, x->c[1]->mxdep) + 1;
        x->sz = x->c[0]->sz + x->c[1]->sz + 1;
    }
    void init() { // 在使用前必须进行初始化
        nil = &_nil; // nil节点初始化
        nil->c[0] = nil->c[1] = nil->p = nil;
        nil->sz = nil->mxdep = nil->key = 0;
        cur = buffer;
    }
    node* access(int key) { // 查询[插入]键值为key的节点
        if (root == NULL) { // 如果整棵树为空，则分配一个节点键值为key，作为树根
            root = newnode(nil, key);
            return root;
        }
        node *p = root, *rtn;
        int dir = key > p->key;
        while (p->key != key) { // 找到合适的位置
            if (p->c[dir] == nil) {
                p->c[dir] = newnode(p, key);
                rtn = p->c[dir];
            } else {
                p = p->c[dir]; // 继续向下找
                dir = key > p->key;
            }
        }
        if (p->key == key) return p; // 如果已经有键值为key的元素，则返回该节点键值
        node *lp = p->c[dir], *llp; // p当前节点，lp儿子，llp孙子
        for (update(p); p != nil; llp = lp, lp = p, p = p->p, update(p)) { // 向上回溯
            int alp = p->c[0]->mxdep - p->c[1]->mxdep;
            if (alp <= -2 || alp >= 2) { // 如果平衡因子绝对值达到2
                node *pp = p->p;
                int dd = isrson(p), d = isrson(lp);
                if (!isrson(llp)) { // LL RR
                    p->c[d] = lp->c[d ^ 1];
                    if (p->c[d] != nil) p->c[d]->p = p;
                    lp->c[d ^ 1] = p;
                    p->p = lp;
                    if (pp == nil) root = lp;
                    else pp->c[dd] = lp;
                } else { // LR RL
                    lp->c[d ^ 1] = llp->c[d];
                    p->c[d] = llp->c[d ^ 1];
                    if (lp->c[d ^ 1] != nil) lp->c[d ^ 1]->p = lp;
                    if (p->c[d] != nil) p->c[d]->p = p;
                    if (pp == nil) root = llp;
                    else pp->c[dd] = llp;
                    update(lp);
                }
                break; // 调整一次即可
            }
        }
        return rtn; // 返回键值为key节点指针
    }
    void pdfs(node *x) { // 逆中序遍历
        if (x == nil) return;
        putchar('(');
        pdfs(x->c[1]);
        printf("%d", x->key);
        pdfs(x->c[0]);
        putchar(')');
    }
};
int main() {
    avl::init();
    int x;
    while (~scanf("%d", &x)) { // 读一个树，查/插一个数
        avl::access(x);
        avl::pdfs(avl::root);
        putchar('\n');
    }
}