#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
char seq[107];
int sz, k;
int main() {
    scanf("%d", &k);
    scanf("%s", seq);
    sz = strlen(seq);
    reverse(seq, seq + sz);
    reverse(seq, seq + k % sz);
    reverse(seq + k % sz, seq + sz);
    puts(seq);
}
/**
d:\git-repos\data-structure-homework\05 (master -> origin)
λ g++ e10.cpp

d:\git-repos\data-structure-homework\05 (master -> origin)
λ a
3
asdfghjkl
jklasdfgh

d:\git-repos\data-structure-homework\05 (master -> origin)
λ
*/