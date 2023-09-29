#include <bits/stdc++.h>

// 邻接矩阵, N^2空间复杂度, 值存权值, 不存在边就-1

// 邻接表, next把连接的所有边连上, 截止条件为NULL

// 链式前向星(邻接表存边)
#define SIZE 100005
struct E
{
    int to;
    int weight;
    int next;
} Edge[SIZE << 1];
int edge_cnt;
int Head[SIZE] = {-1}; // 存的是边的指针, 前n个存的是一共n个点的起始

void AddEdge(int u, int v, int w)
{
    Edge[edge_cnt].to = v;
    Edge[edge_cnt].weight = w;
    Edge[edge_cnt].next = Head[u];
    Head[u] = edge_cnt;
    edge_cnt++;
}

int main()
{
    // for (int i = Head[u]; ~i; i = Edge[i].next)
    return 0;
}