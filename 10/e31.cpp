#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
int c[1007], a[1007], rag[1007];
int n;
int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        scanf("%d", a + i);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            if (a[j] < a[i]) ++c[i];
        }
    }
    for (int i = 0; i < n; ++i)
        rag[c[i]] = a[i];
    for (int i = 0; i < n; ++i)
        printf("%d ", rag[i]);
}
/**
 root  …  git-repos  data-structure-homework  10  g++ e31.cpp    master 
 root  …  git-repos  data-structure-homework  10  ./a.out        master 
5
43 23 12 3 65
3 12 23 43 65 #                                                               
 root  …  git-repos  data-structure-homework  10  ./a.out        master 
10
9 8 7 6 5 4 3 2 1 0
0 1 2 3 4 5 6 7 8 9 #                                                         
 root  …  git-repos  data-structure-homework  10                 master 
