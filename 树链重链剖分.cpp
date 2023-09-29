#include <bits/stdc++.h>

#define SIZE 100005

struct E
{
    int to, next;
} Edge[SIZE << 1];
int Head[SIZE];
int head_cnt;
void AddEdge(int u, int v)
{
    Edge[head_cnt].to = v;
    Edge[head_cnt].next = Head[u];
    Head[u] = head_cnt++;

    Edge[head_cnt].to = u;
    Edge[head_cnt].next = Head[v];
    Head[v] = head_cnt++;
}
struct Node
{
    int dfn; // depth first number
    int size;
    int val;
    int fa;
    int son;
    int depth; // 深度
    int top;
} node[SIZE];
int node_cnt;
int time;
int dfn_map[SIZE];

struct TreeNode
{
    int l, r;
    int val;
    int lazy;
} treenode[SIZE << 2];

void push_down(int idx)
{
    if (treenode[idx].lazy)
    {
        treenode[idx << 1].val += treenode[idx].lazy * (treenode[idx << 1].r - treenode[idx << 1].l + 1);
        treenode[idx << 1].lazy += treenode[idx].lazy;
        treenode[idx << 1 | 1].val += treenode[idx].lazy * (treenode[idx << 1 | 1].r - treenode[idx << 1 | 1].l + 1);
        treenode[idx << 1 | 1].lazy += treenode[idx].lazy;
        treenode[idx].lazy = 0;
    }
}

int query(int l, int r, int idx = 1)
{
    if (treenode[idx].l >= l && treenode[idx].r <= r)
    {
        return treenode[idx].val;
    }
    push_down(idx);
    int mid = l + ((r - l) >> 1);
    int ret = 0;
    if (l <= mid)
    {
        ret += query(l, mid, idx << 1);
    }
    if (r > mid)
    {
        ret += query(mid + 1, r, idx << 1 | 1);
    }
    return ret;
}

void update(int l, int r, int z, int idx = 1)
{
    if (treenode[idx].l >= l && treenode[idx].r <= r)
    {
        treenode[idx].val += z * (r - l + 1);
        treenode[idx].lazy = z;
        return;
    }
    push_down(idx);
    int mid = l + ((r - l) >> 1);
    if (l <= mid)
    {
        update(l, mid, z, idx << 1);
    }
    if (r > mid)
    {
        update(mid + 1, r, z, idx << 1 | 1);
    }
}

void build(int l, int r, int idx)
{
    if (l == r)
    {
        treenode[idx] = {l, r, node[l].val, 0};
        return;
    }
    int mid = l + ((r - l) >> 1);
    if (l <= mid)
    {
        build(l, mid, idx << 1);
    }
    if (r > mid)
    {
        build(mid + 1, r, idx << 1 | 1);
    }
    treenode[idx] = {l, r, treenode[idx << 1].val + treenode[idx << 1 | 1].val, 0};
}

void dfs1(int u, int f) // f是u的父亲
{
    node[u].fa = f;
    node[u].depth = node[f].depth + 1;
    node[u].size = 1;
    int maxsize = -1;
    for (int i = Head[u]; ~i; i = Edge[i].next)
    {
        int v = Edge[i].to;
        if (v == f)
        {
            continue;
        }
        dfs1(v, u);
        node[u].size += node[v].size;
        if (node[v].size > maxsize)
        {
            maxsize = node[v].size;
            node[u].son = v;
        }
    }
}

void dfs2(int u, int top)
{
    node[u].dfn = ++time;
    node[u].top = top;
    dfn_map[time] = node[u].val;

    if (!node[u].son)
    {
        return;
    }
    dfs2(node[u].son, top);
    for (int i = Head[u]; ~i; i = Edge[i].next)
    {
        int v = Edge[i].to;
        if (v == node[u].fa || v == node[u].son)
        {
            continue;
        }
        dfs2(v, v);
    }
}

void modify_tree(int x, int z) // 修改节点子树
{
    update(node[x].dfn, node[x].dfn + node[x].size - 1, z);
}

int query_tree(int x) // 查询节点子树
{
    return query(node[x].dfn, node[x].dfn + node[x].size - 1);
}

int main()
{
    std::fill(Head, Head + SIZE, -1);
    node_cnt = head_cnt = time = 0;
    return 0;
}