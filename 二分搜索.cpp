#include <bits/stdc++.h>

/**
 *  @brief 二分搜索, 找第一个满足条件的点
 *  @param  L   index of first element
 *  @param  R    index of last element + 1 (array size)
 *  @param  arr     非升序或非降序数组array
 *  @param  target     target value
 *  @return  数列中从左到右第一个满足条件的点
 */
int bsearch1(int L, int R, const int *arr, const int target)
{
    while (L < R)
    {
        int mid = (L + R) >> 1;
        if (arr[mid] >= target) // 求非降序数组lower_bound, 修改为>则为求upper_bound, 修改为< 或 <= 则为求非升序数组中相应的bound
            R = mid;
        else
            L = mid + 1;
    }
    return L;
}

/**
 *  @brief 二分搜索, 找第一个不满足条件的点
 *  @param  L   index of first element
 *  @param  R    index of last element
 *  @param  arr     非升序或非降序数组array
 *  @param  target     target value
 *  @return  数列中从左到右第一个不满足条件的点
 */
int bsearch2(int L, int R, const int *arr, const int target)
{
    while (L < R)
    {
        int mid = (L + R + 1) >> 1;
        if (arr[mid] >= target)
        {
            L = mid;
        }
        else
            R = mid - 1;
    }
    if (arr[L] < target)
    {
        return -1;
    }
    return L;
}

int main()
{
    // bsearch1
    int arr[] = {1, 3, 3, 5, 5, 7};
    std::cout << bsearch1(0, sizeof(arr) / sizeof(int), arr, 3) << '\n'; // 输出 1
    std::vector<int> v = {1, 3, 3, 5, 5, 7};
    std::cout << std::lower_bound(v.begin(), v.end(), 3) - v.begin() << '\n'; // 与上述等价

    // bsearch2
    int arr2[] = {7, 5, 5, 3, 3, 1};
    std::cout << bsearch2(0, sizeof(arr) / sizeof(int) - 1, arr, 3) << '\n'; // 4
    std::cout << bsearch2(0, sizeof(arr) / sizeof(int) - 1, arr, 8) << '\n'; // -1

    // 非升序数组的lower_bound用法
    std::vector<int> v = {7, 5, 5, 3, 3, 1};
    std::cout << std::lower_bound(v.begin(), v.end(), 3, std::greater<int>()) - v.begin() << '\n'; // 3
    std::cout << std::upper_bound(v.begin(), v.end(), 3, std::greater<int>()) - v.begin() << '\n'; // 5
    std::cout << std::upper_bound(v.begin(), v.end(), 0, std::greater<int>()) - v.begin() << '\n'; // 6

    return 0;
}