#include <bits/stdc++.h>
#define TREE_SIZE 300005

struct node
{
    int left;
    int right;
    int val;
    int lazy;
} tree[TREE_SIZE << 2];

std::vector<int> arr = {1, 2, 3, 4, 5};

void push_down(int idx)
{
    if (tree[idx].lazy)
    {
        tree[idx << 1].val += (tree[idx << 1].right - tree[idx << 1].left + 1) * tree[idx].lazy;
        tree[idx << 1].lazy += tree[idx].lazy;
        tree[idx << 1 | 1].val += (tree[idx << 1 | 1].right - tree[idx << 1 | 1].left + 1) * tree[idx].lazy;
        tree[idx << 1 | 1].lazy += tree[idx].lazy;
        tree[idx].lazy = 0;
    }
}

/**
 *  @brief query区间
 *  @param  l   区间最左
 *  @param  r   区间最右
 *  @return 区间求和
 */
int query(int l, int r, int idx = 1)
{
    if (tree[idx].left >= l && tree[idx].right <= r) // idx节点负责的范围在所求[l ,r]内
    {
        return tree[idx].val;
    }

    push_down(idx);

    int mid = tree[idx].left + ((tree[idx].right - tree[idx].left) >> 1);
    int ret = 0;
    if (l <= mid)
    {
        ret += query(l, r, idx << 1);
    }
    if (r > mid)
    {
        ret += query(l, r, idx << 1 | 1);
    }
    return ret;
}

/**
 *  @brief update区间
 *  @param  l   区间最左
 *  @param  r   区间最右
 *  @param  value  需要增加的值
 */
void update(const int l, const int r, int value, int idx = 1)
{
    if (tree[idx].left >= l && tree[idx].right <= r) // idx节点负责的范围在所求[l ,r]内
    {
        tree[idx].val += value * (tree[idx].right - tree[idx].left + 1);
        tree[idx].lazy += value;
        return;
    }

    push_down(idx);

    int mid = tree[idx].left + ((tree[idx].right - tree[idx].left) >> 1);

    if (l <= mid)
    {
        update(l, r, idx << 1);
    }
    if (r > mid)
    {
        update(l, r, idx << 1 | 1);
    }

    tree[idx].val = tree[idx << 1].val + tree[idx << 1 | 1].val;
}

/**
 *  @brief 建树
 *  @param  l   区间最左
 *  @param  r   区间最右
 */
void build(int l, int r, int idx = 1)
{
    if (l == r)
    { // 到了叶子节点
        tree[idx] = {l, r, arr[l - 1], 0};
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
    tree[idx] = {l, r, tree[idx << 1].val + tree[idx << 1 | 1].val, 0};
}

int main()
{
    build(1, arr.size());
}