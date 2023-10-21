#include <windows.h>
#include <psapi.h>
#include <bits/stdc++.h>
using namespace std;

int main()
{
    // freopen("input.txt", "r", stdin);
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // solve();
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc)))
    {
        std::cout << "Working Set Size: " << pmc.PagefileUsage / 1024 << " KB" << std::endl;
    }
    else
    {
        std::cerr << "Error retrieving memory info." << std::endl;
    }
    return 0;
}
