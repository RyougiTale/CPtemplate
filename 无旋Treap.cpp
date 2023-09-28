#include <bits/stdc++.h>

#define SIZE 100000
struct Node
{
    int l;
    int r;
    int key;
    int val;
    int size;
    bool reverse;
} fhq[SIZE];

std::mt19937 rnd(996);
int root;
int cnt;

void pre()
{
    root = cnt = 0;
}

int newnode(int val)
{
    cnt++;
    fhq[cnt].l = fhq[cnt].r = fhq[cnt].reverse = 0;
    fhq[cnt].size = 1;
    fhq[cnt].key = rnd();
    fhq[cnt].val = val;
    return cnt;
}

void push_down(int idx)
{
    if (fhq[idx].reverse)
    {
        int &l = fhq[idx].l;
        int &r = fhq[idx].r;
        std::swap(l, r);
        fhq[l].reverse ^= 1;
        fhq[r].reverse ^= 1;
        fhq[idx].reverse = false;
    }
}

void update(int idx)
{
    int &l = fhq[idx].l;
    int &r = fhq[idx].r;
    fhq[idx].size = fhq[l].size + fhq[r].size + 1;
}

/**
 *  @brief 核心操作, 按随机的key值决定
 *  @details 只有2种可能的merge操作, 而两种都不改变中序遍历的结果
 *  @param  x 节点x
 *  @param  y 节点y
 *  @return 合并之后的根节点
 */
int merge(int x, int y)
{
    if (!x || !y)
    {
        return x | y;
    }
    if (fhq[x].key < fhq[y].key) // 这里维持了一个小顶堆, 换一下就会是大顶堆
    {
        push_down(x);
        fhq[x].r = merge(fhq[x].r, y);
        update(x);
        return x;
    }
    else
    {
        push_down(y);
        fhq[y].l = merge(x, fhq[y].l);
        update(y);
        return y;
    }
}

/**
 *  @brief 算是打印节点的中序遍历吧, 也就是原结构
 */
void print(int idx = root)
{
    if (!idx)
    {
        return;
    }
    push_down(idx);
    print(fhq[idx].l);
    std::cout << fhq[idx].val << " \n"[idx == cnt];
    print(fhq[idx].r);
}