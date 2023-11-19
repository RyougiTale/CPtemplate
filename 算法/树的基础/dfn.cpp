/*
带重链的dfs序
*/

// 子树会变成连续
#include <bits/stdc++.h>
using namespace std;

#define NODESIZE 13

struct Node
{
    int val;
    vector<Node *> children;
    int dfn;
    int size;
    int depth;
    Node *father;
    Node *mainson; // 重儿子
    Node *top;     // 重链顶端
} node[NODESIZE];
vector<int> vec(NODESIZE, 0);

vector<std::pair<int, int>> edges = {{1, 2}, {1, 3}, {1, 4}, {2, 5}, {2, 6}, {3, 7}, {4, 8}, {4, 9}, {6, 10}, {9, 11}, {9, 12}};

/*
1
├── 2
│   ├── 5
│   └── 6
│       └── 10
├── 3
│   └── 7
└── 4
    ├── 8
    └── 9
        ├── 11
        └── 12

*/
void dfs1(Node &u, Node &f)
{
    u.father = &f;
    u.depth = f.depth + 1;
    u.size = 1;
    int maxsize = -1;
    for (Node *child : u.children)
    {
        dfs1(*child, u);
        u.size += child->size;
        if (child->size > maxsize)
        {
            maxsize = child->size;
            u.mainson = child;
        }
    }
}

int tim = 0;
void dfs2(Node &u, Node &t)
{
    u.dfn = ++tim;
    u.top = &t;
    vec[tim] = u.val;
    if (u.mainson == nullptr)
    {
        return;
    }
    dfs2(*u.mainson, t);
    for (Node *child : u.children)
    {
        if (child == u.mainson)
        {
            continue;
        }
        dfs2(*child, *child);
    }
}

int count(Node &n)
{
    // cout << n.dfn << " " << n.size << endl;
    // [n.dfn, n.dfn+n.size) 区间内的值
    int sum = 0;
    for (int i = n.dfn; i < n.dfn + n.size; i++)
    {
        sum += vec[i];
    }
    return sum;
}

int main()
{
    for (int i = 1; i < NODESIZE; i++)
    {
        node[i].val = i * i;
    }
    for (auto edge : edges)
    {
        node[edge.first].children.emplace_back(&node[edge.second]);
    }
    dfs1(node[1], node[1]);
    dfs2(node[1], node[1]);
    for (int i = 1; i < NODESIZE; i++)
    {
        cout << vec[i] << " \n"[i == NODESIZE - 1];
    }
    for (int i = 1; i < NODESIZE; i++)
    {
        cout << node[i].dfn << " \n"[i == NODESIZE - 1];
    }
    cout << count(node[4]) << endl;
    return 0;
}
// vec里存的val, 是按照dfs序遍历节点加入的值, 这里存了平方
// 1 16 81 121 144 64 4 36 100 25 9 49

// 是各个节点所处的时间戳位置
// 1 7 11 2 10 8 12 6 3 9 4 5

// 计算4节点和它所有子结点值的和
// 4**2 + 8**2 + 9**2 + 11**2 + 12**2 = 426