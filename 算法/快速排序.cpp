#include <bits/stdc++.h>

void quick_sort(int *arr, int l, int r)
{
    if (l >= r)
        return;
    int i = l - 1;
    int j = r + 1;
    int x = arr[l + ((r - l) >> 1)];
    while(i < j){
        do i++; while(arr[i] < x);
        do j--; while(arr[j] > x);
        if(i < j) std::swap(arr[i], arr[j]);
    }
    quick_sort(arr, l, j);
    quick_sort(arr, j+1, r);
}

int main()
{
    return 0;
}