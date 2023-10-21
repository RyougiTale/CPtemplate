#include <bits/stdc++.h>

#define SIZE 10000
bool is_visit[SIZE] = {false};
int arr[SIZE] = {0}; // 依赖关系
int sum[SIZE] = {0};
int deg[SIZE] = {0}; // 入度
int n;
void dfs(int x, int cursum)
{
    is_visit[x] = true;
    if (deg[x] == 0) // 入度为0的点就是可以删去的点(无人依赖)
    {
        --deg[arr[x]];
        sum[arr[x]] += cursum;
        if (deg[arr[x]] == 0) // 如果删去一个入度的点入度为0
        {
            dfs(arr[x], sum[arr[x]] + 1);
        }
    }
}

int main()
{
    for (int i = 0; i < n; i++)
    {
        deg[arr[i]]++; // 入度
    }

    for (int i = 0; i < n; i++)
    {
        if (deg[i] == 0 && is_visit[i] == false)
        {
            dfs(i, 1);
        }
    }

    // 之后解决环的问题
    for (int i = 0; i < n; i++)
    {
        if (is_visit[i] == true)
        {
            continue;
        }
        std::vector<int> circle;
        for (int k = i; is_visit[k] == false; k = arr[k])
        {
            is_visit[k] = true;
            circle.emplace_back(k);
        }
        // 环
    }
    return 0;
}