#include <iostream>
#include <algorithm>
using namespace std;

struct point
{
    int arr[2];
    int w;
};

struct node
{
    int minimum[2];
    int maximum[2];
    int sum;
    int left;
    int right;
    int size;
    point cur;
};
point p[400005];
node tree[400005];
int root;
int pool[400005];
int top;
int cur;
int DIMENSION;

int newnode()
{
    if (top)
    {
        return pool[top--];
    }
    else
    {
        return ++cur;
    }
}

void up(int k)
{
    int l = tree[k].left;
    int r = tree[k].right;
    // int tmp = i==0? tree[k].cur.x : tree[k].cur.y;
    for (int i = 0; i < 2; i++)
    {

        tree[k].minimum[i] = tree[k].maximum[i] = tree[k].cur.arr[i];
        if (l)
        {
            tree[k].minimum[i] = min(tree[k].minimum[i], tree[l].minimum[i]);
            tree[k].maximum[i] = max(tree[k].maximum[i], tree[l].maximum[i]);
        }
        if (r)
        {
            tree[k].minimum[i] = min(tree[k].minimum[i], tree[r].minimum[i]);
            tree[k].maximum[i] = max(tree[k].maximum[i], tree[r].maximum[i]);
        }
    }
    tree[k].sum = tree[l].sum + tree[r].sum + tree[k].cur.w;
    tree[k].size = tree[l].size + tree[r].size + 1;
}

void ldr(int k, int num)
{
    if (tree[k].left)
    {
        ldr(tree[k].left, num);
    }
    p[tree[tree[k].left].size + num + 1] = tree[k].cur;
    pool[++top] = k;
    if (tree[k].right)
    {
        ldr(tree[k].right, num + tree[tree[k].left].size + 1);
    }
}

bool operator<(point &a, point &b)
{
    return a.arr[DIMENSION] < b.arr[DIMENSION];
}

int build(int l, int r, int dimension)
{
    if (l > r)
    {
        return 0;
    }
    int mid = (l + r) >> 1;
    int k = newnode();
    DIMENSION = dimension;
    nth_element(p + l, p + mid, p + r + 1);
    tree[k].cur = p[mid];
    tree[k].left = build(l, mid - 1, dimension ^ 1);
    tree[k].right = build(mid + 1, r, dimension ^ 1);
    up(k);
    return k;
}

void check(int &k, int dimension)
{
    if (tree[k].size * 0.75 < tree[tree[k].left].size ||
        tree[k].size * 0.75 < tree[tree[k].right].size)
    {
        ldr(k, 0);
        k = build(1, tree[k].size, dimension);
    }
}

void insert(int &k, point &tmp, int dimension)
{
    if (!k)
    {
        k = newnode();
        tree[k].right = tree[k].left = 0;
        tree[k].cur = tmp;
        up(k);
        return;
    }
    if (tmp.arr[dimension] <= tree[k].cur.arr[dimension])
    {
        insert(tree[k].left, tmp, dimension ^ 1);
    }
    else
    {
        insert(tree[k].right, tmp, dimension ^ 1);
    }
    up(k);
    if (k == root)
    {
        check(root, 0);
    }
}

int in(int x1, int y1, int x2, int y2, int X1, int Y1, int X2, int Y2) // 后者是否在前者里
{
    return (X1 >= x1 && X2 <= x2 && Y1 >= y1 && Y2 <= y2);
}

int out(int x1, int y1, int x2, int y2, int X1, int Y1, int X2, int Y2)
{
    return (x1 > X2 || x2 < X1 || y1 > Y2 || y2 < Y1);
}

int query(int k, int x1, int y1, int x2, int y2)
{
    if (!k)
    {
        return 0;
    }
    if (in(x1, y1, x2, y2, tree[k].minimum[0], tree[k].minimum[1], tree[k].maximum[0], tree[k].maximum[1]))
    {
        return tree[k].sum;
    }
    // if (out(x1, y1, x2, y2, tree[k].minimum[0], tree[k].minimum[1], tree[k].maximum[0], tree[k].maximum[1])){
    //     return 0;
    // }
    int ret = 0;
    if (in(x1, y1, x2, y2, tree[k].cur.arr[0], tree[k].cur.arr[1], tree[k].cur.arr[0], tree[k].cur.arr[1]))
    {
        ret += tree[k].cur.w;
    }
    if (!out(x1, y1, x2, y2, tree[tree[k].left].minimum[0], tree[tree[k].left].minimum[1], tree[tree[k].left].maximum[0], tree[tree[k].left].maximum[1]))
        ret += query(tree[k].left, x1, y1, x2, y2);
    if (!out(x1, y1, x2, y2, tree[tree[k].right].minimum[0], tree[tree[k].right].minimum[1], tree[tree[k].right].maximum[0], tree[tree[k].right].maximum[1]))
        ret += query(tree[k].right, x1, y1, x2, y2);

    return ret;
}

int main()
{
    // freopen("input.txt", "r", stdin);
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    int cmd, x, y, x2, y2, A;
    int lastans = 0;

    while (true)
    {
        cin >> cmd;
        if (cmd == 1)
        {
            cin >> x >> y >> A;
            x ^= lastans;
            y ^= lastans;
            A ^= lastans;
            point p({x, y, A});
            insert(root, p, 0);
        }
        else if (cmd == 2)
        {
            cin >> x >> y >> x2 >> y2;
            x ^= lastans;
            y ^= lastans;
            x2 ^= lastans;
            y2 ^= lastans;
            lastans = query(root, x, y, x2, y2);
            cout << lastans << endl;
        }
        else
        {
            break;
        }
    }
    return 0;
}