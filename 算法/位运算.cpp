#include <bits/stdc++.h>

int main()
{
    int x;

    // 取x的最低位1, lowbit
    x & (-x);

    // 去掉最后一个1
    x &(x - 1);

    // *2
    x << 1;

    // /2
    x >> 1;

    // 求1的数量
    int cnt = 0;
    while (x)
    {
        cnt++;
        x &= x - 1;
    }

    // 0^1=1, 1^1=0
    // 和1异或相当于取反

    // 和0或相当于没有改变
}