#include <bits/stdc++.h>
using namespace std;

#define SIZE 100000
int fa[SIZE];
int find(int x)
{
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void merge(int x, int y)
{
    fa[find(x)] = find(y);
}

int main()
{
}